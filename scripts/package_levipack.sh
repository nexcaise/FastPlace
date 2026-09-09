#!/usr/bin/env bash
# Kemas hasil build (.so) + manifest.json (+ resources/) jadi file .levipack
#
# Pakai script ini alih-alih packaging di dalam xmake.lua, karena
# import("utils.archive") milik xmake kadang gagal menemukan archiver
# (zip/7z) saat cross-compiling untuk Android di beberapa environment
# (termasuk beberapa runner GitHub Actions).
#
# Usage: scripts/package_levipack.sh <mod_name> <build_dir>
# Contoh: scripts/package_levipack.sh MyLeviMod build

set -euo pipefail

if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <mod_name> <build_dir>" >&2
    exit 1
fi

MOD_NAME="$1"
BUILD_DIR="$2"

if ! command -v zip >/dev/null 2>&1; then
    echo "Error: 'zip' tidak ditemukan. Install dulu (mis. apt-get install -y zip)." >&2
    exit 1
fi

SO_FILE=$(find "$BUILD_DIR" -name "lib${MOD_NAME}.so" | head -n1)
if [ -z "$SO_FILE" ]; then
    echo "Error: lib${MOD_NAME}.so tidak ditemukan di bawah '$BUILD_DIR'." >&2
    echo "Pastikan sudah build dulu (xmake -y) dan MOD_NAME sesuai xmake.lua." >&2
    exit 1
fi

OUT_DIR="$(dirname "$SO_FILE")"
PACK_DIR="$OUT_DIR/pack"
PACK_FILE="$OUT_DIR/${MOD_NAME}.levipack"

rm -rf "$PACK_DIR" "$PACK_FILE"
mkdir -p "$PACK_DIR"

cp "$SO_FILE" "$PACK_DIR/lib${MOD_NAME}.so"
cp manifest.json "$PACK_DIR/manifest.json"
if [ -d resources ]; then
    cp -r resources "$PACK_DIR/resources"
fi

( cd "$PACK_DIR" && zip -r -q "../$(basename "$PACK_FILE")" . )

echo "Mod .so     : $SO_FILE"
echo "Mod package : $PACK_FILE"

# Untuk dikonsumsi step GitHub Actions lewat $GITHUB_OUTPUT
if [ -n "${GITHUB_OUTPUT:-}" ]; then
    {
        echo "so_file=$SO_FILE"
        echo "pack_file=$PACK_FILE"
    } >> "$GITHUB_OUTPUT"
fi

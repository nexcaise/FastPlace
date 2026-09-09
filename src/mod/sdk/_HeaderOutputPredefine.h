#pragma once

#pragma warning(disable : 4099)
#pragma warning(disable : 4201)
#pragma warning(disable : 4373)

#if defined(__cplusplus)
    #define NC_CXX 1
#else
    #define NC_CXX 0
#endif

#if !defined(__ANDROID__)
    #error "This header is for Android only."
#endif

#define NC_STRINGIFY_IMPL(x) #x
#define NC_STRINGIFY(x) NC_STRINGIFY_IMPL(x)
#define NC_CONCAT_IMPL(a, b) a##b
#define NC_CONCAT(a, b) NC_CONCAT_IMPL(a, b)

#if defined(__clang__) || defined(__GNUC__)
    #define NC_EXPORT __attribute__((visibility("default")))
    #define NC_IMPORT __declspec(dllimport)
    #define NC_HIDDEN  __attribute__((visibility("hidden")))
    #define NC_UNUSED  __attribute__((unused))
    #define NC_USED    __attribute__((used))
    #define NC_NORETURN __attribute__((noreturn))
    #define NC_ALWAYS_INLINE inline __attribute__((always_inline))
    #define NC_NEVER_INLINE __attribute__((noinline))
    #define NC_PACKED __attribute__((packed))
    #define NC_ALIGNED(n) __attribute__((aligned(n)))
    #define NC_LIKELY(x)   __builtin_expect(!!(x), 1)
    #define NC_UNLIKELY(x) __builtin_expect(!!(x), 0)
    #define NC_UNREACHABLE() __builtin_unreachable()
    #define NC_RESTRICT __restrict__
    #define NC_ONLOAD __attribute__((constructor))
    #define NC_ONUNLOAD __attribute__((destructor))
#else
    #define NC_EXPORT
    #define NC_HIDDEN
    #define NC_UNUSED
    #define NC_USED
    #define NC_NORETURN
    #define NC_ALWAYS_INLINE inline
    #define NC_NEVER_INLINE
    #define NC_PACKED
    #define NC_ALIGNED(n)
    #define NC_LIKELY(x) (x)
    #define NC_UNLIKELY(x) (x)
    #define NC_UNREACHABLE() ((void)0)
    #define NC_RESTRICT
    #define NC_ONLOAD
    #define NC_ONUNLOAD
#endif

#if defined(__IMPORT__)
    #define NC NC_IMPORT
#else
    #define NC NC_EXPORT
#endif

#if NC_CXX
    #define NC_EXTERN_C_BEGIN extern "C" {
    #define NC_EXTERN_C_END }
#else
    #define NC_EXTERN_C_BEGIN
    #define NC_EXTERN_C_END
#endif

#if NC_CXX
    #if defined(__has_cpp_attribute)
        #if __has_cpp_attribute(nodiscard)
            #define NC_NODISCARD [[nodiscard]]
        #else
            #define NC_NODISCARD __attribute__((warn_unused_result))
        #endif

        #if __has_cpp_attribute(maybe_unused)
            #define NC_MAYBE_UNUSED [[maybe_unused]]
        #else
            #define NC_MAYBE_UNUSED __attribute__((unused))
        #endif

        #if __has_cpp_attribute(fallthrough)
            #define NC_FALLTHROUGH [[fallthrough]]
        #else
            #define NC_FALLTHROUGH __attribute__((fallthrough))
        #endif
    #else
        #define NC_NODISCARD __attribute__((warn_unused_result))
        #define NC_MAYBE_UNUSED __attribute__((unused))
        #define NC_FALLTHROUGH __attribute__((fallthrough))
    #endif
#else
    #define NC_NODISCARD __attribute__((warn_unused_result))
    #define NC_MAYBE_UNUSED __attribute__((unused))
    #define NC_FALLTHROUGH __attribute__((fallthrough))
#endif

#define API NC_MAYBE_UNUSED NC
#define NAPI NC_HIDDEN
#define HIDDEN NC_HIDDEN

#if NC_CXX
    #define CAPI extern "C" API
#else
    #define CAPI extern API
#endif

#define API_IMPORT  NC_IMPORT
#define API_EXPORT  NC_EXPORT
#define API_HIDDEN  NC_HIDDEN
#define API_UNUSED   NC_UNUSED
#define API_USED     NC_USED
#define API_NODISCARD NC_NODISCARD
#define API_MAYBE_UNUSED NC_MAYBE_UNUSED
#define API_NORETURN NC_NORETURN
#define API_ALWAYS_INLINE NC_ALWAYS_INLINE
#define API_NEVER_INLINE NC_NEVER_INLINE
#define API_PACKED NC_PACKED
#define API_ALIGNED(n) NC_ALIGNED(n)
#define API_LIKELY(x) NC_LIKELY(x)
#define API_UNLIKELY(x) NC_UNLIKELY(x)
#define API_UNREACHABLE() NC_UNREACHABLE()
#define API_RESTRICT NC_RESTRICT
#define API_FALLTHROUGH NC_FALLTHROUGH

#define NCIS API_HIDDEN inline static
#define NCS API_HIDDEN static

#define MCAPI  API
#define MCTAPI template<> MCAPI
#define MCFOLD MCAPI /*Identical COMDAT Folding*/
#define MCNAPI [[deprecated("This API is not available. Open an ticket if you need it. "\
                            "https://nexcaise.my.id/feedback")]] MCAPI

#if defined(NC_CXX) && NC_CXX
#include <expected>
#endif

#include <android/log.h>
#include <android/dlext.h>
#include <algorithm>
#include <any>
#include <array>
#include <atomic>
#include <bitset>
#include <cstdint>
#include <cctype>
#include <cerrno>
#include <chrono>
#include <clocale>
#include <cmath>
#include <complex>
#include <condition_variable>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>
#include <dlfcn.h>
#include <deque>
#include <dirent.h>
#include <exception>
#include <elf.h>
#include <filesystem>
#include <fcntl.h>
#include <forward_list>
#include <fstream>
#include <future>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <jni.h>
#include <limits>
#include <list>
#include <link.h>
#include <map>
#include <memory>
#include <mutex>
#include <numbers>
#include <optional>
#include <ostream>
#include <pthread.h>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <sys/stat.h>
#include <sys/mman.h>
#include <shared_mutex>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <string_view>
#include <thread>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <unistd.h>
#include <variant>
#include <vector>

#include <entt/entt.hpp>
#include "Gloss.h"
#include "Hook.h"

using ushort = unsigned short;
using uint = unsigned int;
using ulong = unsigned long;
using llong = long long;
using ullong = unsigned long long;
using uchar = unsigned char;
using schar = signed char;
using byte = uchar;
using ldouble = long double;
using int64 = long long;
using int32 = int;
using int16 = short;
using int8 = char;
using uint64 = unsigned long long;
using uint32 = unsigned int;
using uint16 = unsigned short;
using uint8 = unsigned char;

namespace fs = std::filesystem;
using Clock = std::chrono::steady_clock;

template <typename TreatAs, typename Pointer>
extern TreatAs& directAccess(Pointer ptr, size_t offset) {
    return *reinterpret_cast<TreatAs*>(reinterpret_cast<uintptr_t>(ptr) + offset);
}

#define CLASS_FIELD(type, name, offset)                                                                          \
    __declspec(property(get = __get_field_##name, put = __set_field_##name)) type name;                          \
    type& __get_field_##name() const { return directAccess<type>(this, offset); }                                 \
    template <typename T>                                                                                        \
    void __set_field_##name(const T& value) { directAccess<type>(this, offset) = value; }

template <std::size_t IIdx, typename TRet, typename... TArgs>
static TRet callVirtualFunc(void* thisptr, TArgs&&... args) {
    using Fn = TRet(*)(void*, TArgs...);
    return (*reinterpret_cast<Fn**>(thisptr))[IIdx](thisptr, std::forward<TArgs>(args)...);
}

template <typename TRet, typename... TArgs>
static TRet callVirtualFuncI(uint32_t index, void* thisptr, TArgs&&... args) {
    using Fn = TRet(*)(void*, TArgs...);
    return (*reinterpret_cast<Fn**>(thisptr))[index](thisptr, std::forward<TArgs>(args)...);
}

inline uintptr_t getLibBase(const char* libname) {
    size_t textSize{};
    uintptr_t text = GlossGetLibSection(libname, ".text", &textSize);
    Dl_info info{};
    if (dladdr((void*)text, &info))
        return (uintptr_t)info.dli_fbase;
    return 0;
}
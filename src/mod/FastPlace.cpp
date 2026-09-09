#include "mod/FastPlace.h"
#include "sdk/GameMode.h"
#include "sdk/ToastAPI.hpp"
#include "sdk/InteractionResult.h"
#include <pl/Mod.hpp>

struct StartMenuScreenController {};

LL_TYPED_HOOK(
    StartMenuScreenController_open,
    memory::HookPriority::Normal,
    StartMenuScreenController,
    pl::memory::resolveVtableFunction("25StartMenuScreenController", 7, "libminecraftpe.so"),
    "libminecraftpe.so",
    void
) {
    origin();
    nexcaise::toastapi::sendToastMessage("FastPlace by NexCaise!");
};

LL_TYPED_HOOK(
    GameMode_useItemOn,
    memory::HookPriority::Normal,
    GameMode,
    pl::memory::resolveVtableFunction("8GameMode", 14, "libminecraftpe.so"),
    "libminecraftpe.so",
    InteractionResult,
    ItemStackBase* stack,
    void* a3,
    unsigned char a4,
    void* a5,
    void* a6,
    bool a7
) {
    if (!mPlayer) {
        return origin(stack, a3, a4, a5, a6, a7);
    }

    auto* mainhand = mPlayer->getHand(0);
    if (!mainhand) {
        return origin(stack, a3, a4, a5, a6, a7);
    }

    origin(stack, a3, a4, a5, a6, a7);
    return origin(mainhand, a3, a4, a5, a6, a7);
};

namespace nexcaise {

FastPlace &FastPlace::getInstance() {
    static FastPlace instance;
    return instance;
}

FastPlace::FastPlace() : mSelf(*ll::mod::NativeMod::current()) {}

bool FastPlace::load() {
    auto &self = getSelf();
    self.getLogger().info("Loading...");
    nexcaise::toastapi::setupAPI();
    return true;
}

bool FastPlace::enable() {
    auto &self = getSelf();
    self.getLogger().info("Enabling...");
    StartMenuScreenController_open::hook();
    GameMode_useItemOn::hook();
    return true;
}

bool FastPlace::disable() {
    getSelf().getLogger().info("Disabling...");
    StartMenuScreenController_open::unhook();
    GameMode_useItemOn::unhook();
    return true;
}

bool FastPlace::unload() {
    getSelf().getLogger().info("Unloading...");
    nexcaise::toastapi::inactiveAPI();
    return true;
}

} // namespace nexcaise

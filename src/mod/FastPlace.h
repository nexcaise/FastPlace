#pragma once

#include <pl/Mod.hpp>

namespace nexcaise {

class FastPlace {
  public:
    static FastPlace &getInstance();

    FastPlace();

    [[nodiscard]] ll::mod::NativeMod &getSelf() const { return mSelf; }

    bool load();
    bool enable();
    bool disable();
    bool unload();

  private:
    ll::mod::NativeMod &mSelf;
};

} // namespace nexcaise

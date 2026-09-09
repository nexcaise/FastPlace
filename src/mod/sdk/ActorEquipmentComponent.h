#pragma once

#include "_HeaderOutputPredefine.h"
#include "IEntityComponent.h"
#include "ItemStackBase.h"

class SimpleContainer {
public:
    virtual ~SimpleContainer();
    virtual void vfunc1() = 0;
    virtual void vfunc2() = 0;
    virtual void vfunc3() = 0;
    virtual void vfunc4() = 0;
    virtual void vfunc5() = 0;
    virtual void vfunc6() = 0;
    virtual ItemStackBase* getItem(int) = 0;
};

struct ActorEquipmentComponent : IEntityComponent {
    static constexpr uint32_t type_hash = 0xB06141A9;

    SimpleContainer* handContainer;
    SimpleContainer* armorContainer;
};
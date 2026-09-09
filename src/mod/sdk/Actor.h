#pragma once

#include "EntityContext.h"
#include "ActorEquipmentComponent.h"

//class Level {
//public:
//    
//};

class Actor {
public:
    CLASS_FIELD(EntityContext, entityContext, 0x8);
//    CLASS_FIELD(Level*, mLevel, 0x1D0);
public:
    template<typename T>
    T* tryGetComponent() {
        return entityContext.enttRegistry.try_get<T>(entityContext.entity);
    }
    ItemStackBase* getArmor(int slot) {
        return this->tryGetComponent<ActorEquipmentComponent>()->armorContainer->getItem(slot);
    }
    ItemStackBase* getHand(int slot) {
        return this->tryGetComponent<ActorEquipmentComponent>()->handContainer->getItem(slot);
    }
};
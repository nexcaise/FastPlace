#pragma once

#include "_HeaderOutputPredefine.h"
#include "Ptr.h"
#include "Item.h"

class CompoundTag;

class ItemStackBase {
public:
    WeakPtr<Item> mItem;
    CompoundTag*  mUserData;
    const void*   mBlock;
    short       mAuxValue;
    uint8_t       mCount;
    bool          mValid_DeprecatedSeeComment;
    bool          mShowPickUp;
    bool          mWasPickedUp;

    uint8_t _pad_26[0x28 - 0x26];

    std::chrono::steady_clock::time_point mPickupTime;

    ItemStackBase();
    ItemStackBase(const ItemStackBase&);
    ItemStackBase& operator=(const ItemStackBase&);
    virtual ~ItemStackBase();

    virtual void reinit_item(const Item&, int, int);
    virtual void reinit_block(const void*, int);
    virtual void reinit_name(const void*, int, int);
    virtual void setNull(void*);

    virtual std::string toString() const;
    virtual std::string toDebugString() const;
public:
    Item* getItem() {
        Item* item = mItem.get();
        if (!item) return nullptr;
        return item;
    }
};
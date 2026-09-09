#pragma once

class Item;
class ItemStackBase;
class Actor;

class IFoodItemComponent {
public:
    virtual ~IFoodItemComponent() = default;
    virtual int getNutrition() const = 0;
    virtual float getSaturationModifier() const = 0;
    virtual bool canAlwaysEat() const = 0;
    virtual Item* eatItem(ItemStackBase&, Actor&, void*) = 0;
};

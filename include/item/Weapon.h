#ifndef WEAPON_H_
#define WEAPON_H_

#include "Item.h"

class Weapon : public Item {
   private:
    int damageValue;  // 伤害值
    int maxAbrasion;
    int abrasion;
    const int abrasionLoss;  // 每使用一次的磨损量
};

#endif  // WEAPON_H_
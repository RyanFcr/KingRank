#ifndef WEAPON_H_
#define WEAPON_H_

#include "Item.h"
#include "common/Config.h"

class Weapon : public Item {
   public:
    Weapon() {}
    Weapon(string n, string d, int w, int attack, int abrasionLoss)
        : Item(n, d, w, WEAPON_ID), attack(attack), abrasion(maxAbrasion), abrasionLoss(abrasionLoss) {}

   private:
    int attack;        // 攻击力
    int abrasion;      // 当前磨损量
    int abrasionLoss;  // 每使用一次的磨损量
};

#endif  // WEAPON_H_
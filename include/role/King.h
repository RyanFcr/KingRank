#ifndef KING_H_
#define KING_H_

#include "Role.h"
#include "bag/Bag.h"
#include "common/Global.h"
#include "map/Map.h"
#include "skill/Skill.h"
#include "text/TextGen.h"

class King : public Role {
   public:
    King() {}
    King(string name, Position position, FieldPosition territoryPosition, Bag bag, int attack = 1, int level = 1, int maxHP = 100, int HP = 100, int maxMP = 100, int MP = 100, int experience = 0, int money = 0)
        : Role(name, position, attack, level, maxHP, HP, maxMP, MP), experience(experience), territoryPosition(territoryPosition), money(money), bag(bag) {
    }
    void ShowMap(const Map& m) const;
    void GoUp(const Map& m);
    void GoDown(const Map& m);
    void GoLeft(const Map& m);
    void GoRight(const Map& m);

   private:
    int experience;                   // 当前的经验值
    FieldPosition territoryPosition;  // 领地位置
    int money;                        // 拥有的金币量
    Bag bag;
    vector<Skill*> skills;
};

#endif  // KING_H_
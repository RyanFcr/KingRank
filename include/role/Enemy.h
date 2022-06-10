#ifndef ENEMEY_H_
#define ENEMEY_H_

#include <vector>
using std::vector;

#include "Role.h"
#include "skill/Skill.h"

class Enemy : public Role {
   public:
    Enemy(string name, int level, int attack, int maxHP, int HP, int maxMP, int MP, int experienceVal, int moneyVal)
        : Role(name, level, attack, maxHP, HP, maxMP, MP), experienceVal(experienceVal), moneyVal(moneyVal) {}
    
    int GetExperienceVal() const { return experienceVal; }
    int GetMoneyVal() const { return moneyVal; }

   private:
    int experienceVal;  // 得到的经验值
    int moneyVal;       // 得到的钱
};

#endif  // ENEMY_H_
#ifndef ATTACK_SKILL_H_
#define ATTACK_SKILL_H_

#include "Skill.h"

class AttackSkill : public Skill {
   public:
    AttackSkill() {}
    AttackSkill(const string& n, const string& d, int MPCost, int damageValue)
        : Skill(n, d, MPCost, ATTACK_SKILL_ID), damageValue(damageValue) {}
    int GetDamageValue() const { return damageValue; }
    void SetDamageValue(int damage) { damageValue = damage; }

   private:
    int damageValue;  // 伤害
};

#endif  // ATTACK_SKILL_H_
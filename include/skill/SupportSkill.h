#ifndef SUPPORT_SKILL_H_
#define SUPPORT_SKILL_H_

#include "skill/Skill.h"

class SupportSkill : public Skill {
   public:
    SupportSkill() {}
    SupportSkill(const string& n, const string& d, int MPCost, int HPValue)
        : Skill(n, d, MPCost, ATTACK_SKILL_ID), HPValue(HPValue) {}

    int GetHPValue() const { return HPValue; }

    void SetHPValue(int HP) { HPValue = HP; }

   private:
    int HPValue;  // 回血量(百分数)
};

#endif  // SUPPORT_SKILL_H_
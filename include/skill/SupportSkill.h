#ifndef SUPPORT_SKILL_H_
#define SUPPORT_SKILL_H_

#include "skill/Skill.h"

class SupportSkill : public Skill {
private:
    int HPValue; // 回血量
    int MPValue; // 回魔量
};

#endif // SUPPORT_SKILL_H_
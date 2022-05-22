#ifndef SKILL_H_
#define SKILL_H_

#include <string>
using std::string;

enum SkillId {
    ATTACK_SKILL_ID,
    SUPPORT_SKILL_ID
};

class Skill {
   protected:
    string name;         // 技能名
    string description;  // 技能介绍
    SkillId id;          // 技能类型
};

#endif  // SKILL_H_
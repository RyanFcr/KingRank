#ifndef SKILLGEN_H_
#define SKILLGEN_H_

#include "AttackSkill.h"
#include "SupportSkill.h"

#include <map>
using std::map;
using std::string;

class SkillGen {
   public:
    static void Init();

   public:
    static map<string, AttackSkill> attackSkills;
    static map<string, SupportSkill> supportSkills;
};

#endif
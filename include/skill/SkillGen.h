#ifndef SKILLGEN_H_
#define SKILLGEN_H_

#include "AttackSkill.h"
#include "SupportSkill.h"

#include <map>
#include <vector>
using std::map;
using std::string;
using std::vector;

class SkillGen {
   public:
    static void Init();

   public:
    static map<string, AttackSkill> attackSkills;
    static map<string, SupportSkill> supportSkills;
    static vector<string> attackSkillsVector;
    static vector<string> supportSkillsVector;
};

#endif
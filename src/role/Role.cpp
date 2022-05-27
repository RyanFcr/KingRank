#include "role/Role.h"

const AttackSkill& Role::GetRandomAttackSkill() {
    int index = rand() % attackSkills.size();
    return attackSkills.at(attackSkillNames[index]);
}

const SupportSkill& Role::GetRandomSupportSkill() {
    int index = rand() % supportSkills.size();
    return supportSkills.at(supportSkillNames[index]);
}
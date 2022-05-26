#include "role/Role.h"

const AttackSkill& Role::GetRandomAttackSkill() {
    int i = 0;
    int index = rand() % attackSkills.size();
    for (auto it = attackSkills.begin(); it != attackSkills.end(); it++) {
        if (i == index) return it->second;
        i++;
    }
}

const SupportSkill& Role::GetRandomSupportSkill() {
    int i = 0;
    int index = rand() % supportSkills.size();
    for (auto it = supportSkills.begin(); it != supportSkills.end(); it++) {
        if (i == index) return it->second;
        i++;
    }
}
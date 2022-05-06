#ifndef ENEMEY_H_
#define ENEMEY_H_

#include <vector>
using std::vector;

#include "Role.h"
#include "skill/Skill.h"

class Enemy : public Role {
private:
    int experienceVal; // 得到的经验值
    int moneyVal; // 得到的钱
    vector<Skill*> skills;
};

#endif // ENEMY_H_
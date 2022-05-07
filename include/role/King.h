#ifndef KING_H_
#define KING_H_

#include "bag/Bag.h"
#include "Role.h"
#include "skill/Skill.h"
#include "common/Global.h"

class King : public Role {
public:
    King(string name, Position position = {fieldNum, 0, 0}, int level = 1, int maxHP = 100, int HP = 100, 
        int maxMP = 100, int MP = 100, int experience = 0) 
        : Role(name, position, level, maxHP, HP, maxMP, MP), experience(experience) {
        
    }
private:
    int experience; //当前的经验值
    Bag bag;
    vector<Skill*> skills;
};

#endif // KING_H_
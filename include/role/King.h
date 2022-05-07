#ifndef KING_H_
#define KING_H_

#include "bag/Bag.h"
#include "Role.h"
#include "skill/Skill.h"

class King : public Role {
private:
    int experience; //当前的经验值
    Bag bag;
    vector<Skill*> skills;
};

#endif // KING_H_
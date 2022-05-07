#ifndef ROLE_H_
#define ROLE_H_

#include <string>
#include <vector>
using std::vector; using std::string;

struct Position {
    int fieldId;
    int sceneX;
    int sceneY;
};

class Role {
public:
    Role(string name, Position position, int level = 1, int maxHP = 100, int HP = 100, int maxMP = 100, int MP = 100) :
        name(name), level(level), maxHP(maxHP), HP(HP), maxMP(maxMP), MP(MP), position(position) {}
    
protected:
    string name;
    int level;
    int maxHP; //最大生命
    int HP; //现有生命值
    int maxMP; //最大魔法值
    int MP; //现有魔法值
    Position position; // 当前位置
};

#endif // ROLE_H_
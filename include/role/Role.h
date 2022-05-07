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
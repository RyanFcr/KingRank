#ifndef FIELD_H_
#define FIELD_H_

#include <string>
using std::string;

#include "common/Config.h"
#include "Scene.h"

class Field {
public:
    Field(int id, string name = "") : id(id), name(name) {}
private:
    int id; // 土地的编号
    string name; // 领地的名字
    int field[fieldSize][fieldSize]; // 土地的大小
};

#endif // FIELD_H_
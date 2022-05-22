#ifndef FIELD_H_
#define FIELD_H_

#include <string>
using std::move;
using std::string;

#include "Scene.h"
#include "common/Config.h"

class Field {
   public:
    Field(string name)
        : name(name) {}
    Scene& GetScene(int row, int col) {
        return field[row][col];
    }
    const string& GetName() const { return name; }

   private:
    string name;                        // 领地的名字
    Scene field[fieldSize][fieldSize];  // 土地上的事件
};

#endif  // FIELD_H_
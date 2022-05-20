#ifndef MAP_H_
#define MAP_H_

#include <vector>
using std::vector;

#include "Field.h"
#include "common/Global.h"

class Map {
public:
    Map();
    void MapExtend(string name = "");
private:
    vector<vector<Field*>> fields;
};

#endif // MAP_H_
#ifndef MAP_H_
#define MAP_H_

#include <vector>
using std::vector;

#include "Field.h"
#include "common/Global.h"

class Map {
public:
    void Init();
    void MapExtend(string name = "");
    ~Map() {
        for (int i = 0; i < fields.size(); i++)
            for (int j = 0; j < fields[i].size(); j++)
                delete fields[i][j];
    }
private:
    vector<vector<Field*>> fields;
};

#endif // MAP_H_
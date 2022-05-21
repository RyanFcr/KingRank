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
    Scene GetScene(const Position &p) const;
    Field GetField(const int fieldX, const int fieldY) const;
    int GetRowNum() const { return fields.size(); }
    int GetColNum(int row) const {
        if (row < 0 || row >= GetRowNum()) return 0;
        else return fields[row].size();
    }

    ~Map() {
        for (int i = 0; i < fields.size(); i++)
            for (int j = 0; j < fields[i].size(); j++)
                delete fields[i][j];
    }
private:
    vector<vector<Field*>> fields;
};

#endif // MAP_H_
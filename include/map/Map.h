#ifndef MAP_H_
#define MAP_H_

#include <vector>
using std::vector;

#include "Field.h"
#include "common/Global.h"

class Map {
   public:
    Scene GetScene(const Position& p) const;
    Field GetField(const int fieldX, const int fieldY) const;
    int GetRowNum() const { return fields.size(); }
    int GetColNum(int row) const {
        if (row < 0 || row >= GetRowNum())
            return 0;
        else
            return fields[row].size();
    }

    void PushField(Field* field, int row = -1);
    void Clear();

    bool IsValidPosition(Position& p) const;

   private:
    vector<vector<Field*>> fields;
};

#endif  // MAP_H_
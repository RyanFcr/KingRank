#ifndef MAP_H_
#define MAP_H_

#include <vector>
using std::vector;

#include "Field.h"
#include "Scene.h"
#include "common/Global.h"

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
using rapidjson::SizeType;
using rapidjson::StringBuffer;
using rapidjson::Value;
using rapidjson::Writer;

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

    template <typename Writer>
    void Serialize(Writer& writer) const {
        writer.StartObject();
        writer.String("fields");

        writer.StartArray();
        for (auto row : fields) {
            writer.StartArray();
            for (auto col : row) {
                col->Serialize(writer);
            }
            writer.EndArray();
        }
        writer.EndArray();

        writer.EndObject();
    }

   private:
    vector<vector<Field*>> fields;
};

#endif  // MAP_H_
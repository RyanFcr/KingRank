#ifndef FIELD_H_
#define FIELD_H_

#include <string>
using std::move;
using std::string;

#include "Scene.h"
#include "common/Config.h"
#include "common/Macro.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
using rapidjson::SizeType;
using rapidjson::StringBuffer;
using rapidjson::Value;
using rapidjson::Writer;

class Field {
   public:
    Field(string name = initialFieldName) : name(name) {}
    void InitScenes();
    void InitScenes(int type);
    Scene& GetScene(int row, int col) { return field[row][col]; }
    const string& GetName() const { return name; }

    template <typename Writer>
    void Serialize(Writer& writer) const {
        writer.StartObject();
        SERIALIZE_STRING("name", name)

        writer.String("field");
        writer.StartArray();
        for (int i = 0; i < fieldSize; i++) {
            writer.StartArray();
            for (int j = 0; j < fieldSize; j++)
                field[i][j].Serialize(writer);
            writer.EndArray();
        }
        writer.EndArray();

        writer.EndObject();
    }

   private:
    string name;                        // 领地的名字
    Scene field[fieldSize][fieldSize];  // 土地上的事件
};

#endif  // FIELD_H_
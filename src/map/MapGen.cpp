#include "map/MapGen.h"

#include "common/Config.h"
#include "common/Global.h"
#include "common/Macro.h"
#include "text/TextGen.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"

#include <fstream>
#include <iostream>
#include <vector>
using rapidjson::Document;
using rapidjson::SizeType;
using rapidjson::Value;
using rapidjson::Writer;
using rapidjson::StringBuffer;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::string;
using std::vector;

// instantiation
Map MapGen::map;

/**
 * @brief Init function of Map
 * `Init' must be called after the construction of Map
 * @throw OPEN_FILE_FAIL
 * @throw HAS_PARSE_ERROR
 * @throw bad_alloc
 */
void MapGen::Init() {
    ifstream ifs(mapFile, ios::in);
    if (ifs.fail())
        throw OPEN_FILE_FAIL;
    string mapData;
    std::getline(ifs, mapData);
    // Field
    string name;
    // Scene
    string enemyName, medicineName;
    int enemyPossibility, money, moneyPossibility, medicinePossibility;

    Document d;
    PARSE_DOM_OBJECT(d, mapData.c_str())
    ASSERT_DOM_OBJECT_HAS_MEMBER(d, "fields")
    ASSERT_DOM_OBJECT_IS_ARRAY(d["fields"])

    const Value& fieldsRow = d["fields"];
    for (SizeType i = 0; i < fieldsRow.Size(); i++) {
        const Value& fieldsCol = fieldsRow[i];
        vector<Field*> v;
        Field* f;

        ASSERT_DOM_OBJECT_IS_ARRAY(fieldsCol)
        for (SizeType j = 0; j < fieldsCol.Size(); j++) {
            const Value& field = fieldsCol[j];
            ASSERT_DOM_OBJECT_IS_OBJECT(field)
            DOM_OBJECT_MEMBER_TO_VAR_STRING(field, "name", name);
            ASSERT_DOM_OBJECT_HAS_MEMBER(field, "field")
            ASSERT_DOM_OBJECT_IS_ARRAY(field["field"])

            f = new Field{name};
            const Value& fieldRow = field["field"];
            for (SizeType m = 0; m < fieldRow.Size(); m++) {
                const Value& fieldCol = fieldRow[m];
                ASSERT_DOM_OBJECT_IS_ARRAY(fieldCol)

                for (SizeType n = 0; n < fieldCol.Size(); n++) {
                    const Value& scene = fieldCol[n];
                    ASSERT_DOM_OBJECT_IS_OBJECT(scene)

                    DOM_OBJECT_MEMBER_TO_VAR_STRING(scene, "enemyName", enemyName)
                    DOM_OBJECT_MEMBER_TO_VAR_INT(scene, "enemyPossibility", enemyPossibility)
                    DOM_OBJECT_MEMBER_TO_VAR_INT(scene, "money", money)
                    DOM_OBJECT_MEMBER_TO_VAR_INT(scene, "moneyPossibility", moneyPossibility)
                    DOM_OBJECT_MEMBER_TO_VAR_STRING(scene, "medicineName", medicineName)
                    DOM_OBJECT_MEMBER_TO_VAR_INT(scene, "medicinePossibility", medicinePossibility)

                    f->GetScene(m, n).Load(enemyName, enemyPossibility, money, moneyPossibility, medicineName,
                                           medicinePossibility);
                }
            }
            map.PushField(f, i);
        }
    }
    ifs.close();
}

void MapGen::Free() {
    map.Clear();
}

/**
 * @brief save the map to json file 
 * @throw OPEN_FILE_FAIL
 */
void MapGen::Save() {
    ofstream ofs(mapFile, ios::out);
    if (ofs.fail())
        throw OPEN_FILE_FAIL;
    StringBuffer sb;
    Writer<StringBuffer> writer(sb);
    map.Serialize(writer);
    string kingData = sb.GetString();
    ofs << kingData;
    ofs.close();
}
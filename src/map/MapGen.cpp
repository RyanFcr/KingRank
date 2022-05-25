#include "map/MapGen.h"

#include "common/Config.h"
#include "common/Global.h"
#include "common/Macro.h"
#include "rapidjson/document.h"
#include "text/TextGen.h"

// #include <exception>
#include <fstream>
#include <iostream>
#include <vector>
using rapidjson::Document;
using rapidjson::SizeType;
using rapidjson::Value;
// using std::bad_alloc;
using std::ifstream;
using std::ios;
using std::string;
using std::vector;

// instantiation
Map MapGen::map;
Document MapGen::d;

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

    CHECK_DOM_OBJECT_HAS_PARSE_ERROR(d, mapData.c_str())
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

                    f->GetScene(m, n).Init(enemyName, enemyPossibility, money, moneyPossibility, medicineName,
                                           medicinePossibility);
                }
            }
            map.PushField(f, i);
        }
    }
    ifs.close();

    // } catch (KRerror errorId) {
    //     switch (errorId) {
    //         case OPEN_FILE_FAIL:
    //             error = "Can't find map data! Please check the integrity of the game!";
    //             TextGen::Print<warning>(error);
    //             exit(1);  // exit forcefully
    //             break;

    //         case HAS_PARSE_ERROR:
    //             error = "Map data has parse error! Please check the validity of the data!";
    //             TextGen::Print<warning>(error);
    //             exit(1);  // exit forcefully
    //             break;

    //         default:
    //             break;
    //     }
    // } catch (const std::bad_alloc& e) {
    //     error = "Not enough memory!";
    //     TextGen::Print<warning>(error);
    //     exit(1);  // exit forcefully
    // }
}

void MapGen::MapExend() {}

void MapGen::Free() {
    map.Clear();
}
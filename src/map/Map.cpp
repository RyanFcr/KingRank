#include "map/Map.h"
#include "common/Config.h"
#include "common/Global.h"
#include "text/TextGen.h"
#include "rapidjson/document.h"

#include <iostream>
#include <fstream>
#include <exception>
#include <vector>
using std::string; using std::ifstream; 
using std::ios; using std::bad_alloc; 
using std::vector;
using rapidjson::Document; using rapidjson::SizeType;
using rapidjson::Value;

/**
 * @brief Init function of Map
 * `Init' must be called after the construction of Map
 */
void Map::Init() {
    string error;

    try {
        ifstream ifs;
        ifs.open(mapFile, ios::in);
        if (ifs.fail()) throw OPEN_FILE_FAIL;
        string mapData;
        ifs >> mapData;
        /* paser */
        Document d;
        // Field
        string name;
        // Scene
        int enemyId;
        if (d.Parse(mapData.c_str()).HasParseError()) throw HAS_PARSE_ERROR;
        if (!d.IsObject()) throw HAS_PARSE_ERROR;
        if (!d.HasMember("fields")) throw HAS_PARSE_ERROR;
        if (!d["fields"].IsArray()) throw HAS_PARSE_ERROR;

        const Value &fieldsRow = d["fields"];
        for (SizeType i = 0; i < fieldsRow.Size(); i++) {
            const Value &fieldsCol = fieldsRow[i];
            if (!fieldsCol.IsArray()) throw HAS_PARSE_ERROR;
            /// @attention 局部变量v被释放似乎不会有太大问题
            vector<Field*> v;
            Field *f;

            for (SizeType j = 0; j < fieldsCol.Size(); j++) {
                const Value &field = fieldsCol[j];
                if (!field.IsObject()) throw HAS_PARSE_ERROR;

                if (!field.HasMember("name")) throw HAS_PARSE_ERROR;
                if (!field["name"].IsString()) throw HAS_PARSE_ERROR;
                name = field["name"].GetString();

                if (!field.HasMember("field")) throw HAS_PARSE_ERROR;
                if (!field["field"].IsArray()) throw HAS_PARSE_ERROR;

                f = new Field{name};
                const Value &fieldRow = field["field"];
                for (SizeType m = 0; m < fieldRow.Size(); m++) {
                    const Value &fieldCol = fieldRow[m];
                    if (!fieldCol.IsArray()) throw HAS_PARSE_ERROR;

                    for (SizeType n = 0; n < fieldCol.Size(); n++) {
                        const Value &scene = fieldCol[n];
                        if (!scene.IsObject()) throw HAS_PARSE_ERROR;

                        if (!scene.HasMember("enemyId")) throw HAS_PARSE_ERROR;
                        if (!scene["enemyId"].IsInt()) throw HAS_PARSE_ERROR;
                        enemyId = scene["enemyId"].GetInt();

                        f->GetScene(m, n).Init(enemyId);
                    }
                }
                v.emplace_back(f);
            }
            fields.emplace_back(v);
        }
        ifs.close();
    }
    catch (KRerror errorId) {
        switch (errorId) {
            case OPEN_FILE_FAIL:
                error = "Can't find map data! Please check the integrity of the game!";
                TextGen::Print<warning>(error);
                exit(1); // exit forcefully
                break;
            
            case HAS_PARSE_ERROR:
                error = "Map data has parse error! Please check the validity of the data!";
                TextGen::Print<warning>(error);
                exit(1); // exit forcefully
                break;
            
            default:
                break;
        }
    }
    catch (bad_alloc) {
        error = "Not enough memory!";
        TextGen::Print<warning>(error);
        exit(1); // exit forcefully
    }
}

void Map::MapExtend(string name) {
    
}

Field Map::GetField(const int fieldX, const int fieldY) const {
    return *(fields[fieldX][fieldY]);
}

Scene Map::GetScene(const Position &p) const {
    return fields[p.fieldX][p.fieldY]->GetScene(p.sceneX, p.sceneY);
}

/**
 * @brief check the existence of the target field
 * The function can be called in the `MapExtend'
 * @param p position, must be normalized
 * @return true: the target field exist
 * @return false: the target fiels doesn't exist
 */
bool Map::IsValidPosition(Position &p) const {
    // check the validity
    if (p.fieldX < 0 || p.fieldX >= GetColNum(p.fieldX) ||
        p.fieldY < 0 || p.fieldY >= GetRowNum())
        return false;
    else 
        return true;
}
#include "map/Map.h"

Field Map::GetField(const int fieldX, const int fieldY) const {
    return *(fields[fieldX][fieldY]);
}

Scene Map::GetScene(const Position& p) const {
    return fields[p.fieldX][p.fieldY]->GetScene(p.sceneX, p.sceneY);
}

/**
 * @brief Push a new field to *row*-th row of map
 * @attention the field should be allocated outside the function
 * and manager outside the Map. Most times, the memory managerment
 * is depended on `MapGen' 
 * @param field 
 * @param row negative(default) or exceed size indicate start a new row
 * @return FieldPosition: the new field's position
 * @attention currently only extend to two side
 */
FieldPosition Map::PushField(Field *field, int row) {
    if (row < 0 || row >= (int)fields.size()) {
        // start a new row
        vector<Field*> v{field};
        fields.emplace_back(v);
        return FieldPosition{GetRowNum() - 1, 0};
    } else {
        fields[row].emplace_back(field);
        return FieldPosition{row, GetColNum(row) - 1};
    }
}

/**
 * @brief clear and delete the content in the map
 * @attention only called by `MapGen'
 */
void Map::Clear() {
    for (size_t i = 0; i < fields.size(); i++)
        for (size_t j = 0; j < fields[i].size(); j++)
            delete fields[i][j];
}

/**
 * @brief check the existence of the target field
 * The function can be called in the `MapExtend'
 * @param p position, must be normalized
 * @return true: the target field exist
 * @return false: the target fiels doesn't exist
 */
bool Map::IsValidPosition(Position& p) const {
    // check the validity
    if (p.fieldX < 0 || p.fieldX >= GetRowNum() ||
        p.fieldY < 0 || p.fieldY >= GetColNum(p.fieldX))
        return false;
    else
        return true;
}

FieldPosition Map::MapExtend(string countryName) {
    int index;
    for (int i = 0; i < extendPlain; i++) {
        index = rand() % (GetRowNum() + 1);
        Field *plain = new Field{};
        plain->InitScenes();
        PushField(plain, index);
    }

    index = rand() % (GetRowNum() + 1);
    Field *country = new Field{countryName};
    country->InitScenes();
    return PushField(country, index);
}
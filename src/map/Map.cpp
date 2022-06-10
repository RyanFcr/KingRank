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
FieldPosition Map::PushField(Field* field, int row) {
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
    if (p.fieldX < 0 || p.fieldX >= GetRowNum() || p.fieldY < 0 || p.fieldY >= GetColNum(p.fieldX))
        return false;
    else
        return true;
}

/**
 * @brief extend the map when a new user logins in
 * extend the map with two plains and one country
 * @param countryName name of the new user's name
 * @return FieldPosition: the field of the king's name
 */
FieldPosition Map::MapExtend(string countryName) {
    int index;
    for (int i = 0; i < extendPlain; i++) {
        index = rand() % (GetRowNum() + 1);
        Field* plain = new Field{};
        plain->InitScenes();
        PushField(plain, index);
    }

    index = rand() % (GetRowNum() + 1);
    Field* country = new Field{countryName};
    country->InitScenes();
    return PushField(country, index);
}

/**
 * @brief show directions of the given position
 * show the direction one can go nearby
 * @param p given position
 */
void Map::ShowDirection(const Position& p) const {
    if (p.fieldX >= 0 && p.fieldX < GetRowNum() && p.fieldY >= 0 && p.fieldY < GetColNum(p.fieldX)) {
        // Field Name
        string centerFieldName{GetField(p.fieldX, p.fieldY).GetName()};
        string leftFieldName{centerFieldName}, rightFieldName{centerFieldName};
        string upFieldName{centerFieldName}, downFieldName{centerFieldName};

        // Coordinate
        string leftCo{""}, rightCo{""}, upCo{""}, downCo{""};
        string centerCo = "(" + std::to_string(p.sceneX) + "," + std::to_string(p.sceneY) + ")";

        // down
        if (p.sceneX - 1 < 0 && (p.fieldX == 0 || GetColNum(p.fieldX - 1) <= p.fieldY)) {
            downFieldName = "";
            downCo = "";
        } else if (p.sceneX - 1 < 0) {
            downFieldName = GetField(p.fieldX - 1, p.fieldY).GetName();
            downCo = "(" + std::to_string(fieldSize - 1) + "," + std::to_string(p.sceneY) + ")";
        } else
            downCo = "(" + std::to_string(p.sceneX - 1) + "," + std::to_string(p.sceneY) + ")";

        // up
        if (p.sceneX + 1 >= fieldSize && (p.fieldX == GetRowNum() - 1 || GetColNum(p.fieldX + 1) <= p.fieldY)) {
            upFieldName = "";
            upCo = "";
        } else if (p.sceneX + 1 >= fieldSize) {
            upFieldName = GetField(p.fieldX + 1, p.fieldY).GetName();
            upCo = "(" + std::to_string(0) + "," + std::to_string(p.sceneY) + ")";
        } else {
            upCo = "(" + std::to_string(p.sceneX + 1) + "," + std::to_string(p.sceneY) + ")";
        }
        // left
        if (p.sceneY - 1 < 0 && p.fieldY == 0) {
            leftFieldName = "";
            leftCo = "";
        } else if (p.sceneY - 1 < 0) {
            leftFieldName = GetField(p.fieldX, p.fieldY - 1).GetName();
            leftCo = "(" + std::to_string(p.sceneX) + "," + std::to_string(fieldSize - 1) + ")";
        } else
            leftCo = "(" + std::to_string(p.sceneX) + "," + std::to_string(p.sceneY - 1) + ")";

        // right
        if (p.sceneY + 1 >= fieldSize && p.fieldY == GetColNum(p.fieldX) - 1) {
            rightFieldName = "";
            rightCo = "";
        } else if (p.sceneY + 1 >= fieldSize) {
            rightFieldName = GetField(p.fieldX, p.fieldY + 1).GetName();
            rightCo = "(" + std::to_string(p.sceneX) + "," + std::to_string(0) + ")";
        } else
            rightCo = "(" + std::to_string(p.sceneX) + "," + std::to_string(p.sceneY + 1) + ")";
        // draw the map

        // if left can go
        if (leftFieldName != "") {
            // up
            if (upFieldName != "") {
                TextGen::PrintCenter(upFieldName, maxTerminalLenghth);
                TextGen::PrintCenter(upCo, maxTerminalLenghth);
                TextGen::PrintCenter("up state", maxTerminalLenghth);
                TextGen::PrintCenter("|", maxTerminalLenghth);
                TextGen::PrintCenter("|", maxTerminalLenghth);
                TextGen::PrintCenter("|", maxTerminalLenghth);
            }

            // right
            if (rightFieldName != "") {
                TextGen::PrintThree(leftFieldName, centerFieldName, rightFieldName, maxTerminalLenghth);
                TextGen::PrintThree(leftCo, centerCo, rightCo, maxTerminalLenghth, "-");
                TextGen::PrintThree("left state", "center", "right state", maxTerminalLenghth);
            } else {
                TextGen::PrintTwo(leftFieldName, centerFieldName, maxTerminalLenghth);
                TextGen::PrintTwo(leftCo, centerCo, maxTerminalLenghth, "-");
                TextGen::PrintTwo("left state", "center", maxTerminalLenghth);
            }

            // down
            if (downFieldName != "") {
                TextGen::PrintCenter("|", maxTerminalLenghth);
                TextGen::PrintCenter("|", maxTerminalLenghth);
                TextGen::PrintCenter("|", maxTerminalLenghth);
                TextGen::PrintCenter(downFieldName, maxTerminalLenghth);
                TextGen::PrintCenter(downCo, maxTerminalLenghth);
                TextGen::PrintCenter("down state", maxTerminalLenghth);
            }
        } else {
            // up
            if (upFieldName != "") {
                TextGen::Print(upFieldName);
                TextGen::Print(upCo);
                TextGen::Print("up state");
                TextGen::Print("|");
                TextGen::Print("|");
                TextGen::Print("|");
            }

            if (rightFieldName != "") {
                TextGen::PrintTwo(centerFieldName, rightFieldName, maxTerminalLenghth);
                TextGen::PrintTwo(centerCo, rightCo, maxTerminalLenghth, "-");
                TextGen::PrintTwo("center", "right state", maxTerminalLenghth);
            } else {
                TextGen::Print(centerFieldName);
                TextGen::Print(centerCo);
                TextGen::Print("center");
            }
            // down
            if (downFieldName != "") {
                TextGen::Print("|");
                TextGen::Print("|");
                TextGen::Print("|");
                TextGen::Print(downFieldName);
                TextGen::Print(downCo);
                TextGen::Print("down state");
            }
        }
    } else {
        TextGen::Print<warning>("You has entered an unknown field!");
    }
}
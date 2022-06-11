#include "map/Map.h"
#include "common/Global.h"

/**
 * @brief Get the scene state string and style
 * @param[in] m map
 * @param[in] p position
 * @param[out] stateString return: string representing the state 
 * @param[out] stateStyle return: style to show the state
 */
static void GetSceneState(const Map &m, const Position &p, std::string &stateString, int &stateStyle) {
    Scene s = m.GetScene(p);
    int moneyPoss = s.GetMoneyPossibility();
    int mediPoss = s.GetMedicinePossibility();
    int shopPoss = s.GetShopPossibility();
    int enemyPoss = s.GetEnemyPossibility();
    double moneyRatio, mediRatio, shopRatio, enemyRatio, maxRatio;
    
    if (enemyPoss) {
        // plain
        moneyRatio = double(moneyPoss) / plainMoneyExpect;
        shopRatio = double(shopPoss) / plainShopExpect;
        mediRatio = double(mediPoss) / plainMedicineExpect;
        enemyRatio = double(enemyPoss) / plainEnemyExpect;
        maxRatio = MaxFour(moneyRatio, shopRatio, mediRatio, enemyRatio);
    } else {
        // country
        moneyRatio = double(moneyPoss) / countryMoneyExpect;
        shopRatio = double(shopPoss) / countryShopExpect;
        mediRatio = double(mediPoss) / countryMedicineExpect;
        enemyRatio = 0;
        maxRatio = MaxThree(moneyRatio, shopRatio, mediRatio);
    } 

    /// @attention equality of double is uncertain
    if (maxRatio == moneyRatio) {
        stateString = "Money " + std::to_string(moneyPoss) + "%";
        stateStyle = YELLOW_;
    } else if (maxRatio == shopRatio) {
        stateString = "Shop " + std::to_string(shopPoss) + "%";
        stateStyle = YELLOW_;
    } else if (maxRatio == mediRatio) {
        stateString = "Medicine " + std::to_string(mediPoss) + "%";
        stateStyle = GREEN_;
    } else if (maxRatio == enemyRatio) {
        stateString = "Enemy " + std::to_string(enemyPoss) + "%";
        stateStyle = RED_;
    } else {
        stateString = "Normal";
        stateStyle = 0;
    }
}

Field Map::GetField(const int fieldX, const int fieldY) const {
    return *(fields[fieldX][fieldY]);
}

Scene Map::GetScene(const Position& p) const {
    return fields[p.fieldX][p.fieldY]->GetScene(p.sceneX, p.sceneY);
}

Scene& Map::GetSceneForChange(const Position& p) {
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
void Map::ShowDirection(const Position& p, const string centerString, int centerStyle) const {
    // Get State
    string stateString[4]{"up", "down", "left", "right"};  // up down left right
    int stateStyle[4]{0, 0, 0, 0};                         // up down left right

    // Print Direction
    if (p.fieldX >= 0 && p.fieldX < GetRowNum() && p.fieldY >= 0 && p.fieldY < GetColNum(p.fieldX)) {
        // Field Name
        string centerFieldName{GetField(p.fieldX, p.fieldY).GetName()};
        string leftFieldName{centerFieldName}, rightFieldName{centerFieldName};
        string upFieldName{centerFieldName}, downFieldName{centerFieldName};

        // Coordinate
        string leftCo{""}, rightCo{""}, upCo{""}, downCo{""};
        string centerCo = "(" + std::to_string(p.sceneX) + "," + std::to_string(p.sceneY) + ")";
        Position leftPo, rightPo, upPo, downPo;

        // down
        if (p.sceneX - 1 < 0 && (p.fieldX == 0 || GetColNum(p.fieldX - 1) <= p.fieldY)) {
            downFieldName = "";
            downCo = "";
        } else if (p.sceneX - 1 < 0) {
            downFieldName = GetField(p.fieldX - 1, p.fieldY).GetName();
            downCo = "(" + std::to_string(fieldSize - 1) + "," + std::to_string(p.sceneY) + ")";
            downPo = {p.fieldX - 1, p.fieldY, fieldSize - 1, p.sceneY};
        } else {
            downCo = "(" + std::to_string(p.sceneX - 1) + "," + std::to_string(p.sceneY) + ")";
            downPo = {p.fieldX, p.fieldY, p.sceneX - 1, p.sceneY};
        }
        // up
        if (p.sceneX + 1 >= fieldSize && (p.fieldX == GetRowNum() - 1 || GetColNum(p.fieldX + 1) <= p.fieldY)) {
            upFieldName = "";
            upCo = "";
        } else if (p.sceneX + 1 >= fieldSize) {
            upFieldName = GetField(p.fieldX + 1, p.fieldY).GetName();
            upCo = "(" + std::to_string(0) + "," + std::to_string(p.sceneY) + ")";
            upPo = {p.fieldX + 1, p.fieldY, 0, p.sceneY};
        } else {
            upCo = "(" + std::to_string(p.sceneX + 1) + "," + std::to_string(p.sceneY) + ")";
            upPo = {p.fieldX, p.fieldY, p.sceneX + 1, p.sceneY};
        }
        // left
        if (p.sceneY - 1 < 0 && p.fieldY == 0) {
            leftFieldName = "";
            leftCo = "";
        } else if (p.sceneY - 1 < 0) {
            leftFieldName = GetField(p.fieldX, p.fieldY - 1).GetName();
            leftCo = "(" + std::to_string(p.sceneX) + "," + std::to_string(fieldSize - 1) + ")";
            leftPo = {p.fieldX, p.fieldY - 1, p.sceneX, fieldSize - 1};
        } else {
            leftCo = "(" + std::to_string(p.sceneX) + "," + std::to_string(p.sceneY - 1) + ")";
            leftPo = {p.fieldX, p.fieldY, p.sceneX, p.sceneY - 1};
        }
        // right
        if (p.sceneY + 1 >= fieldSize && p.fieldY == GetColNum(p.fieldX) - 1) {
            rightFieldName = "";
            rightCo = "";
        } else if (p.sceneY + 1 >= fieldSize) {
            rightFieldName = GetField(p.fieldX, p.fieldY + 1).GetName();
            rightCo = "(" + std::to_string(p.sceneX) + "," + std::to_string(0) + ")";
            rightPo = {p.fieldX, p.fieldY + 1, p.sceneX, 0};
        } else {
            rightCo = "(" + std::to_string(p.sceneX) + "," + std::to_string(p.sceneY + 1) + ")";
            rightPo = {p.fieldX, p.fieldY, p.sceneX, p.sceneY + 1};
        }
        // draw the map

        // if left can go
        if (leftFieldName != "") {
            // up
            if (upFieldName != "") {
                GetSceneState(*this, upPo, stateString[0], stateStyle[0]);
                TextGen::PrintCenter(upFieldName, maxTerminalLenghth);
                TextGen::PrintCenter(upCo, maxTerminalLenghth);
                TextGen::PrintCenter(stateString[0], maxTerminalLenghth, stateStyle[0]);
                TextGen::PrintCenter("|", maxTerminalLenghth);
                TextGen::PrintCenter("|", maxTerminalLenghth);
                TextGen::PrintCenter("|", maxTerminalLenghth);
            }

            // right
            if (rightFieldName != "") {
                GetSceneState(*this, leftPo, stateString[2], stateStyle[2]);
                GetSceneState(*this, rightPo, stateString[3], stateStyle[3]);
                TextGen::PrintThree(leftFieldName, centerFieldName, rightFieldName, maxTerminalLenghth);
                TextGen::PrintThree(leftCo, centerCo, rightCo, maxTerminalLenghth, "-");
                TextGen::PrintThree(stateString[2], centerString, stateString[3], maxTerminalLenghth, " ",
                                    stateStyle[2], centerStyle, stateStyle[3]);
            } else {
                GetSceneState(*this, leftPo, stateString[2], stateStyle[2]);
                TextGen::PrintTwo(leftFieldName, centerFieldName, maxTerminalLenghth);
                TextGen::PrintTwo(leftCo, centerCo, maxTerminalLenghth, "-");
                TextGen::PrintTwo(stateString[2], centerString, maxTerminalLenghth, " ", stateStyle[2], centerStyle);
            }

            // down
            if (downFieldName != "") {
                GetSceneState(*this, downPo, stateString[1], stateStyle[1]);
                TextGen::PrintCenter("|", maxTerminalLenghth);
                TextGen::PrintCenter("|", maxTerminalLenghth);
                TextGen::PrintCenter("|", maxTerminalLenghth);
                TextGen::PrintCenter(downFieldName, maxTerminalLenghth);
                TextGen::PrintCenter(downCo, maxTerminalLenghth);
                TextGen::PrintCenter(stateString[1], maxTerminalLenghth, stateStyle[1]);
            }
        } else {
            // up
            if (upFieldName != "") {
                GetSceneState(*this, upPo, stateString[0], stateStyle[0]);
                TextGen::Print(upFieldName);
                TextGen::Print(upCo);
                TextGen::Print(stateString[0], "\n", stateStyle[0]);
                TextGen::Print("|");
                TextGen::Print("|");
                TextGen::Print("|");
            }

            if (rightFieldName != "") {
                GetSceneState(*this, rightPo, stateString[3], stateStyle[3]);
                TextGen::PrintTwo(centerFieldName, rightFieldName, maxTerminalLenghth);
                TextGen::PrintTwo(centerCo, rightCo, maxTerminalLenghth, "-");
                TextGen::PrintTwo(centerString, stateString[3], maxTerminalLenghth, " ", centerStyle, stateStyle[3]);
            } else {
                TextGen::Print(centerFieldName);
                TextGen::Print(centerCo);
                TextGen::Print(centerString, "\n", centerStyle);
            }
            // down
            if (downFieldName != "") {
                GetSceneState(*this, downPo, stateString[1], stateStyle[1]);
                TextGen::Print("|");
                TextGen::Print("|");
                TextGen::Print("|");
                TextGen::Print(downFieldName);
                TextGen::Print(downCo);
                TextGen::Print(stateString[1], "\n", stateStyle[1]);
            }
        }
    } else {
        TextGen::Print<warning>("您进入了无人之境!");
    }
}
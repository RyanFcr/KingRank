#include "role/King.h"
#include <string>
using std::to_string;

void King::ShowMap(const Map& m) const {
    TextGen::PrintDirection(m, position);
}

void King::GoUp(const Map& m) {
    position.GoUp();
    if (!(m.IsValidPosition(position))) {
        position.GoDown();
        TextGen::Print<warning>("Can't go up!");
    } else
        TriggerEvent(m);
}

void King::GoDown(const Map& m) {
    position.GoDown();
    if (!(m.IsValidPosition(position))) {
        position.GoUp();
        TextGen::Print<warning>("Can't go down!");
    } else
        TriggerEvent(m);
}

void King::GoLeft(const Map& m) {
    position.GoLeft();
    if (!(m.IsValidPosition(position))) {
        position.GoRight();
        TextGen::Print<warning>("Can't go left!");
    } else
        TriggerEvent(m);
}

void King::GoRight(const Map& m) {
    position.GoRight();
    if (!(m.IsValidPosition(position))) {
        position.GoLeft();
        TextGen::Print<warning>("Can't go right!");
    } else
        TriggerEvent(m);
}

void King::TriggerEvent(const Map& m) {
    int totalMoney = 0, totalMedicineNumber = 0;

    // Get Money
    while (rand() % 100 < m.GetScene(position).GetMoneyPossibility()) {
        totalMoney += money;
    }
    if (totalMoney > 0) {
        TextGen::Print<reward>("Congratulation! You get " + to_string(totalMoney) + " Kin!");
        IncreaseMoney(totalMoney);
    }
}
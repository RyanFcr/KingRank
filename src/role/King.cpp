#include "role/King.h"
#include <string>
#include "item/ItemGen.h"
using std::to_string;

void King::ShowMap(const Map& m) const {
    TextGen::PrintDirection(m, position);
}

void King::ShowMoney() const {
    TextGen::PrintMoney(money);
}

void King::ShowSkill() const {
    TextGen::PrintSkill(attackSkills, supportSkills);
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
    int inputInt;
    int totalMoney = 0, totalMedicineNumber = 0;
    Scene s = m.GetScene(position);
    string medicineName = s.GetMedicineName();

    // Get Money
    while (rand() % 100 < s.GetMoneyPossibility()) {
        totalMoney += s.GetMoney();
    }
    if (totalMoney > 0) {
        TextGen::Print<reward>("Congratulation! You get " + to_string(totalMoney) + " Kin!");
        IncreaseMoney(totalMoney);
    }

    // Get Medicine
    while (rand() % 100 < s.GetMedicinePossibility()) {
        totalMedicineNumber += 1;
    }
    if (totalMedicineNumber > 0) {
        TextGen::Print<reward>("Lucky! You meet with " + to_string(totalMedicineNumber) + " " + medicineName + "!");
        TextGen::Print<request>("How many do you need?");
        TextGen::Print("Pay attention to your bag! Weight limit: ", "");
        TextGen::Print<warning>(to_string(GetBag().GetWeightLimit()), ", ");
        TextGen::Print("Current weight: ", "");
        TextGen::Print<buff>(to_string(GetBag().GetCurWeight()), ", ");
        TextGen::Print(medicineName + " weight: ", "");
        TextGen::Print<reward>(to_string(ItemGen::GetMedicine(medicineName).GetWeight()));
        inputInt = TextGen::InputInt();
        while (inputInt < 0 || inputInt > totalMedicineNumber || !InsertMedicine(medicineName, inputInt)) {
            TextGen::Print<warning>("Invalid input!");
            inputInt = TextGen::InputInt();
        }
        if (inputInt > 0) {
            TextGen::Print<reward>("You pick up " + to_string(inputInt) + " " + medicineName + "!");
        } else
            TextGen::Print<warning>("You ignore " + medicineName + "!");
    }
}
#include "event/EventSystem.h"
#include "item/ItemGen.h"
#include "role/EnemyGen.h"
#include "combat/CombatSystem.h"
#include "common/Global.h"

#include <string>
using std::to_string;

void EventSystem::TriggerEvent(King& king, const Map& m) {
    int inputInt;
    int totalMoney = 0, totalMedicineNumber = 0;
    Scene s = m.GetScene(king.GetPosition());
    string medicineName = s.GetMedicineName();

    // Get Money
    while (rand() % 100 < s.GetMoneyPossibility()) {
        totalMoney += s.GetMoney();
    }
    if (totalMoney > 0) {
        TextGen::Print<reward>("Congratulation! You get " + to_string(totalMoney) + " Kin!");
        king.IncreaseMoney(totalMoney);
    }

    // Get Medicine
    while (rand() % 100 < s.GetMedicinePossibility()) {
        totalMedicineNumber += 1;
    }
    if (totalMedicineNumber > 0) {
        TextGen::Print<reward>("Lucky! You meet with " + to_string(totalMedicineNumber) + " " + medicineName + "!");
        TextGen::Print<request>("How many do you need?");
        TextGen::Print("Pay attention to your bag! Weight limit: ", "");
        TextGen::Print<warning>(to_string(king.GetBag().GetWeightLimit()), ", ");
        TextGen::Print("Current weight: ", "");
        TextGen::Print<buff>(to_string(king.GetBag().GetCurWeight()), ", ");
        TextGen::Print(medicineName + " weight: ", "");
        TextGen::Print<reward>(to_string(ItemGen::GetMedicine(medicineName).GetWeight()));
        inputInt = TextGen::InputInt();
        while (inputInt < 0 || inputInt > totalMedicineNumber || !king.InsertMedicine(medicineName, inputInt)) {
            TextGen::Print<warning>("Invalid input!");
            inputInt = TextGen::InputInt();
        }
        if (inputInt > 0) {
            TextGen::Print<reward>("You pick up " + to_string(inputInt) + " " + medicineName + "!");
        } else
            TextGen::Print<warning>("You ignore " + medicineName + "!");
    }

    // Combat
    if (s.GetEnemyName() != "" && rand() % 100 <= s.GetEnemyPossibility()) {
        Enemy e = EnemyGen::enemys.at(s.GetEnemyName());
        TextGen::Print<warning>("You meet with " + e.GetName() + "!");
        CombatSystem::Combat(king, e);
    }
}
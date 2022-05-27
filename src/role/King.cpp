#include "role/King.h"
#include <string>
#include "combat/CombatSystem.h"
#include "item/ItemGen.h"
#include "role/RoleGen.h"
#include "role/EnemyGen.h"

using std::to_string;

void King::ShowMap(const Map& m) const {
    TextGen::PrintDirection(m, position);
}

void King::ShowMoney() const {
    TextGen::PrintMoney(money);
}

void King::ShowSkills() const {
    TextGen::PrintSkills(attackSkillNames, supportSkillNames);
}

void King::ShowAttackSkills() const {
    TextGen::PrintAttackSkills(attackSkillNames);
}

void King::ShowSupportSkills() const {
    TextGen::PrintSupportSkills(supportSkillNames);
}

void King::ShowState() const {
    TextGen::Print("Name: " + GetName());
    TextGen::Print("Level: " + to_string(GetLevel()));
    TextGen::Print("Exp: " + to_string(GetExperience()) + "/" + to_string(GetLevelUpExperience()));
    TextGen::Print("HP: " + to_string(GetHP()) + "/" + to_string(GetMaxHP()));
    TextGen::Print("MP: " + to_string(GetMP()) + "/" + to_string(GetMaxMP()));
    TextGen::Print("Attack:" + to_string(GetAttack()));
    TextGen::Print("Country: " + GetCountryName());
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

    // Combat
    if (s.GetEnemyName() != "" && rand() % 100 <= s.GetEnemyPossibility()) {
        Enemy e = EnemyGen::enemys.at(s.GetEnemyName());
        TextGen::Print<warning>("You meet with " + e.GetName() + "!");
        CombatSystem::Combat(*this, e);
    }
}

void King::Resurrect() {
    SetPosition({territoryPosition.fieldX, territoryPosition.fieldY, rand() % fieldSize, rand() % fieldSize});
    SetMoney(0);
    SetHP(maxHP);
    SetMP(maxMP);
    bag.DiscardAll();
}

void King::IncreaseExperience(int experience_) {
    experience += experience_;
    if (experience >= GetLevelUpExperience()) {
        IncreaseLevel(1);
        SetExperience(0);

        TextGen::Print("Level up! Now your level is ", "");
        TextGen::Print<buff>(to_string(GetLevel()));

        switch (level) {
            case 2:
                IncreaseMaxHP(100);
                break;
            case 3:
                IncreaseAttack(2);
                break;
            case 4:
                IncreaseMaxMP(50);
                break;
            case 5:
                IncreaseMaxHP(200);
                break;
            case 6:
                IncreaseAttack(2);
                break;
            case 7:
                IncreaseMaxHP(300);
                break;
            case 8:
                IncreaseMaxMP(100);
                break;
            case 9:
                IncreaseAttack(5);
                break;
            case 10:
                IncreaseMaxHP(300);
                IncreaseMaxMP(50);
                break;
            default:
                break;
        }

        SetHP(GetMaxHP());
        SetMP(GetMaxMP());
    }
}
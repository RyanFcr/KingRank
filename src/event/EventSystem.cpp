#include "event/EventSystem.h"
#include "combat/CombatSystem.h"
#include "common/Global.h"
#include "item/ItemGen.h"
#include "role/EnemyGen.h"
#include "role/NpcGen.h"

#include <string>
using std::to_string;

void EventSystem::TriggerEvent(King& king, const Map& m) {
    Scene s = m.GetScene(king.GetPosition());
    MoneyEvent(king, s);
    MedicineEvent(king, s);
    CombatEvent(king, s);
    NpcEvent(king, s);
}
/**
 * @brief Npc对话事件
 * 
 * @param king 
 * @param s 
 */
void EventSystem::NpcEvent(King& king, const Scene& s) {
    Position kingPosition = king.GetPosition();

    map<Position, Npc, decltype(PositionCmp)*>::iterator it_find;
    it_find = NpcGen::Npcs.find(kingPosition);
    if(it_find!=NpcGen::Npcs.end())
    {
        Npc npc = NpcGen::Npcs[kingPosition];
        npc.NpcSpeak("0");
        string input = TextGen::Input();
        npc.NpcSpeak(input);
        // string statement =
        // TextGen::Print<reward>()
    }else
    {
        return;
    }
}
void EventSystem::MoneyEvent(King& king, const Scene& s) {
    int totalMoney = 0;

    // Get Money
    while (rand() % 100 < s.GetMoneyPossibility()) {
        totalMoney += s.GetMoney();
    }
    if (totalMoney > 0) {
        TextGen::Print<reward>("恭喜! 您获得了 " + to_string(totalMoney) + " Kin!");
        king.IncreaseMoney(totalMoney);
    }
}

void EventSystem::MedicineEvent(King& king, const Scene& s) {
    int totalMedicineNumber = 0;
    int inputInt;
    string medicineName = s.GetMedicineName();

    // Get Medicine
    while (rand() % 100 < s.GetMedicinePossibility()) {
        totalMedicineNumber += 1;
    }
    if (totalMedicineNumber > 0) {
        TextGen::Print<reward>("哇，在您面前出现了 " + to_string(totalMedicineNumber) + " " + medicineName + "!");
        TextGen::Print<request>("您想要几个?请输入您想要的数量");
        TextGen::Print("请注意背包容量! 最大限额: ", "");
        TextGen::Print<warning>(to_string(king.GetBag().GetWeightLimit()), ", ");
        TextGen::Print("现在的容量为: ", "");
        TextGen::Print<buff>(to_string(king.GetBag().GetCurWeight()), ", ");
        TextGen::Print(medicineName + " 占容: ", "");
        TextGen::Print<reward>(to_string(ItemGen::GetMedicine(medicineName).GetWeight()));
        inputInt = TextGen::InputInt();
        while (inputInt < 0 || inputInt > totalMedicineNumber || !king.InsertMedicine(medicineName, inputInt)) {
            TextGen::Print<warning>("请输入正确的指令!");
            inputInt = TextGen::InputInt();
        }
        if (inputInt > 0) {
            TextGen::Print<reward>("您捡起了 " + to_string(inputInt) + " " + medicineName + "!");
        } else
            TextGen::Print<warning>("这 " + medicineName + " 不要也罢!");
    }
}

void EventSystem::CombatEvent(King& king, const Scene& s) {
    // Combat
    if (s.GetEnemyName() != "" && rand() % 100 <= s.GetEnemyPossibility()) {
        Enemy e = EnemyGen::enemys.at(s.GetEnemyName());
        TextGen::Print<warning>("突然从草丛杀出一个黑影，糟糕，您遇到了 " + e.GetName() + "!");
        CombatSystem::Combat(king, e);
    }
}
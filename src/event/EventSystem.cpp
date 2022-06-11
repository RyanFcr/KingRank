#include "event/EventSystem.h"
#include "combat/CombatSystem.h"
#include "common/Global.h"
#include "item/ItemGen.h"
#include "role/EnemyGen.h"
#include "role/NpcGen.h"
#include "shop/Shop.h"

#include <string>
using std::to_string;

void EventSystem::TriggerEvent(King& king, Map& m) {
    Scene& s = m.GetSceneForChange(king.GetPosition());
    MoneyEvent(king, s);
    MedicineEvent(king, s);
    ShopEvent(king, s);
    CombatEvent(king, s);
    NpcEvent(king, s);
}
/**
 * @brief Npc对话事件
 * 
 * @param king 
 * @param s 
 */
void EventSystem::NpcEvent(King& king, Scene& s) {
    Position kingPosition = king.GetPosition();

    map<Position, Npc, decltype(PositionCmp)*>::iterator it_find;
    it_find = NpcGen::Npcs.find(kingPosition);
    if(it_find!=NpcGen::Npcs.end()) {
        Npc npc = NpcGen::Npcs[kingPosition];
        npc.NpcSpeak("0");
        string input = TextGen::Input();
        npc.NpcSpeak(input);
        // string statement =
        // TextGen::Print<reward>()
    } else {
        return;
    }
}

void EventSystem::MoneyEvent(King& king, Scene& s) {
    int totalMoney = 0;

    // Get Money
    while (rand() % 100 < s.GetMoneyPossibility()) {
        totalMoney += s.GetMoney();
    }
    if (totalMoney > 0) {
        TextGen::Print<reward>("恭喜! 您获得了 " + to_string(totalMoney) + " Kin!");
        king.IncreaseMoney(totalMoney);
    }

    // Lower Possibility and Money according to totalMoney
    if (totalMoney)
        s.SetMoneyPossibility(s.GetMoney() / double(totalMoney) / 1.5 * s.GetMoneyPossibility());
}

void EventSystem::MedicineEvent(King& king, Scene& s) {
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
            TextGen::Print<warning>("请输入正确的整数!");
            inputInt = TextGen::InputInt();
        }
        if (inputInt > 0) {
            TextGen::Print<reward>("您捡起了 " + to_string(inputInt) + " " + medicineName + "!");

            // Lower Possibility
            s.SetMedicinePossibility(s.GetMedicinePossibility() / double(inputInt) / 1.5);
        } else
            TextGen::Print<warning>("这 " + medicineName + " 不要也罢!");
    }
}

void EventSystem::CombatEvent(King& king, Scene& s) {
    // Combat
    if (s.GetEnemyName() != "" && rand() % 100 <= s.GetEnemyPossibility()) {
        Enemy e = EnemyGen::enemys.at(s.GetEnemyName());
        TextGen::Print<warning>("突然从草丛杀出一个黑影，糟糕，您遇到了 " + e.GetName() + "!");
        CombatSystem::Combat(king, e);
    }
}

void EventSystem::ShopEvent(King& king, Scene& s) {
    int inputInt;
    int itemNum;
    int offset;
    int price, weight;
    std::string itemName;

    // Shop
    if (rand() % 100 <= s.GetShopPossibility()) {
        TextGen::Print<YELLOW_>("你遇到了一个商店!");
        Shop shop;
        while (1) {
            shop.ShowShopItems();
            itemNum = shop.GetItemNum();
            offset = shop.GetMedicineNum();
            TextGen::Print<request>("请选择你要买的商品(输入-1退出商店)");
            TextGen::Print("您的金币数量: ", "");
            TextGen::Print<YELLOW_>(to_string(king.GetMoney()) + " Kin", ", ");
            TextGen::Print("背包当前容量: ", "");
            TextGen::Print<GREEN_>(to_string(king.GetBag().GetCurWeight()), ", ");
            TextGen::Print("最大限额: ", "");
            TextGen::Print<RED_>(to_string(king.GetBag().GetWeightLimit()));
            inputInt = TextGen::InputInt();
            while (inputInt < -1 || inputInt > itemNum) {
                TextGen::Print<warning>("请输入正确的整数!");
                inputInt = TextGen::InputInt();
            }
            if (inputInt == -1) {
                break;
            } else {
                if (inputInt < offset) {
                    // medicine
                    itemName = shop.GetMedicineByIndex(inputInt);
                    Medicine medicine = ItemGen::GetMedicine(itemName);
                    price = medicine.GetPrice();
                    weight = medicine.GetWeight();
                    if (price > king.GetMoney()) {
                        TextGen::Print<warning>("您没有足够的金币!");
                    } else if (weight + king.GetBag().GetCurWeight() > king.GetBag().GetWeightLimit()) {
                        TextGen::Print<warning>("您没有足够的背包容量!");
                    } else {
                        king.IncreaseMoney(-price);
                        king.InsertMedicine(itemName, 1);
                        shop.SellOutMedicineByIndex(inputInt);
                        TextGen::Print<buff>("购买成功!");
                    }
                } else {
                    // weapon
                    inputInt -= offset;
                    itemName = shop.GetWeaponByIndex(inputInt);
                    Weapon weapon = ItemGen::GetWeapon(itemName);
                    price = weapon.GetPrice();
                    weight = weapon.GetWeight();
                    if (price > king.GetMoney()) {
                        TextGen::Print<warning>("您没有足够的金币!");
                    } else if (weight + king.GetBag().GetCurWeight() > king.GetBag().GetWeightLimit()) {
                        TextGen::Print<warning>("您没有足够的背包容量!");
                    } else {
                        king.IncreaseMoney(-price);
                        king.InsertWeapon(weapon);
                        shop.SellOutWeaponByIndex(inputInt);
                        TextGen::Print<buff>("购买成功!");
                    }
                }
            }
            TextGen::Print("");
        }
        TextGen::Print("欢迎下次光临!");
    }
}
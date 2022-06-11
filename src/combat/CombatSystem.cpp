#include "combat/CombatSystem.h"
#include "common/Config.h"
#include "item/ItemGen.h"
#include "role/Enemy.h"
#include "role/King.h"
#include "text/TextGen.h"

#include <string>
using std::string;
using std::to_string;

#include <iostream>
using std::cout;

static bool CheckCombatFinish(const King& king, const Enemy& enemy) {
    return king.GetHP() <= 0 || enemy.GetHP() <= 0;
}

void CombatSystem::Combat(King& king, Enemy& enemy, vector<Mission>& kingMissions) {
    bool finish = false;

    TextGen::Print<warning>("战斗正式开始!");
    while (!finish) {
        finish = CombatProcess(king, enemy);
    }
    if (king.GetHP() <= 0) {
        CombatLose(king);
    } else if (king.GetHP() > 0 && enemy.GetHP() <= 0) {
        CombatWin(king, enemy);
        vector<Mission>::iterator it = kingMissions.begin();
        while (it != kingMissions.end()) {
            if (it->GetTargetName() == enemy.GetName()) {
                it->IncreaseCurrent();
                if (it->IsFinish()) {
                    TextGen::Print<YELLOW_>("完成任务，获得奖励！");
                    TextGen::Print<YELLOW_>("获得经验" + it->GetExperience());
                    TextGen::Print<YELLOW_>("获得金币" + it->GetReward());
                    king.IncreaseExperience(it->GetExperience());
                    king.IncreaseMoney(it->GetReward());
                    kingMissions.erase(it);
                }
            }
            it++;
        }
    }
}

bool CombatSystem::CombatProcess(King& king, Enemy& enemy) {
    bool escape = false;

    if (rand() % 100 <= kingFirst) {
        KingTurn(king, enemy, escape);
        if (CheckCombatFinish(king, enemy) || escape)
            return true;
        EnemyTurn(king, enemy);
        if (CheckCombatFinish(king, enemy))
            return true;
    } else {
        EnemyTurn(king, enemy);
        if (CheckCombatFinish(king, enemy))
            return true;
        KingTurn(king, enemy, escape);
        if (CheckCombatFinish(king, enemy) || escape)
            return true;
    }

    return false;
}

void CombatSystem::CombatWin(King& king, Enemy& enemy) {
    int experienceVal = enemy.GetExperienceVal();
    int moneyVal = enemy.GetMoneyVal();
    TextGen::Print("恭喜国王获得胜利! 你获得了 ", "");
    TextGen::Print<buff>(to_string(experienceVal) + " EXP", " and ");
    TextGen::Print<reward>(to_string(moneyVal) + " Kin", "!\n");
    king.IncreaseMoney(moneyVal);
    king.IncreaseExperience(experienceVal);
}

void CombatSystem::CombatLose(King& king) {
    TextGen::Print<warning>("年轻的国王战死沙场!");
    TextGen::Print<warning>("您即将在您的领土复活，但是背包里的所有东西都被影之一族的族人偷走了~");
    king.Resurrect();
}

void CombatSystem::KingTurn(King& king, Enemy& enemy, bool& escape) {
    string input;
    int inputInt;
    int MPCost, damageVal, HPVal, MPVal;

    escape = false;
    while (1) {
        TextGen::Print<request>("请输入战斗指令(escape/attack/support/state/bag/medicine/equip)");
        input = TextGen::Input();
        if (input == "escape") {
            if (king.GetLevel() < 5 || rand() % 100 <= escapePossibility) {
                TextGen::Print<buff>("溜了溜了，拜拜了您");
                escape = true;
                break;
            } else {
                TextGen::Print<warning>("逃跑失败！留下来！");
                break;
            }
        } else if (input == "attack") {
            TextGen::Print<request>("您想发动什么技能？");
            king.ShowAttackSkills();
            inputInt = TextGen::InputInt();
            TextGen::Print<request>("请输入技能的序号");
            if (king.HasAttackSkillByIndex(inputInt)) {
                const AttackSkill& attackSkill = king.GetAttackSkillByIndex(inputInt);
                TextGen::Print("您使出了 ", "");
                TextGen::Print<warning>(attackSkill.GetName(), "!\n");
                MPCost = attackSkill.GetMPCost();
                damageVal = attackSkill.GetDamageValue() * king.GetAttack();
                king.IncreaseMP(-MPCost);
                enemy.IncreaseHP(-damageVal);
                king.AbraseCurrentWeapon();
                TextGen::Print("您消耗了 ", "");
                TextGen::Print<BLUE_>(to_string(MPCost), " MP! ");
                TextGen::Print("您发动了进攻，对他造成了 ", "");
                TextGen::Print<RED_>(to_string(damageVal), " 伤害!\n");
                break;
            } else {
                TextGen::Print<warning>("请输入正确的指令!");
            }
        } else if (input == "support") {
            TextGen::Print<request>("您想发动什么技能？请输入技能的序号");
            king.ShowSupportSkills();
            inputInt = TextGen::InputInt();
            if (king.HasSupportSkillByIndex(inputInt)) {
                const SupportSkill& supportSkill = king.GetSupportSkillByIndex(inputInt);
                TextGen::Print("您使出了 ", "");
                TextGen::Print<buff>(supportSkill.GetName(), "!\n");
                MPCost = supportSkill.GetMPCost();
                HPVal = supportSkill.GetHPValue() * king.GetMaxHP() / 100;
                if (HPVal + king.GetHP() >= king.GetMaxHP())
                    HPVal = king.GetMaxHP() - king.GetHP();
                king.IncreaseMP(-MPCost);
                king.IncreaseHP(HPVal);
                TextGen::Print("您消耗了 ", "");
                TextGen::Print<BLUE_>(to_string(MPCost), " MP! ");
                TextGen::Print("您恢复了 ", "");
                TextGen::Print<RED_>(to_string(HPVal), " HP!\n");
                break;
            } else {
                TextGen::Print<warning>("请输入正确的指令!");
            }
        } else if (input == "state") {
            king.ShowState();
        } else if (input == "bag") {
            king.ShowBag();
        } else if (input == "medicine") {
            if (king.GetBag().HasNoMedicine()) {
                TextGen::Print<warning>("您没有药！药丸了！");
            } else {
                TextGen::Print<request>("您想使用什么药?请输入想使用药品的序号");
                king.ShowMedicine();
                inputInt = TextGen::InputInt();
                if (king.GetBag().HasMedicineByIndex(inputInt)) {
                    const string medicineName = king.GetBag().GetMedicineNameByIndex(inputInt);
                    const Medicine& medicine = ItemGen::GetMedicine(medicineName);
                    HPVal = medicine.GetHPValue() * king.GetMaxHP() / 100;
                    MPVal = medicine.GetMPValue() * king.GetMaxMP() / 100;
                    if (HPVal + king.GetHP() >= king.GetMaxHP())
                        HPVal = king.GetMaxHP() - king.GetHP();
                    if (MPVal + king.GetMP() >= king.GetMaxMP())
                        MPVal = king.GetMaxMP() - king.GetMP();
                    king.IncreaseMP(MPVal);
                    king.IncreaseHP(HPVal);
                    king.DiscardItem(medicineName, 1);
                    TextGen::Print("您使用了 " + medicineName);
                    TextGen::Print("您恢复了 ", "");
                    TextGen::Print<BLUE_>(to_string(MPVal), " MP! ");
                    TextGen::Print("您恢复了 ", "");
                    TextGen::Print<RED_>(to_string(HPVal), " HP!\n");
                    break;
                } else {
                    TextGen::Print<warning>("请输入正确的指令!");
                }
            }
        } else if (input == "equip") {
            king.EquipWeapon();
        } else
            TextGen::Print<warning>("请输入正确的指令!");
    }
}

void CombatSystem::EnemyTurn(King& king, Enemy& enemy) {
    int MPCost, damageVal;

    const AttackSkill& attackSkill = enemy.GetRandomAttackSkill();
    MPCost = attackSkill.GetMPCost();
    damageVal = attackSkill.GetDamageValue() * enemy.GetAttack();

    enemy.IncreaseMP(-MPCost);
    king.IncreaseHP(-damageVal);

    TextGen::Print("敌人使出了 ", "");
    TextGen::Print<warning>(attackSkill.GetName(), "!\n");
    TextGen::Print("您遭受了 ", "");
    TextGen::Print<RED_>(to_string(damageVal), " 伤害!\n");
}
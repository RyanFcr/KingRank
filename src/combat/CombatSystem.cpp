#include "combat/CombatSystem.h"
#include "common/Config.h"
#include "role/Enemy.h"
#include "role/King.h"
#include "text/TextGen.h"

#include <string>
using std::string;
using std::to_string;

static bool CheckCombatFinish(const King& king, const Enemy& enemy) {
    return king.GetHP() <= 0 || enemy.GetHP() <= 0;
}

void CombatSystem::Combat(King& king, Enemy& enemy) {
    bool finish = false;

    TextGen::Print<warning>("Combat Start!");
    while (!finish) {
        finish = CombatProcess(king, enemy);
    }
    if (king.GetHP() <= 0) {
        CombatLose(king);
    } else if (king.GetHP() > 0 && enemy.GetHP() <= 0) {
        CombatWin(king, enemy);
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
    TextGen::Print("Congratulations, King! You get ", "");
    TextGen::Print<buff>(to_string(experienceVal) + " EXP", " and ");
    TextGen::Print<reward>(to_string(moneyVal) + " Kin", "!\n");
}

void CombatSystem::CombatLose(King& king) {
    TextGen::Print<warning>("Massacred!");
    TextGen::Print<warning>("You wil resurrect in your territory, BUT you will lose all your money and items!");
    king.Resurrect();
}

void CombatSystem::KingTurn(King& king, Enemy& enemy, bool& escape) {
    string input;
    int MPCost, damageVal;

    escape = false;
    while (1) {
        input = TextGen::Input();
        if (input == "escape") {
            if (king.GetLevel() < 5 || rand() % 100 <= escapePossibility) {
                TextGen::Print<buff>("Escape Success!");
                escape = true;
                break;
            } else {
                TextGen::Print<warning>("Escape Fail!");
                break;
            }
        } else if (input == "attack") {
            TextGen::Print<request>("Which skill do your want to use?");
            king.ShowAttackSkills();
            input = TextGen::Input();
            if (king.HasAttackSkill(input)) {
                TextGen::Print("You use ", "");
                TextGen::Print<warning>(input, "!\n");
                MPCost = king.GetAttackSkill(input).GetMPCost();
                damageVal = king.GetAttackSkill(input).GetDamageValue() * king.GetAttack();
                king.IncreaseMP(-MPCost);
                enemy.IncreaseHP(-damageVal);
                TextGen::Print("You consume ", "");
                TextGen::Print<BLUE_>(to_string(MPCost), " MP! ");
                TextGen::Print("You cause ", "");
                TextGen::Print<RED_>(to_string(damageVal), " damage!\n");
            } else {
                TextGen::Print<warning>("Invalid input!");
            }
        } else if (input == "support") {
            /// @todo
        } else {
            TextGen::Print<warning>("Invalid input!");
        }
    }
}

void CombatSystem::EnemyTurn(King& king, Enemy& enemy) {
    int MPCost, damageVal;
    
    const AttackSkill& attackSkill = enemy.GetRandomAttackSkill();
    MPCost = attackSkill.GetMPCost();
    damageVal = attackSkill.GetDamageValue() * enemy.GetAttack();

    enemy.IncreaseMP(-MPCost);
    king.IncreaseHP(-damageVal);

    TextGen::Print("Enemy uses ", "");
    TextGen::Print<warning>(attackSkill.GetName(), "!\n");
    TextGen::Print("You suffer ", "");
    TextGen::Print<RED_>(to_string(damageVal), " damage!\n");
}
#include "role/King.h"
#include <string>

using std::to_string;

void King::ShowMap(const Map& m) const {
    m.ShowDirection(position);
}

void King::ShowMoney() const {
    TextGen::Print<reward>("Kin: " + to_string(money));
}

void King::ShowSkills() const {
    ShowAttackSkills();
    ShowSupportSkills();
}

void King::ShowAttackSkills() const {
    /// @attention too long string!
    TextGen::Print<warning>("进攻技能:");
    if (attackSkillNames.size() == 0) {
        TextGen::Print("无", "");
    } else {
        for (size_t i = 0; i < attackSkillNames.size(); i++) {
            TextGen::Print(to_string(int(i)) + ". " + attackSkillNames[i], " ");
        }
    }
    TextGen::Print("");
}

void King::ShowSupportSkills() const {
    /// @attention too long string!
    TextGen::Print<buff>("辅助技能:");
    if (supportSkillNames.size() == 0) {
        TextGen::Print("空", "");
    } else {
        for (size_t i = 0; i < supportSkillNames.size(); i++) {
            TextGen::Print(to_string(int(i)) + ". " + supportSkillNames[i], " ");
        }
    }
    TextGen::Print("");
}

void King::ShowState() const {
    TextGen::Print("Name: " + GetName());
    TextGen::Print("Level: " + to_string(GetLevel()));
    TextGen::Print("Exp: " + to_string(GetExperience()) + "/" + to_string(GetLevelUpExperience()));
    TextGen::Print("HP: " + to_string(GetHP()) + "/" + to_string(GetMaxHP()));
    TextGen::Print("MP: " + to_string(GetMP()) + "/" + to_string(GetMaxMP()));
    TextGen::Print("Attack: " + to_string(GetAttack()));
    TextGen::Print("Country: " + GetCountryName());
}

bool King::GoUp(const Map& m) {
    position.GoUp();
    if (!(m.IsValidPosition(position))) {
        position.GoDown();
        TextGen::Print<warning>("Can't go up!");
        return false;
    } else
        return true;
}

bool King::GoDown(const Map& m) {
    position.GoDown();
    if (!(m.IsValidPosition(position))) {
        position.GoUp();
        TextGen::Print<warning>("Can't go down!");
        return false;
    } else
        return true;
}

bool King::GoLeft(const Map& m) {
    position.GoLeft();
    if (!(m.IsValidPosition(position))) {
        position.GoRight();
        TextGen::Print<warning>("Can't go left!");
        return false;
    } else
        return true;
}

bool King::GoRight(const Map& m) {
    position.GoRight();
    if (!(m.IsValidPosition(position))) {
        position.GoLeft();
        TextGen::Print<warning>("Can't go right!");
        return false;
    } else
        return true;
}

void King::GoHome(const Map& m) {
    if (position.fieldX == territoryPosition.fieldX && position.fieldY == territoryPosition.fieldY) {
        TextGen::Print<warning>("您已经在您的国家了!");
        return;
    }

    position.fieldX = territoryPosition.fieldX;
    position.fieldY = territoryPosition.fieldY;
    position.sceneX = 0;
    position.sceneY = 0;
    TextGen::Print("欢迎回家，我的陛下~");
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

        TextGen::Print("升级啦! 现在您的等级是 ", "");
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
#include "role/King.h"
#include "skill/SkillGen.h"
#include <string>

using std::to_string;

void King::ShowMap(const Map& m) const {
    string stateString;
    int stateStyle;

    // set state
    if (HP >= 0.7 * maxHP) {
        if (MP >= 0.7 * maxMP) {
            stateString = "Healty";
            stateStyle = GREEN_;
        } else if (MP >= 0.3 * maxMP) {
            stateString = "Medium MP";
            stateStyle = YELLOW_;
        } else {
            stateString = "Dangerous MP";
            stateStyle = RED_;
        }
    } else if (HP >= 0.3 * maxHP) {
        if (MP >= 0.3 * maxMP) {
            stateString = "Medium HP";
            stateStyle = YELLOW_;
        } else {
            stateString = "Dangerous MP";
            stateStyle = RED_;
        }
    } else {
        stateString = "Dangerous HP";
        stateStyle = RED_;
    }

    m.ShowDirection(position, stateString, stateStyle);
}

void King::ShowMoney() const {
    TextGen::Print<reward>("金币: " + to_string(money));
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
    TextGen::Print("姓名: " + GetName());
    TextGen::Print("等级: " + to_string(GetLevel()));
    TextGen::Print("经验: " + to_string(GetExperience()) + "/" + to_string(GetLevelUpExperience()));
    TextGen::Print("MP: " + to_string(GetHP()) + "/" + to_string(GetMaxHP()));
    TextGen::Print("HP: " + to_string(GetMP()) + "/" + to_string(GetMaxMP()));
    TextGen::Print("攻击力: " + to_string(GetAttack()));
    TextGen::Print("国家: " + GetCountryName());
    if (GetCurrentWeapon() == "")
        TextGen::Print("当前武器: 无");
    else
        TextGen::Print("当前武器: " + GetCurrentWeapon());
}

bool King::GoUp(const Map& m) {
    position.GoUp();
    if (!(m.IsValidPosition(position))) {
        position.GoDown();
        TextGen::Print<warning>("不能向上!");
        return false;
    } else
        return true;
}

bool King::GoDown(const Map& m) {
    position.GoDown();
    if (!(m.IsValidPosition(position))) {
        position.GoUp();
        TextGen::Print<warning>("不能向下!");
        return false;
    } else
        return true;
}

bool King::GoLeft(const Map& m) {
    position.GoLeft();
    if (!(m.IsValidPosition(position))) {
        position.GoRight();
        TextGen::Print<warning>("不能向左!");
        return false;
    } else
        return true;
}

bool King::GoRight(const Map& m) {
    position.GoRight();
    if (!(m.IsValidPosition(position))) {
        position.GoLeft();
        TextGen::Print<warning>("不能向右!");
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

        string attackSkillString, supportSkillString;
        AttackSkill attackSkill;
        SupportSkill supportSkill;

        switch (level) {
            case 2:
                IncreaseMaxHP(100);
                attackSkillString = SkillGen::attackSkillsVector[1];
                attackSkill = SkillGen::attackSkills.at(attackSkillString);
                MasterAttackSkill(attackSkill);
                TextGen::Print<reward>("HP增加100, 获得技能 " + attackSkill.GetName() + " !");
                break;
            case 3:
                IncreaseAttack(2);
                supportSkillString = SkillGen::supportSkillsVector[1];
                supportSkill = SkillGen::supportSkills.at(supportSkillString);
                MasterSupportSkill(supportSkill);
                TextGen::Print<reward>("攻击力增加1, 获得技能 " + supportSkill.GetName() + " !");
                break;
            case 4:
                IncreaseMaxMP(50);
                attackSkillString = SkillGen::attackSkillsVector[2];
                attackSkill = SkillGen::attackSkills.at(attackSkillString);
                MasterAttackSkill(attackSkill);
                TextGen::Print<reward>("MP增加50, 获得技能 " + attackSkill.GetName() + " !");
                break;
            case 5:
                IncreaseMaxHP(200);
                supportSkillString = SkillGen::supportSkillsVector[2];
                supportSkill = SkillGen::supportSkills.at(supportSkillString);
                MasterSupportSkill(supportSkill);
                TextGen::Print<reward>("HP增加200, 获得技能 " + supportSkill.GetName() + " !");
                break;
            case 6:
                IncreaseAttack(2);
                attackSkillString = SkillGen::attackSkillsVector[3];
                attackSkill = SkillGen::attackSkills.at(attackSkillString);
                MasterAttackSkill(attackSkill);
                TextGen::Print<reward>("攻击力增加2, 获得技能 " + attackSkill.GetName() + " !");
                break;
            case 7:
                IncreaseMaxHP(300);
                supportSkillString = SkillGen::supportSkillsVector[3];
                supportSkill = SkillGen::supportSkills.at(supportSkillString);
                MasterSupportSkill(supportSkill);
                TextGen::Print<reward>("HP增加300, 获得技能 " + supportSkill.GetName() + " !");
                break;
            case 8:
                IncreaseMaxMP(100);
                attackSkillString = SkillGen::attackSkillsVector[4];
                attackSkill = SkillGen::attackSkills.at(attackSkillString);
                MasterAttackSkill(attackSkill);
                TextGen::Print<reward>("MP增加100, 获得技能 " + attackSkill.GetName() + " !");
                break;
            case 9:
                IncreaseAttack(5);
                supportSkillString = SkillGen::supportSkillsVector[4];
                supportSkill = SkillGen::supportSkills.at(supportSkillString);
                MasterSupportSkill(supportSkill);
                TextGen::Print<reward>("攻击力增加5, 获得技能 " + supportSkill.GetName() + " !");
                break;
            case 10:
                IncreaseMaxHP(300);
                IncreaseMaxMP(50);
                attackSkillString = SkillGen::attackSkillsVector[5];
                attackSkill = SkillGen::attackSkills.at(attackSkillString);
                MasterAttackSkill(attackSkill);
                TextGen::Print<reward>("HP增加300, MP增加50, 获得技能 " + attackSkill.GetName() + " !");
                break;
            default:
                break;
        }

        SetHP(GetMaxHP());
        SetMP(GetMaxMP());
    }
}

void King::EquipWeapon() {
    int inputInt;
    int weaponNum = bag.GetWeaponsNum();

    bag.ShowWeapon();
    TextGen::Print<request>("请选择您想装备的武器(输入-1卸下当前武器)");
    inputInt = TextGen::InputInt();
    if (inputInt < -1 || inputInt >= weaponNum) {
        TextGen::Print<warning>("错误序号，取消装备!");
    } else if (inputInt == -1) {
        if (curWeapon != "") {
            Weapon& weapon = bag.GetWeaponByName(curWeapon);
            attack -= weapon.GetAttack();
            TextGen::Print<buff>("成功卸下 " + curWeapon + " !");
            curWeapon = "";
        }
    } else {
        if (curWeapon != "") {
            Weapon& weapon = bag.GetWeaponByName(curWeapon);
            attack -= weapon.GetAttack();
        }
        curWeapon = bag.GetWeaponNameByIndex(inputInt);
        Weapon& newWeapon = bag.GetWeaponByName(curWeapon);
        attack += newWeapon.GetAttack();
        TextGen::Print<buff>("成功装备 " + curWeapon + " !");
    }
}

void King::AbraseCurrentWeapon() {
    if (curWeapon == "") return;
    Weapon& weapon = bag.GetWeaponByName(curWeapon);
    if (weapon.Abrase()) {
        // weapon is broken
        TextGen::Print<warning>("您的 " + curWeapon + " 已经磨损成废品了!");
        DiscardItem(curWeapon);
    }
}

void King::DropItem() {
    int offset = bag.GetMedicineNum();
    int inputInt;

    bag.ShowBag();
    TextGen::Print<request>("请选择您想丢弃的物品");
    inputInt = TextGen::InputInt();
    if (inputInt < 0 || inputInt >= bag.GetTotalNum()) {
        TextGen::Print<warning>("错误序号，取消丢弃!");
    } else {
        string name;
        if (inputInt >= offset) {
            // 丢弃武器
            inputInt -= offset;
            name = bag.GetWeaponNameByIndex(inputInt);
        } else {
            // 丢弃药品
            name = bag.GetMedicineNameByIndex(inputInt);
        }
        DiscardItem(name);
        TextGen::Print<buff>("您成功丢弃 " + name + " !");
    }
}
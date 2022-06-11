#ifndef KING_H_
#define KING_H_

#include "Role.h"
#include "bag/Bag.h"
#include "common/Global.h"
#include "map/Map.h"
#include "skill/SkillGen.h"
#include "text/TextGen.h"

class King : public Role {
   public:
    King() {}
    King(string kingName,
         string countryName,
         Position position,
         FieldPosition territoryPosition,
         int attack = initialAttack,
         int level = initialLevel,
         int maxHP = initialMaxHP,
         int HP = initialHP,
         int maxMP = initialMaxMP,
         int MP = initialMP,
         int experience = initialExperience,
         int money = initialMoney,
         string curWeapon = "")
        : Role(kingName, attack, level, maxHP, HP, maxMP, MP),
          experience(experience),
          territoryPosition(territoryPosition),
          countryName(countryName),
          money(money),
          position(position),
          curWeapon(curWeapon) {
        for (auto& item : initialMedicines) {
            InsertMedicine(item.first, item.second);
        }
        for (auto& attackSkillName : initialAttackSkills) {
            MasterAttackSkill(SkillGen::attackSkills[attackSkillName]);
        }
        for (auto& supportSkillName : initialSupportSkills) {
            MasterSupportSkill(SkillGen::supportSkills[supportSkillName]);
        }
    }

    int GetExperience() const { return experience; }
    int GetLevelUpExperience() const { return 100 + level * ((level + 10) / 10) * 10; }
    const FieldPosition& GetTerritoryPosition() const { return territoryPosition; }
    const string& GetCountryName() const { return countryName; }
    int GetMoney() const { return money; }
    const Bag& GetBag() const { return bag; }
    Position GetPosition() const { return position; }
    const string& GetCurrentWeapon() const { return curWeapon; }

    void SetExperience(int experience_) { experience = experience_; }
    void SetTerritoryPosition(const FieldPosition& territoryPosition_) { territoryPosition = territoryPosition_; }
    void SetCountryName(const string& countryName_) { countryName = countryName_; }
    void SetMoney(int money_) { money = money_; }
    void SetBagLevel(int level_) { bag.SetLevel(level_); }
    void SetBagWeightLimit(int weightLimit_) { bag.SetWeightLimit(weightLimit_); }
    void SetBagCurWeight(int curWeight_) { bag.SetCurWeight(curWeight_); }
    void SetPosition(const Position& position_) { position = position_; }
    void SetCurrentWeapon(const string& curWeapon_) { curWeapon = curWeapon_; }

    void IncreaseMoney(int money_) { money += money_; }
    void IncreaseExperience(int experience_);

    bool InsertMedicine(const string& name, int num = 1) { return bag.InsertMedicine(name, num); }
    bool InsertWeapon(const Weapon& weapon) { return bag.InsertWeapon(weapon); }
    bool DiscardItem(const string& name, int num = 1) {
        if (curWeapon == name)
            curWeapon = "";
        return bag.Discard(name, num);
    }
    void EquipWeapon();

    void ShowMap(const Map& m) const;
    bool GoUp(const Map& m);
    bool GoDown(const Map& m);
    bool GoLeft(const Map& m);
    bool GoRight(const Map& m);
    void GoHome(const Map& m);

    void ShowBag() const { bag.ShowBag(); }
    void ShowMedicine() const { bag.ShowMedicine(); }
    void ShowWeapon() const { bag.ShowWeapon(); }
    void ShowMoney() const;
    void ShowSkills() const;
    void ShowAttackSkills() const;
    void ShowSupportSkills() const;
    void ShowState() const;

    void Resurrect();

   private:
    int experience;                   // 当前的经验值
    FieldPosition territoryPosition;  // 领地位置
    string countryName;               // 领地名称
    int money;                        // 拥有的金币量
    Bag bag;                          // 背包
    Position position;                // 当前位置
    string curWeapon;                 // 当前装备的武器
};

#endif  // KING_H_
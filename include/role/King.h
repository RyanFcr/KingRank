#ifndef KING_H_
#define KING_H_

#include "Role.h"
#include "bag/Bag.h"
#include "common/Global.h"
#include "map/Map.h"
#include "skill/AttackSkill.h"
#include "skill/Skill.h"
#include "skill/SkillGen.h"
#include "skill/SupportSkill.h"
#include "text/TextGen.h"

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
using rapidjson::Document;
using rapidjson::StringBuffer;
using rapidjson::Value;
using rapidjson::Writer;

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
         int money = initialMoney)
        : Role(kingName, position, attack, level, maxHP, HP, maxMP, MP),
          experience(experience),
          territoryPosition(territoryPosition),
          countryName(countryName),
          money(money) {
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
    const FieldPosition& GetTerritoryPosition() const { return territoryPosition; }
    const string& GetCountryName() const { return countryName; }
    int GetMoney() const { return money; }
    const Bag& GetBag() const { return bag; }
    const map<string, AttackSkill>& GetAttackSkills() const { return attackSkills; }
    const map<string, SupportSkill>& GetSupportSkills() const { return supportSkills; }

    void SetExperience(int experience_) { experience = experience_; }
    void SetTerritoryPosition(const FieldPosition& territoryPosition_) { territoryPosition = territoryPosition_; }
    void SetCountryName(const string& countryName_) { countryName = countryName_; }
    void SetMoney(int money_) { money = money_; }
    void SetBagLevel(int level_) { bag.SetLevel(level_); }
    void SetBagWeightLimit(int weightLimit_) { bag.SetWeightLimit(weightLimit_); }
    void SetBagCurWeight(int curWeight_) { bag.SetCurWeight(curWeight_); }

    void IncreaseMoney(int money_) { money += money_; }

    bool InsertMedicine(const string& name, int num = 1) { return bag.InsertMedicine(name, num); }
    bool InsertWeapon(const Weapon& weapon) { return bag.InsertWeapon(weapon); }
    bool DiscardItem(const string& name, int num = 1) { return bag.Discard(name, num); }

    void MasterAttackSkill(const AttackSkill& attackSkill) {
        attackSkills.insert(make_pair(attackSkill.GetName(), attackSkill));
    }
    void MasterSupportSkill(const SupportSkill& supportSkill) {
        supportSkills.insert(make_pair(supportSkill.GetName(), supportSkill));
    }

    void ShowMap(const Map& m) const;
    void GoUp(const Map& m);
    void GoDown(const Map& m);
    void GoLeft(const Map& m);
    void GoRight(const Map& m);

    void ShowBag() const { bag.ShowBag(); }

   private:
    void TriggerEvent(const Map& m);

    template <typename Writer>
    void Serialize(Writer& writer) const {
        writer.StartObject();

        Role::Serialize(writer);

        writer.String("experience");
        writer.Int(experience);

        writer.String("territoryPosition");
        territoryPosition.Serialize(writer);

        writer.String("countryName");
        writer.String(countryName.c_str(), static_cast<SizeType>(countryName.length()));

        writer.String("money");
        writer.Int(money);

        writer.String("bag");
        bag.Serialize(writer);

        /// @todo skills

        writer.EndObject();
    }

   private:
    int experience;                           // 当前的经验值
    FieldPosition territoryPosition;          // 领地位置
    string countryName;                       // 领地名称
    int money;                                // 拥有的金币量
    Bag bag;                                  // 背包
    map<string, AttackSkill> attackSkills;    // 攻击技能列表
    map<string, SupportSkill> supportSkills;  // 辅助技能列表
};

#endif  // KING_H_
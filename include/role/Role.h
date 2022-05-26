#ifndef ROLE_H_
#define ROLE_H_

#include "skill/AttackSkill.h"
#include "skill/SupportSkill.h"

#include <string>
#include <vector>
#include <map>
using std::string;
using std::vector;
using std::map;

#include "common/Global.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
using rapidjson::SizeType;
using rapidjson::Value;

class Role {
   public:
    Role() {}
    Role(string name,
         int level = 1,
         int attack = 1,
         int maxHP = 100,
         int HP = 100,
         int maxMP = 100,
         int MP = 100)
        : name(name), level(level), attack(attack), maxHP(maxHP), HP(HP), maxMP(maxMP), MP(MP) {}

    const string& GetName() const { return name; }
    int GetLevel() const { return level; }
    int GetAttack() const { return attack; }
    int GetMaxHP() const { return maxHP; }
    int GetHP() const { return HP; }
    int GetMaxMP() const { return maxMP; }
    int GetMP() const { return MP; }
    const map<string, AttackSkill>& GetAttackSkills() const { return attackSkills; }
    const map<string, SupportSkill>& GetSupportSkills() const { return supportSkills; }

    void SetName(const string& name_) { name = name_; }
    void SetLevel(int level_) { level = level_; }
    void SetAttack(int attack_) { attack = attack_; }
    void SetMaxHP(int maxHP_) { maxHP = maxHP_; }
    void SetHP(int HP_) { HP = HP_; }
    void SetMaxMP(int maxMP_) { maxMP = maxMP_; }
    void SetMP(int MP_) { MP = MP_; }

    void MasterAttackSkill(const AttackSkill& attackSkill) {
        attackSkills.insert(make_pair(attackSkill.GetName(), attackSkill));
    }
    void MasterSupportSkill(const SupportSkill& supportSkill) {
        supportSkills.insert(make_pair(supportSkill.GetName(), supportSkill));
    }

    // template <typename Writer>
    // void Serialize(Writer& writer) const {
    //     writer.String("name");
    //     const string name = GetName();
    //     writer.String(name.c_str(), static_cast<SizeType>(name.length()));

    //     writer.String("level");
    //     writer.Int(GetLevel());

    //     writer.String("attack");
    //     writer.Int(GetAttack());

    //     writer.String("maxHP");
    //     writer.Int(GetMaxHP());

    //     writer.String("HP");
    //     writer.Int(GetHP());

    //     writer.String("maxMP");
    //     writer.Int(GetMaxMP());

    //     writer.String("MP");
    //     writer.Int(GetMP());

    //     writer.String("position");
    //     position.Serialize(writer);
    // }

   protected:
    string name;                              // 名字
    int level;                                // 等级
    int attack;                               // 进攻值
    int maxHP;                                // 最大生命
    int HP;                                   // 现有生命值
    int maxMP;                                // 最大魔法值
    int MP;                                   // 现有魔法值
    map<string, AttackSkill> attackSkills;    // 攻击技能列表
    map<string, SupportSkill> supportSkills;  // 辅助技能列表
};

#endif  // ROLE_H_
#ifndef ROLE_H_
#define ROLE_H_

#include "skill/AttackSkill.h"
#include "skill/SupportSkill.h"

#include <map>
#include <string>
#include <vector>
using std::map;
using std::string;
using std::vector;

#include "common/Global.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
using rapidjson::SizeType;
using rapidjson::Value;

class Role {
   public:
    Role() {}
    Role(string name, int level = 1, int attack = 1, int maxHP = 100, int HP = 100, int maxMP = 100, int MP = 100)
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
    const AttackSkill& GetAttackSkill(const string& skillName) const { return attackSkills.at(skillName); }
    const SupportSkill& GetSupportSkill(const string& skillName) const { return supportSkills.at(skillName); }
    const AttackSkill& GetAttackSkillByIndex(int index) const { return attackSkills.at(attackSkillNames[index]); }
    const SupportSkill& GetSupportSkillByIndex(int index) const { return supportSkills.at(supportSkillNames[index]); }
    const AttackSkill& GetRandomAttackSkill();
    const SupportSkill& GetRandomSupportSkill();

    void SetName(const string& name_) { name = name_; }
    void SetLevel(int level_) { level = level_; }
    void SetAttack(int attack_) { attack = attack_; }
    void SetMaxHP(int maxHP_) { maxHP = maxHP_; }
    void SetHP(int HP_) { HP = HP_; }
    void SetMaxMP(int maxMP_) { maxMP = maxMP_; }
    void SetMP(int MP_) { MP = MP_; }

    void IncreaseLevel(int delta) { level += delta; }
    void IncreaseAttack(int delta) { attack += delta; }
    void IncreaseMaxHP(int delta) { maxHP += delta; }
    void IncreaseMaxMP(int delta) { maxMP += delta; }
    void IncreaseMP(int delta) { MP += delta; }
    void IncreaseHP(int delta) { HP += delta; }

    void MasterAttackSkill(const AttackSkill& attackSkill) {
        attackSkills.insert(make_pair(attackSkill.GetName(), attackSkill));

        attackSkillNames.clear();
        attackSkillNames.reserve(attackSkills.size());
        for (auto& item : attackSkills)
            attackSkillNames.emplace_back(item.first);
    }
    void MasterSupportSkill(const SupportSkill& supportSkill) {
        supportSkills.insert(make_pair(supportSkill.GetName(), supportSkill));

        supportSkillNames.clear();
        supportSkillNames.reserve(supportSkills.size());
        for (auto& item : supportSkills)
            supportSkillNames.emplace_back(item.first);
    }

    bool HasAttackSkill(const string& name) const { return attackSkills.count(name) != 0; }
    bool HasSupportSkill(const string& name) const { return supportSkills.count(name) != 0; }
    bool HasAttackSkillByIndex(size_t index) const { return attackSkillNames.size() > index; }
    bool HasSupportSkillByIndex(size_t index) const { return supportSkillNames.size() > index; }

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
    vector<string> attackSkillNames;          // 攻击技能名列表
    vector<string> supportSkillNames;         // 辅助技能名列表
};

#endif  // ROLE_H_
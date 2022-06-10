#ifndef SKILL_H_
#define SKILL_H_

#include <string>
using std::string;

enum SkillId { ATTACK_SKILL_ID, SUPPORT_SKILL_ID };

class Skill {
   public:
    Skill() {}
    Skill(const string& n, const string& d, int MPCost, const SkillId& id)
        : name(n), description(d), MPCost(MPCost), id(id) {}

    const string& GetName() const { return name; }
    const string& GetDescription() const { return description; }
    const SkillId& GetId() const { return id; }
    int GetMPCost() const { return MPCost; }

    void SetName(const string& n) { name = n; }
    void SetDescription(const string& d) { description = d; }
    void SetSkillId(const SkillId& id_) { id = id_; }

   protected:
    string name;         // 技能名
    string description;  // 技能介绍
    int MPCost;          // 消耗MP
    SkillId id;          // 技能类型
};

#endif  // SKILL_H_
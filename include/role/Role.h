#ifndef ROLE_H_
#define ROLE_H_

#include <string>
#include <vector>
using std::string;
using std::vector;

#include "common/Global.h"
#include "rapidjson/writer.h"
#include "rapidjson/document.h"
using rapidjson::SizeType;
using rapidjson::Value;

class Role {
   public:
    Role() {}
    Role(string name,
         Position position,
         int level = 1,
         int attack = 1,
         int maxHP = 100,
         int HP = 100,
         int maxMP = 100,
         int MP = 100)
        : name(name), level(level), attack(attack), maxHP(maxHP), HP(HP), maxMP(maxMP), MP(MP), position(position) {}

    const string& GetName() const { return name; }
    int GetLevel() const { return level; }
    int GetAttack() const { return attack; }
    int GetMaxHP() const { return maxHP; }
    int GetHP() const { return HP; }
    int GetMaxMP() const { return maxMP; }
    int GetMP() const { return MP; }
    Position GetPosition() const { return position; }

    template <typename Writer>
    void Serialize(Writer& writer) const {
        writer.String("name");
        const string name = GetName();
        writer.String(name.c_str(), static_cast<SizeType>(name.length()));

        writer.String("level");
        writer.Int(GetLevel());

        writer.String("attack");
        writer.Int(GetAttack());

        writer.String("maxHP");
        writer.Int(GetMaxHP());

        writer.String("HP");
        writer.Int(GetHP());

        writer.String("maxMP");
        writer.Int(GetMaxMP());

        writer.String("MP");
        writer.Int(GetMP());

        writer.String("position");
        position.Serialize(writer);
    }

   protected:
    string name;        // 名字
    int level;          // 等级
    int attack;         // 进攻值
    int maxHP;          // 最大生命
    int HP;             // 现有生命值
    int maxMP;          // 最大魔法值
    int MP;             // 现有魔法值
    Position position;  // 当前位置
};

#endif  // ROLE_H_
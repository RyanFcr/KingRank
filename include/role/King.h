#ifndef KING_H_
#define KING_H_

#include "Role.h"
#include "bag/Bag.h"
#include "common/Global.h"
#include "map/Map.h"
#include "skill/Skill.h"
#include "text/TextGen.h"

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
using rapidjson::Writer;
using rapidjson::StringBuffer;

class King : public Role {
   public:
    King() {}
    King(string name,
         Position position,
         FieldPosition territoryPosition,
         int attack = 1,
         int level = 1,
         int maxHP = 100,
         int HP = 100,
         int maxMP = 100,
         int MP = 100,
         int experience = 0,
         int money = 0)
        : Role(name, position, attack, level, maxHP, HP, maxMP, MP),
          experience(experience),
          territoryPosition(territoryPosition),
          money(money) {}

    void ShowMap(const Map& m) const;
    void GoUp(const Map& m);
    void GoDown(const Map& m);
    void GoLeft(const Map& m);
    void GoRight(const Map& m);

    template <typename Writer>
    void Serialize(Writer& writer) const {
        writer.StartObject();

        Role::Serialize(writer);

        writer.String("experience");
        writer.Int(experience);

        writer.String("territoryPosition");
        territoryPosition.Serialize(writer);

        writer.String("money");
        writer.Int(money);

        writer.EndObject();
    }

   private:
    int experience;                   // 当前的经验值
    FieldPosition territoryPosition;  // 领地位置
    int money;                        // 拥有的金币量
    // Bag bag;
    // vector<Skill*> skills;
};

#endif  // KING_H_
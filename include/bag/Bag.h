#ifndef BAG_H_
#define BAG_H_

#include <map>
using std::map;

#include "item/Medicine.h"
#include "item/Weapon.h"
#include "rapidjson/writer.h"
using rapidjson::SizeType;

class Bag {
   public:
    Bag(int level = 1, int weightLimit = 10, int curWeight = 0)
        : level(level), weightLimit(weightLimit), curWeight(curWeight) {}

    int GetLevel() const { return level; }
    int GetWeightLimit() const { return weightLimit; }
    int GetCurWeight() const { return curWeight; }
    const map<string, int>& GetMedicines() const { return medicines; }
    const map<string, Weapon>& GetWeapons() const { return weapons; }

    void SetLevel(int level_) { level = level_; }
    void SetWeightLimit(int weightLimit_) { weightLimit = weightLimit_; }
    void SetCurWeight(int curWeight_) { curWeight = curWeight_; }
    bool InsertMedicine(const string& name, int num = 1);
    bool InsertWeapon(const Weapon& weapon);
    bool Discard(const string& name, int num = 1);

    template <typename Writer>
    void Serialize(Writer& writer) const {
        writer.StartObject();

        writer.String("level");
        writer.Int(level);
        writer.String("weightLimit");
        writer.Int(weightLimit);
        writer.String("curWeight");
        writer.Int(curWeight);

        writer.String("medicines");
        writer.StartObject();
        for (auto& item : medicines) {
            writer.String(item.first.c_str(), static_cast<SizeType>(item.first.length()));
            writer.Int(item.second);
        }
        writer.EndObject();

        writer.String("weapons");
        writer.StartObject();
        for (auto& item : weapons) {
            writer.String(item.first.c_str(), static_cast<SizeType>(item.first.length()));
            item.second.Serialize(writer);
        }
        writer.EndObject();

        writer.EndObject();
    }

   private:
    int level;                    // 背包等级
    int weightLimit;              // 重量上限
    int curWeight;                // 当前重量
    map<string, int> medicines;   // 存放的药瓶(数量不定)
    map<string, Weapon> weapons;  // 存放的武器(数量最多为1，但可以强化)
};

#endif  // BAG_H_
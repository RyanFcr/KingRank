#ifndef BAG_H_
#define BAG_H_

#include <map>
#include <utility>
#include <vector>
using std::make_pair;
using std::map;
using std::pair;
using std::vector;

#include "common/Config.h"
#include "item/Medicine.h"
#include "item/Weapon.h"
#include "rapidjson/writer.h"
using rapidjson::SizeType;

class Bag {
   public:
    Bag(int level = initialBagLevel, int weightLimit = initialWeightLimit, int curWeight = 0)
        : level(level), weightLimit(weightLimit), curWeight(curWeight) {}

    int GetLevel() const { return level; }
    int GetWeightLimit() const { return weightLimit; }
    int GetCurWeight() const { return curWeight; }
    int GetWeaponsNum() const { return weapons.size(); }
    const map<string, int>& GetMedicines() const { return medicines; }
    const map<string, Weapon>& GetWeapons() const { return weapons; }
    const vector<pair<string, int>>& GetMedicineNames() const { return medicineNames; }
    const vector<string>& GetWeaponNames() const { return weaponNames; }
    const string& GetMedicineNameByIndex(int index) const { return medicineNames[index].first; }
    const string& GetWeaponNameByIndex(int index) const { return weaponNames[index]; }
    Weapon& GetWeaponByName(const string& name) { return weapons.at(name); }

    void SetLevel(int level_) { level = level_; }
    void SetWeightLimit(int weightLimit_) { weightLimit = weightLimit_; }
    void SetCurWeight(int curWeight_) { curWeight = curWeight_; }
    bool InsertMedicine(const string& name, int num = 1);
    bool InsertWeapon(const Weapon& weapon);
    bool Discard(const string& name, int num = 1);
    void DiscardAll();

    void ShowBag() const;
    void ShowMedicine() const;
    void ShowWeapon() const;

    bool HasMedicineByIndex(size_t index) const { return medicineNames.size() > index; }
    bool HasWeaponByIndex(size_t index) const { return weaponNames.size() > index; }
    bool HasMedicine(const string& name) const { return medicines.count(name) != 0; }
    bool HasWeapon(const string& name) const { return weapons.count(name) != 0; }
    bool HasNoMedicine() const { return medicineNames.size() == 0; }
    bool HasNoWeapon() const { return weaponNames.size() == 0; }

   private:
    int level;                                // 背包等级
    int weightLimit;                          // 重量上限
    int curWeight;                            // 当前重量
    map<string, int> medicines;               // 存放的药品(数量不定)
    map<string, Weapon> weapons;              // 存放的武器(数量最多为1，但可以强化)
    vector<pair<string, int>> medicineNames;  // 药品名列表
    vector<string> weaponNames;               // 武器名列表
};

#endif  // BAG_H_
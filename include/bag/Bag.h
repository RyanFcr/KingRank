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
    int GetMedicineNum() const { return medicines.size(); }
    int GetWeaponsNum() const { return weapons.size(); }
    int GetTotalNum() const { return medicines.size() + weapons.size(); }
    const map<string, int>& GetMedicines() const { return medicines; }
    const map<string, Weapon>& GetWeapons() const { return weapons; }
    const vector<pair<string, int>>& GetMedicineNames() const { return medicineNames; }
    const vector<string>& GetWeaponNames() const { return weaponNames; }
    const string& GetMedicineNameByIndex(int index) const { return medicineNames[index].first; }
    const string& GetWeaponNameByIndex(int index) const { return weaponNames[index]; }
    Weapon& GetWeaponByName(const string& name) { return weapons[name]; }

    void SetLevel(int level_) { level = level_; }
    void SetWeightLimit(int weightLimit_) { weightLimit = weightLimit_; }
    void SetCurWeight(int curWeight_) { curWeight = curWeight_; }
    bool InsertMedicine(const string& name, int num = 1);
    bool InsertWeapon(const Weapon& weapon);
    bool Discard(const string& name, int num = 1);
    void DiscardAll();
    void IncreaseCapacity(int capacity_) { weightLimit += capacity_; }

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
    int level;                                // ????????????
    int weightLimit;                          // ????????????
    int curWeight;                            // ????????????
    map<string, int> medicines;               // ???????????????(????????????)
    map<string, Weapon> weapons;              // ???????????????(???????????????1??????????????????)
    vector<pair<string, int>> medicineNames;  // ???????????????
    vector<string> weaponNames;               // ???????????????
};

#endif  // BAG_H_
#include "bag/Bag.h"
#include "common/Global.h"
#include "item/ItemGen.h"
#include "text/TextGen.h"

#include <iostream>
using std::cout;
using std::to_string;
/**
 * @brief insert medicines into the bag
 * @param name Name of medicines
 * @param num Number of medicines
 * @return false: insertion fail(too full bag)
 * @throw UNKNOWN_ITEM
 */
bool Bag::InsertMedicine(const string& name, int num) {
    int weight;

    // medicine exist
    if (ItemGen::IsMedicineExist(name)) {
        weight = ItemGen::GetMedicine(name).GetWeight();
        if (curWeight + num * weight <= weightLimit) {
            // have enought space
            medicines[name] += num;
            curWeight += num * weight;

            medicineNames.clear();
            for (auto& item : medicines)
                medicineNames.push_back(item);
            return true;
        }
        return false;
    }

    // unknown_item
    throw UNKNOWN_ITEM;
}

/**
 * @brief insert weapon into the bag
 * @param name Name of weapon
 * @return false: insertion fail(too full bag)
 * @throw UNKNOWN_ITEM
 */
bool Bag::InsertWeapon(const Weapon& weapon) {
    int weight;
    string name = weapon.GetName();

    // weapon exist
    if (ItemGen::IsWeaponExist(name)) {
        if (weapons.count(name))
            return false;

        weight = ItemGen::GetWeapon(name).GetWeight();
        if (curWeight + weight <= weightLimit) {
            weapons.insert(make_pair(name, weapon));
            curWeight += weight;

            weaponNames.clear();
            for (auto& item : weapons)
                weaponNames.push_back(item.first);
            return true;
        }
        return false;
    }

    // unknown_item
    throw UNKNOWN_ITEM;
}

/**
 * @brief discard item in the bag
 * @param name name of the item
 * @param num number of the item(only for medicine)
 * @return false: discard fail(have no `name', have too few medicines)
 */
bool Bag::Discard(const string& name, int num) {
    int weight;

    // medicine exist
    if (ItemGen::IsMedicineExist(name)) {
        weight = ItemGen::GetMedicine(name).GetWeight();
        if (medicines[name] >= num) {
            // have enough medicines
            medicines[name] -= num;
            curWeight -= num * weight;
            if (medicines[name] == 0)
                medicines.erase(name);

            medicineNames.clear();
            for (auto& item : medicines)
                medicineNames.push_back(item);
            return true;
        }
        return false;
    }

    // weapon exist
    if (ItemGen::IsWeaponExist(name)) {
        if (!weapons.count(name))
            return false;

        weight = ItemGen::GetWeapon(name).GetWeight();
        weapons.erase(name);
        curWeight -= weight;
        if (medicines[name] == 0)
            medicines.erase(name);

        weaponNames.clear();
        for (auto& item : weapons)
            weaponNames.push_back(item.first);
        return true;
    }

    // unknown_item
    throw UNKNOWN_ITEM;
}

/**
 * @brief print the items in the bag
 */
void Bag::ShowBag() const {
    TextGen::Print("Weight Limit: " + to_string(GetWeightLimit()));
    TextGen::Print("Current Weight: " + to_string(GetCurWeight()));
    ShowMedicine();
    ShowWeapon();
}

void Bag::ShowMedicine() const {
    TextGen::Print("Medicines:");
    if (medicineNames.size() == 0) {
        TextGen::Print("empty", "");
    } else {
        for (size_t i = 0; i < medicineNames.size(); i++) {
            TextGen::Print(to_string(int(i)) + ". " + medicineNames[i].first + ":" + to_string(medicineNames[i].second),
                           "  ");
        }
    }
    TextGen::Print("");
}

void Bag::ShowWeapon() const {
    TextGen::Print("Weapons:");
    if (weaponNames.size() == 0) {
        TextGen::Print("empty", "");
    } else {
        for (size_t i = 0; i < weaponNames.size(); i++) {
            TextGen::Print(to_string(int(i)) + ". " + weaponNames[i], " ");
        }
    }
    TextGen::Print("");
}

void Bag::DiscardAll() {
    medicines.clear();
    weapons.clear();
    medicineNames.clear();
    weaponNames.clear();
}
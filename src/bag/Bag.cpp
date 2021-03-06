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
            for (auto item : medicines)
                medicineNames.push_back(item);
            return true;
        }
        return false;
    }

    // unknown_item
    throw UNKNOWN_ITEM;
}

/**
 * @brief insert weapon into the bag, if existed,
 * then upgrade the weapon
 * @param name Name of weapon
 * @return false: insertion fail(too full bag)
 * @throw UNKNOWN_ITEM
 */
bool Bag::InsertWeapon(const Weapon& weapon) {
    int weight;
    string name = weapon.GetName();

    // weapon exist
    if (ItemGen::IsWeaponExist(name)) {
        if (weapons.count(name)) {
            // upgrade
            Weapon& bagWeapon = weapons[name];
            bagWeapon.SetAbrasion(maxAbrasion);              // restore abrasion
            bagWeapon.SetAttack(bagWeapon.GetAttack() + 1);  // increase attack
            return false;
        }

        weight = ItemGen::GetWeapon(name).GetWeight();
        if (curWeight + weight <= weightLimit) {
            weapons.insert(make_pair(name, weapon));
            curWeight += weight;

            weaponNames.clear();
            for (auto item : weapons)
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
            for (auto item : medicines)
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

        weaponNames.clear();
        for (auto item : weapons)
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
    TextGen::Print("????????????: " + to_string(GetWeightLimit()));
    TextGen::Print("??????????????????: " + to_string(GetCurWeight()));

    // show medicine
    ShowMedicine();

    // show weapon
    int offset = medicineNames.size();
    TextGen::Print("??????:");
    if (weaponNames.size() == 0) {
        TextGen::Print("???", "");
    } else {
        for (size_t i = 0; i < weaponNames.size(); i++) {
            const Weapon& weapon = weapons.at(weaponNames[i]);
            TextGen::Print(to_string(int(i + offset)) + ". ", " ");
            TextGen::Print(weapon.GetName(), "(");
            TextGen::Print("?????????: " + to_string(weapon.GetAttack()), ", ");
            TextGen::Print("??????: " + to_string(weapon.GetAbrasion()) + "/" + to_string(maxAbrasion), ", ");
            TextGen::Print("???????????????: " + to_string(weapon.GetAbrasionLoss()) + ")");
        }
    }
    TextGen::Print("");
}

void Bag::ShowMedicine() const {
    TextGen::Print("??????:");
    if (medicineNames.size() == 0) {
        TextGen::Print("???", "");
    } else {
        for (size_t i = 0; i < medicineNames.size(); i++) {
            Medicine medicine = ItemGen::GetMedicine(medicineNames[i].first);
            int num = medicineNames[i].second;
            TextGen::Print(to_string(int(i)) + ". ", " ");
            TextGen::Print(medicine.GetName(), "(");
            TextGen::Print("??????: " + to_string(num), ", ");
            TextGen::Print("HP: " + to_string(medicine.GetHPValue()) + "%", ", ");
            TextGen::Print("MP: " + to_string(medicine.GetMPValue()) + "%)");
        }
    }
    TextGen::Print("");
}

void Bag::ShowWeapon() const {
    TextGen::Print("??????:");
    if (weaponNames.size() == 0) {
        TextGen::Print("???", "");
    } else {
        for (size_t i = 0; i < weaponNames.size(); i++) {
            const Weapon& weapon = weapons.at(weaponNames[i]);
            TextGen::Print(to_string(int(i)) + ". ", " ");
            TextGen::Print(weapon.GetName(), "(");
            TextGen::Print("?????????: " + to_string(weapon.GetAttack()), ", ");
            TextGen::Print("??????: " + to_string(weapon.GetAbrasion()) + "/" + to_string(maxAbrasion), ", ");
            TextGen::Print("???????????????: " + to_string(weapon.GetAbrasionLoss()) + ")");
        }
    }
    TextGen::Print("");
}

void Bag::DiscardAll() {
    medicines.clear();
    weapons.clear();
    medicineNames.clear();
    weaponNames.clear();
    curWeight = 0;
}
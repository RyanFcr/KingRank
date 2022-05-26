#include "bag/Bag.h"
#include "common/Global.h"
#include "item/ItemGen.h"
#include "text/TextGen.h"

#include <utility>
using std::make_pair;

#include <iostream>
using std::cout;
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
        return true;
    }

    // unknown_item
    throw UNKNOWN_ITEM;
}

/**
 * @brief print the items in the bag
 */
void Bag::ShowBag() const {
    TextGen::PrintBag(*this);
}

void Bag::DiscardAll() {
    medicines.clear();
    weapons.clear();
}
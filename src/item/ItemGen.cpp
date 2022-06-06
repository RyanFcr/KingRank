#include "item/ItemGen.h"

#include "common/Config.h"
#include "common/Global.h"
#include "rapidjson/document.h"

#include <fstream>
#include <utility>

using rapidjson::Document;
using rapidjson::SizeType;
using rapidjson::Value;
using std::getline;
using std::ifstream;
using std::ios;
using std::make_pair;
using std::string;
using std::vector;

// instantiation
map<string, Medicine> ItemGen::medicines;
map<string, Weapon> ItemGen::weapons;
vector<string> ItemGen::weaponNames;
vector<string> ItemGen::medicineNames;

/**
 * @brief Deserialize into `Item' objects from json file
 * Just call `InitMedicine' and `InitWeapon' function.
 * @throw OPEN_FILE_FAIL
 * @throw HAS_PARSE_ERROR
 */
void ItemGen::Init() {
    ifstream ifs(itemFile, ios::in);
    if (ifs.fail())
        throw OPEN_FILE_FAIL;
    string itemData;
    getline(ifs, itemData);

    Document d;
    PARSE_DOM_OBJECT(d, itemData.c_str())

    // Weapons
    ASSERT_DOM_OBJECT_HAS_MEMBER(d, "weapons")
    ASSERT_DOM_OBJECT_IS_ARRAY(d["weapons"])
    const Value& weaponData = d["weapons"];
    InitWeapon(weaponData);

    // Medicines
    ASSERT_DOM_OBJECT_HAS_MEMBER(d, "medicines")
    ASSERT_DOM_OBJECT_IS_ARRAY(d["medicines"])
    const Value& medicineData = d["medicines"];
    InitMedicine(medicineData);

    ifs.close();
}

/**
 * @brief Deserialize into `Medicine' objects from json file
 * @throw HAS_PARSE_ERROR
 */
void ItemGen::InitMedicine(const Value& data) {
    string name, description;
    int weight, HPValue, MPValue, price;

    for (SizeType i = 0; i < data.Size(); i++) {
        const Value& medicine = data[i];
        ASSERT_DOM_OBJECT_IS_OBJECT(medicine)

        DOM_OBJECT_MEMBER_TO_VAR_STRING(medicine, "name", name)
        DOM_OBJECT_MEMBER_TO_VAR_STRING(medicine, "description", description)
        DOM_OBJECT_MEMBER_TO_VAR_INT(medicine, "weight", weight)
        DOM_OBJECT_MEMBER_TO_VAR_INT(medicine, "HP", HPValue)
        DOM_OBJECT_MEMBER_TO_VAR_INT(medicine, "MP", MPValue)
        DOM_OBJECT_MEMBER_TO_VAR_INT(medicine, "price", price)

        medicines.insert(make_pair(name, Medicine{name, description, weight, price, HPValue, MPValue}));
        medicineNames.push_back(name);
    }
}

/**
 * @brief Deserialize into `Weapon' objects from json file
 * @throw HAS_PARSE_ERROR
 */
void ItemGen::InitWeapon(const Value& data) {
    string name, description;
    int weight, attack, abrasionLoss, price;

    for (SizeType i = 0; i < data.Size(); i++) {
        const Value& weapon = data[i];
        ASSERT_DOM_OBJECT_IS_OBJECT(weapon)

        DOM_OBJECT_MEMBER_TO_VAR_STRING(weapon, "name", name)
        DOM_OBJECT_MEMBER_TO_VAR_STRING(weapon, "description", description)
        DOM_OBJECT_MEMBER_TO_VAR_INT(weapon, "weight", weight)
        DOM_OBJECT_MEMBER_TO_VAR_INT(weapon, "attack", attack)
        DOM_OBJECT_MEMBER_TO_VAR_INT(weapon, "abrasionLoss", abrasionLoss)
        DOM_OBJECT_MEMBER_TO_VAR_INT(weapon, "price", price)

        weapons.insert(make_pair(name, Weapon{name, description, weight, price, attack, abrasionLoss}));
        weaponNames.push_back(name);
    }
}

/**
 * @brief Check whether certain medicine exists
 * @param name name of the medicine
 * @return true: exist
 * @return false: non-exist
 */
bool ItemGen::IsMedicineExist(const string &name) {
    return medicines.count(name) != 0;
}

/**
 * @brief Check whether certain weapon exists
 * @param name name of the weapon
 * @return true: exist
 * @return false: non-exist
 */
bool ItemGen::IsWeaponExist(const string &name) {
    return weapons.count(name) != 0;
}

/**
 * @brief Get Weapon
 * @param name 
 * @return Weapon 
 * @throw UNKNOWN_ITEM
 */
Weapon ItemGen::GetWeapon(const string &name) {
    if (IsWeaponExist(name)) throw UNKNOWN_ITEM;
    return weapons[name];
}

/**
 * @brief Get Medicine
 * @param name 
 * @return Medicine 
 * @throw UNKNOWN_ITEM
 */
Medicine ItemGen::GetMedicine(const string &name) {
    if (!IsMedicineExist(name)) throw UNKNOWN_ITEM;
    return medicines[name];
}

string ItemGen::GetRandomMedicineName() {
    if (medicineNames.size() == 0)
        return "";
    int index = rand() % (medicineNames.size());
    return medicineNames[index];
}

string ItemGen::GetRandomWeaponName() {
    if (weaponNames.size() == 0)
        return "";
    int index = rand() % (weaponNames.size());
    return weaponNames[index];
}
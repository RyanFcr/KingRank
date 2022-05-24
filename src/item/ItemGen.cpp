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

// instantiation
map<string, Medicine> ItemGen::medicines;
map<string, Weapon> ItemGen::weapons;

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
    if (d.Parse(itemData.c_str()).HasParseError())
        throw HAS_PARSE_ERROR;
    if (!d.IsObject())
        throw HAS_PARSE_ERROR;

    // Weapons
    if (!d.HasMember("weapons"))
        throw HAS_PARSE_ERROR;
    if (!d["weapons"].IsArray())
        throw HAS_PARSE_ERROR;
    const Value& weaponData = d["weapons"];
    InitWeapon(weaponData);

    // Medicines
    if (!d.HasMember("medicines"))
        throw HAS_PARSE_ERROR;
    if (!d["medicines"].IsArray())
        throw HAS_PARSE_ERROR;
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
    int weight, HPValue, MPValue;

    for (SizeType i = 0; i < data.Size(); i++) {
        const Value& medicine = data[i];
        if (!medicine.IsObject())
            throw HAS_PARSE_ERROR;

        if (!medicine.HasMember("name"))
            throw HAS_PARSE_ERROR;
        if (!medicine["name"].IsString())
            throw HAS_PARSE_ERROR;
        name = medicine["name"].GetString();

        if (!medicine.HasMember("description"))
            throw HAS_PARSE_ERROR;
        if (!medicine["description"].IsString())
            throw HAS_PARSE_ERROR;
        description = medicine["description"].GetString();

        if (!medicine.HasMember("weight"))
            throw HAS_PARSE_ERROR;
        if (!medicine["weight"].IsInt())
            throw HAS_PARSE_ERROR;
        weight = medicine["weight"].GetInt();

        if (!medicine.HasMember("HP"))
            throw HAS_PARSE_ERROR;
        if (!medicine["HP"].IsInt())
            throw HAS_PARSE_ERROR;
        HPValue = medicine["HP"].GetInt();

        if (!medicine.HasMember("MP"))
            throw HAS_PARSE_ERROR;
        if (!medicine["MP"].IsInt())
            throw HAS_PARSE_ERROR;
        MPValue = medicine["MP"].GetInt();

        medicines.insert(make_pair(name, Medicine{name, description, weight, HPValue, MPValue}));
    }
}

/**
 * @brief Deserialize into `Weapon' objects from json file
 * @throw HAS_PARSE_ERROR
 */
void ItemGen::InitWeapon(const Value& data) {
    string name, description;
    int weight, attack, abrasionLoss;

    for (SizeType i = 0; i < data.Size(); i++) {
        const Value& weapon = data[i];
        if (!weapon.IsObject())
            throw HAS_PARSE_ERROR;

        if (!weapon.HasMember("name"))
            throw HAS_PARSE_ERROR;
        if (!weapon["name"].IsString())
            throw HAS_PARSE_ERROR;
        name = weapon["name"].GetString();

        if (!weapon.HasMember("description"))
            throw HAS_PARSE_ERROR;
        if (!weapon["description"].IsString())
            throw HAS_PARSE_ERROR;
        description = weapon["description"].GetString();

        if (!weapon.HasMember("weight"))
            throw HAS_PARSE_ERROR;
        if (!weapon["weight"].IsInt())
            throw HAS_PARSE_ERROR;
        weight = weapon["weight"].GetInt();

        if (!weapon.HasMember("attack"))
            throw HAS_PARSE_ERROR;
        if (!weapon["attack"].IsInt())
            throw HAS_PARSE_ERROR;
        attack = weapon["attack"].GetInt();

        if (!weapon.HasMember("abrasionLoss"))
            throw HAS_PARSE_ERROR;
        if (!weapon["abrasionLoss"].IsInt())
            throw HAS_PARSE_ERROR;
        abrasionLoss = weapon["abrasionLoss"].GetInt();

        weapons.insert(make_pair(name, Weapon{name, description, weight, attack, abrasionLoss}));
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
    if (IsMedicineExist(name)) throw UNKNOWN_ITEM;
    return medicines[name];
}
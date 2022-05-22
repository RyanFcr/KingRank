#include "item/ItemGen.h"

#include "common/Config.h"
#include "common/Global.h"
#include "rapidjson/document.h"

#include <fstream>
#include <utility>

using rapidjson::Document;
using rapidjson::SizeType;
using rapidjson::Value;
using std::ifstream;
using std::ios;
using std::make_pair;
using std::string;

/**
 * @brief Serialize into `Item' objects from json file
 * Just call `InitMedicine' and `InitWeapon' function.
 * @throw OPEN_FILE_FAIL
 * @throw HAS_PARSE_ERROR
 */
void ItemGen::Init() {
    ifstream ifs(itemFile, ios::in);
    if (ifs.fail())
        throw OPEN_FILE_FAIL;
    string itemData;
    ifs >> itemData;

    Document d;
    if (d.Parse(itemData.c_str()).HasParseError())
        throw HAS_PARSE_ERROR;
    if (!d.IsObject())
        throw HAS_PARSE_ERROR;

    // Weapons
    if (!d.HasMember("Weapon"))
        throw HAS_PARSE_ERROR;
    if (!d["Weapon"].IsArray())
        throw HAS_PARSE_ERROR;
    const Value& weaponData = d["Weapon"];
    InitWeapon(weaponData);

    // Medicines
    if (!d.HasMember("Medicine"))
        throw HAS_PARSE_ERROR;
    if (!d["Medicine"].IsArray())
        throw HAS_PARSE_ERROR;
    const Value& medicineData = d["Medicine"];
    InitMedicine(medicineData);

    ifs.close();
}

/**
 * @brief Serialize into `Medicine' objects from json file
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

        if (!medicine.HasMember("HPValue"))
            throw HAS_PARSE_ERROR;
        if (!medicine["HPValue"].IsInt())
            throw HAS_PARSE_ERROR;
        HPValue = medicine["HPValue"].GetInt();

        if (!medicine.HasMember("MPValue"))
            throw HAS_PARSE_ERROR;
        if (!medicine["MPValue"].IsInt())
            throw HAS_PARSE_ERROR;
        MPValue = medicine["MPValue"].GetInt();

        medicines.insert(make_pair(name, Medicine{name, description, weight, HPValue, MPValue}));
    }
}

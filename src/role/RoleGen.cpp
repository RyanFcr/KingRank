#include "role/RoleGen.h"
#include "bag/Bag.h"
#include "common/Global.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "text/TextGen.h"

#include <fstream>
using rapidjson::Document;
using rapidjson::kArrayType;
using rapidjson::kObjectType;
using rapidjson::SizeType;
using rapidjson::StringBuffer;
using rapidjson::Value;
using rapidjson::Writer;
using std::getline;
using std::ifstream;
using std::ios;
using std::ofstream;

/// instantiation
King RoleGen::king;
Document RoleGen::kingDocument;

/**
 * @brief serialize `kingData' into writer
 * @param kingData document value of single king
 * @throw HAS_PARSE_ERROR
 */
template <typename Writer>
static void SerializeKing(const Value& kingData, Writer& writer);

/**
 * @brief initialize king by creating or loading
 * @param map
 * @throw HAS_PARSE_ERROR
 */
void RoleGen::InitKing(Map& map) {
    string input, kingData;

    ifstream ifs(kingFile, ios::in);
    getline(ifs, kingData);
    if (kingDocument.Parse(kingData.c_str()).HasParseError())
        throw HAS_PARSE_ERROR;
    ifs.close();

    TextGen::Print("Welcome to the world of Kings!");
    TextGen::Print<request>("Do you have your own territory, young King?");
    while (1) {
        input = TextGen::Input();
        if (input == "yes") {
            if (LoadKing())
                break;
            else {
                TextGen::Print<warning>("Sorry, your territory doesn't exist!");
                TextGen::Print<request>("Do you really have your own territory, young King?");
            }
        } else if (input == "no") {
            if (CreateKing(map))
                break;
            else {
                TextGen::Print<warning>("Sorry, fail to register your territory!");
                TextGen::Print<request>("Have you already had your own territory, young King?");
            }
        } else {
            TextGen::Print<warning>("Invalid Input!");
        }
    }
}

/**
 * @brief check whether the name is in the json file
 * @param name
 * @return true: redundancy exists
 */
bool RoleGen::CheckRedundancy(string kingName) {
    if (!kingDocument.IsObject()) {
        throw HAS_PARSE_ERROR;
    }
    const Value& kings = kingDocument["kings"];
    for (SizeType i = 0; i < kings.Size(); i++) {
        const Value& kingData = kings[i];
        if (!kingData.IsObject())
            throw HAS_PARSE_ERROR;
        if (kingData.HasMember("name")) {
            const Value& documentNameValue = kingData["name"];
            if (!documentNameValue.IsString())
                throw HAS_PARSE_ERROR;
            string documentName = documentNameValue.GetString();
            if (documentName == kingName)
                return true;
        }
    }
    return false;
}

bool RoleGen::LoadKing() {
    return false;
}

/**
 * @brief create a new king and allocate him with a territory
 * @param map
 * @return false: creation fail (exist king name)
 * @throw HAS_PARSE_ERROR
 */
bool RoleGen::CreateKing(Map& map) {
    string kingName, countryName;

    /// set king name
    TextGen::Print<request>("What's your name, young King?");
    kingName = TextGen::Input();

    if (CheckRedundancy(kingName))
        return false;

    /// set kingdom name
    TextGen::Print("Welcome, " + kingName + "!");
    TextGen::Print("You have your own territory, your Kingdom!");
    TextGen::Print<request>("What's your country's name?");
    countryName = TextGen::Input();

    /// allocate a new land
    // map.MapExtend(name);

    /// randomly choose a birthplace and territory
    Position birthPlace{rand() % initialMapSize, rand() % initialMapSize, rand() % fieldSize, rand() % fieldSize};
    FieldPosition territoryPosition{birthPlace.fieldX, birthPlace.fieldY};

    /// construct king
    king = King{kingName, countryName, birthPlace, territoryPosition};

    return true;
}

/**
 * @brief Save `king' into the json file
 * @throw OPEN_FILE_FAIL
 */
void RoleGen::SaveKing() {
    ofstream ofs(kingFile, ios::out);
    if (ofs.fail())
        throw OPEN_FILE_FAIL;

    StringBuffer sb;
    Writer<StringBuffer> writer(sb);
    Value& kings = kingDocument["kings"];

    if (CheckRedundancy(king.GetName())) {
        // Modify

    } else {
        // Append
        AppendKing();
    }

    // write into file
    writer.StartObject();
    writer.String("kings");
    writer.StartArray();
    for (SizeType i = 0; i < kings.Size(); i++) {
        SerializeKing(kings[i], writer);
    }
    writer.EndArray();
    writer.EndObject();

    string kingData = sb.GetString();
    ofs << kingData;

    ofs.close();
}

template <typename Writer>
static void SerializeKing(const Value& kingData, Writer& writer) {
    writer.StartObject();

    /// role相关
    writer.String("name");
    if (!kingData.HasMember("name") || !kingData["name"].IsString())
        throw HAS_PARSE_ERROR;
    const string name = kingData["name"].GetString();
    writer.String(name.c_str(), static_cast<SizeType>(name.length()));

    writer.String("level");
    if (!kingData.HasMember("level") || !kingData["level"].IsInt())
        throw HAS_PARSE_ERROR;
    writer.Int(kingData["level"].GetInt());

    writer.String("attack");
    if (!kingData.HasMember("attack") || !kingData["attack"].IsInt())
        throw HAS_PARSE_ERROR;
    writer.Int(kingData["attack"].GetInt());

    writer.String("maxHP");
    if (!kingData.HasMember("maxHP") || !kingData["maxHP"].IsInt())
        throw HAS_PARSE_ERROR;
    writer.Int(kingData["maxHP"].GetInt());

    writer.String("HP");
    if (!kingData.HasMember("HP") || !kingData["HP"].IsInt())
        throw HAS_PARSE_ERROR;
    writer.Int(kingData["HP"].GetInt());

    writer.String("maxMP");
    if (!kingData.HasMember("maxMP") || !kingData["maxMP"].IsInt())
        throw HAS_PARSE_ERROR;
    writer.Int(kingData["maxMP"].GetInt());

    writer.String("MP");
    if (!kingData.HasMember("MP") || !kingData["MP"].IsInt())
        throw HAS_PARSE_ERROR;
    writer.Int(kingData["MP"].GetInt());

    /// position相关
    writer.String("position");
    writer.StartObject();

    writer.String("fieldX");
    if (!kingData["position"].HasMember("fieldX") || !kingData["position"]["fieldX"].IsInt())
        throw HAS_PARSE_ERROR;
    writer.Int(kingData["position"]["fieldX"].GetInt());

    writer.String("fieldY");
    if (!kingData["position"].HasMember("fieldY") || !kingData["position"]["fieldY"].IsInt())
        throw HAS_PARSE_ERROR;
    writer.Int(kingData["position"]["fieldY"].GetInt());

    writer.String("sceneX");
    if (!kingData["position"].HasMember("sceneX") || !kingData["position"]["sceneX"].IsInt())
        throw HAS_PARSE_ERROR;
    writer.Int(kingData["position"]["sceneX"].GetInt());

    writer.String("sceneY");
    if (!kingData["position"].HasMember("sceneY") || !kingData["position"]["sceneY"].IsInt())
        throw HAS_PARSE_ERROR;
    writer.Int(kingData["position"]["sceneY"].GetInt());

    writer.EndObject();

    /// king相关
    writer.String("experience");
    if (!kingData.HasMember("experience") || !kingData["experience"].IsInt())
        throw HAS_PARSE_ERROR;
    writer.Int(kingData["experience"].GetInt());

    /// territory相关
    writer.String("territoryPosition");
    writer.StartObject();

    writer.String("fieldX");
    if (!kingData["territoryPosition"].HasMember("fieldX") || !kingData["territoryPosition"]["fieldX"].IsInt())
        throw HAS_PARSE_ERROR;
    writer.Int(kingData["territoryPosition"]["fieldX"].GetInt());

    writer.String("fieldY");
    if (!kingData["territoryPosition"].HasMember("fieldY") || !kingData["territoryPosition"]["fieldY"].IsInt())
        throw HAS_PARSE_ERROR;
    writer.Int(kingData["territoryPosition"]["fieldY"].GetInt());

    writer.EndObject();

    /// 继续king相关
    writer.String("countryName");
    if (!kingData.HasMember("countryName") || !kingData["countryName"].IsString())
        throw HAS_PARSE_ERROR;
    const string countryName = kingData["countryName"].GetString();
    writer.String(countryName.c_str(), static_cast<SizeType>(countryName.length()));

    writer.String("money");
    if (!kingData.HasMember("money") || !kingData["money"].IsInt())
        throw HAS_PARSE_ERROR;
    writer.Int(kingData["money"].GetInt());

    /// bag相关
    writer.String("bag");
    writer.StartObject();

    writer.String("level");
    if (!kingData["bag"].HasMember("level") || !kingData["bag"]["level"].IsInt())
        throw HAS_PARSE_ERROR;
    writer.Int(kingData["bag"]["level"].GetInt());

    writer.String("weightLimit");
    if (!kingData["bag"].HasMember("weightLimit") || !kingData["bag"]["weightLimit"].IsInt())
        throw HAS_PARSE_ERROR;
    writer.Int(kingData["bag"]["weightLimit"].GetInt());

    writer.String("curWeight");
    if (!kingData["bag"].HasMember("curWeight") || !kingData["bag"]["curWeight"].IsInt())
        throw HAS_PARSE_ERROR;
    writer.Int(kingData["bag"]["curWeight"].GetInt());

    writer.String("medicines");
    writer.StartObject();
    for (auto& m : kingData["bag"]["medicines"].GetObject()) {
        const string& mName = m.name.GetString();
        writer.String(mName.c_str(), static_cast<SizeType>(mName.length()));
        writer.Int(m.value.GetInt());
    }
    writer.EndObject();

    writer.String("weapons");
    writer.StartObject();
    for (auto& m : kingData["bag"]["weapons"].GetObject()) {
        const string& mName = m.name.GetString();
        writer.String(mName.c_str(), static_cast<SizeType>(mName.length()));
        /// Weapon相关
        writer.StartObject();

        writer.String("name");
        const string& mValueName = m.value["name"].GetString();
        writer.String(mValueName.c_str(), static_cast<SizeType>(mValueName.length()));
        writer.String("description");
        const string& mValueDescription = m.value["description"].GetString();
        writer.String(mValueDescription.c_str(), static_cast<SizeType>(mValueDescription.length()));
        writer.String("weight");
        writer.Int(m.value["weight"].GetInt());
        writer.String("id");
        writer.Int(m.value["id"].GetInt());

        writer.String("attack");
        writer.Int(m.value["attack"].GetInt());
        writer.String("abrasion");
        writer.Int(m.value["abrasion"].GetInt());
        writer.String("abrasionLoss");
        writer.Int(m.value["abrasionLoss"].GetInt());

        writer.EndObject();
    }
    writer.EndObject();

    writer.EndObject();

    /// @todo skills

    writer.EndObject();
}

void RoleGen::AppendKing() {
    Value& kings = kingDocument["kings"];
    Document::AllocatorType& allocator = kingDocument.GetAllocator();

    Value kingValue(kObjectType);
    kingValue.AddMember(
        "name", Value().SetString(king.GetName().c_str(), static_cast<SizeType>(king.GetName().length())), allocator);
    kingValue.AddMember("level", Value().SetInt(king.GetLevel()), allocator);
    kingValue.AddMember("attack", Value().SetInt(king.GetAttack()), allocator);
    kingValue.AddMember("maxHP", Value().SetInt(king.GetMaxHP()), allocator);
    kingValue.AddMember("HP", Value().SetInt(king.GetHP()), allocator);
    kingValue.AddMember("maxMP", Value().SetInt(king.GetMaxMP()), allocator);
    kingValue.AddMember("MP", Value().SetInt(king.GetMP()), allocator);
    Value positionValue(kObjectType);
    positionValue.AddMember("fieldX", Value().SetInt(king.GetPosition().fieldX), allocator);
    positionValue.AddMember("fieldY", Value().SetInt(king.GetPosition().fieldY), allocator);
    positionValue.AddMember("sceneX", Value().SetInt(king.GetPosition().sceneX), allocator);
    positionValue.AddMember("sceneY", Value().SetInt(king.GetPosition().sceneY), allocator);
    kingValue.AddMember("position", positionValue, allocator);
    kingValue.AddMember("experience", Value().SetInt(king.GetExperience()), allocator);
    Value territoryPositionValue(kObjectType);
    territoryPositionValue.AddMember("fieldX", Value().SetInt(king.GetTerritoryPosition().fieldX), allocator);
    territoryPositionValue.AddMember("fieldY", Value().SetInt(king.GetTerritoryPosition().fieldY), allocator);
    kingValue.AddMember("territoryPosition", territoryPositionValue, allocator);
    kingValue.AddMember(
        "countryName",
        Value().SetString(king.GetCountryName().c_str(), static_cast<SizeType>(king.GetCountryName().length())),
        allocator);
    kingValue.AddMember("money", Value().SetInt(king.GetMoney()), allocator);
    Value bagValue(kObjectType);
    bagValue.AddMember("level", Value().SetInt(king.GetBag().GetLevel()), allocator);
    bagValue.AddMember("weightLimit", Value().SetInt(king.GetBag().GetWeightLimit()), allocator);
    bagValue.AddMember("curWeight", Value().SetInt(king.GetBag().GetCurWeight()), allocator);
    Value medicinesValue(kObjectType);
    for (auto& item : king.GetBag().GetMedicines()) {
        medicinesValue.AddMember(Value().SetString(item.first.c_str(), static_cast<SizeType>(item.first.length())),
                                 Value().SetInt(item.second), allocator);
    }
    bagValue.AddMember("medicines", medicinesValue, allocator);
    Value weaponsValue(kObjectType);
    for (auto& item : king.GetBag().GetWeapons()) {
        Value weaponValue(kObjectType);
        weaponValue.AddMember("attack", Value().SetInt(item.second.GetAttack()), allocator);
        weaponValue.AddMember("abrasion", Value().SetInt(item.second.GetAttack()), allocator);
        weaponValue.AddMember("abrasionLoss", Value().SetInt(item.second.GetAttack()), allocator);
        medicinesValue.AddMember(Value().SetString(item.first.c_str(), static_cast<SizeType>(item.first.length())),
                                 weaponValue, allocator);
    }
    bagValue.AddMember("weapons", weaponsValue, allocator);

    kingValue.AddMember("bag", bagValue, allocator);
    kings.PushBack(kingValue, allocator);
}
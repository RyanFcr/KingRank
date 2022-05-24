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
    string input, kingData, kingName;

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
            TextGen::Print<request>("What's your name, young King?");
            kingName = TextGen::Input();

            if (LoadKing(kingName)) {
                TextGen::Print("Welcome! King." + king.GetName() + "!");
                break;
            } else {
                TextGen::Print<warning>("Sorry, your territory doesn't exist!");
                TextGen::Print<request>("Do you really have your own territory, young King?");
            }
        } else if (input == "no") {
            TextGen::Print<request>("What's your name, young King?");
            kingName = TextGen::Input();
            if (CreateKing(kingName, map))
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
 * @param index: if exist, return the index of kingDocument["kings"]
 * @return true: redundancy exists
 */
bool RoleGen::CheckRedundancy(const string& kingName, int& index) {
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
            if (documentName == kingName) {
                index = i;
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief load king from json file to `king'
 * @param kingName
 * @return false: load fail(non-exist king name)
 */
bool RoleGen::LoadKing(const string& kingName) {
    int index = -1;

    if (!CheckRedundancy(kingName, index)) {
        return false;
    }

    const Value& kingValue = kingDocument["kings"][index].GetObject();
    king.SetName(kingValue["name"].GetString());
    king.SetLevel(kingValue["level"].GetInt());
    king.SetAttack(kingValue["attack"].GetInt());
    king.SetMaxHP(kingValue["maxHP"].GetInt());
    king.SetHP(kingValue["HP"].GetInt());
    king.SetMaxMP(kingValue["maxMP"].GetInt());
    king.SetMP(kingValue["MP"].GetInt());
    king.SetPosition(Position{
        kingValue["position"]["fieldX"].GetInt(),
        kingValue["position"]["fieldY"].GetInt(),
        kingValue["position"]["sceneX"].GetInt(),
        kingValue["position"]["sceneY"].GetInt(),
    });

    king.SetExperience(kingValue["experience"].GetInt());
    king.SetTerritoryPosition(FieldPosition{kingValue["territoryPosition"]["fieldX"].GetInt(),
                                            kingValue["territoryPosition"]["fieldY"].GetInt()});
    king.SetCountryName(kingValue["countryName"].GetString());
    king.SetMoney(kingValue["money"].GetInt());
    king.SetBagLevel(kingValue["bag"]["level"].GetInt());
    king.SetBagWeightLimit(kingValue["bag"]["weightLimit"].GetInt());
    king.SetBagCurWeight(kingValue["bag"]["curWeight"].GetInt());
    for (auto& m : kingValue["bag"]["medicines"].GetObject()) {
        king.InsertMedicine(m.name.GetString(), m.value.GetInt());
    }

    for (auto& m : kingValue["bag"]["weapons"].GetObject()) {
        Weapon weapon{m.name.GetString(),         m.value["description"].GetString(), m.value["weight"].GetInt(),
                      m.value["attack"].GetInt(), m.value["abrasionLoss"].GetInt(),   m.value["abrasion"].GetInt()};
        king.InsertWeapon(weapon);
    }

    for (auto& m : kingValue["attackSkills"].GetObject()) {
        AttackSkill attackSkill{m.name.GetString(), m.value["description"].GetString(), m.value["MPCost"].GetInt(),
                                m.value["damageValue"].GetInt()};
        king.MasterAttackSkill(attackSkill);
    }

    for (auto& m : kingValue["supportSkills"].GetObject()) {
        SupportSkill supportSkill{m.name.GetString(), m.value["description"].GetString(), m.value["MPCost"].GetInt(),
                                  m.value["HPValue"].GetInt()};
        king.MasterSupportSkill(supportSkill);
    }

    return true;
}

/**
 * @brief create a new king and allocate him with a territory
 * @param map
 * @return false: creation fail (exist king name)
 * @throw HAS_PARSE_ERROR
 */
bool RoleGen::CreateKing(const string& kingName, Map& map) {
    string countryName;
    int index = -1;

    if (CheckRedundancy(kingName, index))
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
 * @attention for modifying, we erase the origin data and append current king to the document
 * @throw OPEN_FILE_FAIL
 */
void RoleGen::SaveKing() {
    int index = -1;

    ofstream ofs(kingFile, ios::out);
    if (ofs.fail())
        throw OPEN_FILE_FAIL;

    StringBuffer sb;
    Writer<StringBuffer> writer(sb);
    Value& kings = kingDocument["kings"];

    if (CheckRedundancy(king.GetName(), index)) {
        // Modify
        kings.Erase(kings.Begin() + index);
    }

    // Append
    AppendKing();

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

/**
 * @brief Serialize `kingData' to the writer, only called by `SaveKing'
 * @tparam Writer
 * @param kingData
 * @param writer
 */
template <typename Writer>
static void SerializeKing(const Value& kingData, Writer& writer) {
    writer.StartObject();

    {
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
        {
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
        }

        /// king相关
        writer.String("experience");
        if (!kingData.HasMember("experience") || !kingData["experience"].IsInt())
            throw HAS_PARSE_ERROR;
        writer.Int(kingData["experience"].GetInt());

        /// territory相关
        writer.String("territoryPosition");
        {
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
        }

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
        {
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
            {
                writer.StartObject();
                for (auto& m : kingData["bag"]["medicines"].GetObject()) {
                    const string& mName = m.name.GetString();
                    writer.String(mName.c_str(), static_cast<SizeType>(mName.length()));
                    writer.Int(m.value.GetInt());
                }
                writer.EndObject();
            }

            writer.String("weapons");
            {
                writer.StartObject();
                for (auto& m : kingData["bag"]["weapons"].GetObject()) {
                    const string& mName = m.name.GetString();
                    writer.String(mName.c_str(), static_cast<SizeType>(mName.length()));
                    {
                        /// Weapon相关
                        writer.StartObject();

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
                }
                writer.EndObject();
            }

            writer.EndObject();
        }
        
        /// skills
        writer.String("attackSkills");
        {
            writer.StartObject();
            for (auto& m : kingData["attackSkills"].GetObject()) {
                const string& mName = m.name.GetString();
                writer.String(mName.c_str(), static_cast<SizeType>(mName.length()));
                {
                    writer.StartObject();
                    writer.String("description");
                    const string& mValueDescription = m.value["description"].GetString();
                    writer.String(mValueDescription.c_str(), static_cast<SizeType>(mValueDescription.length()));
                    writer.String("MPCost");
                    writer.Int(m.value["MPCost"].GetInt());
                    writer.String("damageValue");
                    writer.Int(m.value["damageValue"].GetInt());
                    writer.EndObject();
                }
            }
            writer.EndObject();
        }
        
        writer.String("supportSkills");
        {
            writer.StartObject();
            for (auto& m : kingData["supportSkills"].GetObject()) {
                const string& mName = m.name.GetString();
                writer.String(mName.c_str(), static_cast<SizeType>(mName.length()));
                {
                    writer.StartObject();
                    writer.String("description");
                    const string& mValueDescription = m.value["description"].GetString();
                    writer.String(mValueDescription.c_str(), static_cast<SizeType>(mValueDescription.length()));
                    writer.String("MPCost");
                    writer.Int(m.value["MPCost"].GetInt());
                    writer.String("HPValue");
                    writer.Int(m.value["HPValue"].GetInt());
                    writer.EndObject();
                }
            }
            writer.EndObject();
        }
        
    }
    writer.EndObject();
}

/**
 * @brief append a new king to the DOM object
 */
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
    {
        Value positionValue(kObjectType);
        positionValue.AddMember("fieldX", Value().SetInt(king.GetPosition().fieldX), allocator);
        positionValue.AddMember("fieldY", Value().SetInt(king.GetPosition().fieldY), allocator);
        positionValue.AddMember("sceneX", Value().SetInt(king.GetPosition().sceneX), allocator);
        positionValue.AddMember("sceneY", Value().SetInt(king.GetPosition().sceneY), allocator);
        kingValue.AddMember("position", positionValue, allocator);
    }
    kingValue.AddMember("experience", Value().SetInt(king.GetExperience()), allocator);
    {
        Value territoryPositionValue(kObjectType);
        territoryPositionValue.AddMember("fieldX", Value().SetInt(king.GetTerritoryPosition().fieldX), allocator);
        territoryPositionValue.AddMember("fieldY", Value().SetInt(king.GetTerritoryPosition().fieldY), allocator);
        kingValue.AddMember("territoryPosition", territoryPositionValue, allocator);
    }
    kingValue.AddMember(
        "countryName",
        Value().SetString(king.GetCountryName().c_str(), static_cast<SizeType>(king.GetCountryName().length())),
        allocator);
    kingValue.AddMember("money", Value().SetInt(king.GetMoney()), allocator);
    {
        Value bagValue(kObjectType);
        bagValue.AddMember("level", Value().SetInt(king.GetBag().GetLevel()), allocator);
        bagValue.AddMember("weightLimit", Value().SetInt(king.GetBag().GetWeightLimit()), allocator);
        bagValue.AddMember("curWeight", Value().SetInt(king.GetBag().GetCurWeight()), allocator);
        {
            Value medicinesValue(kObjectType);
            for (auto& item : king.GetBag().GetMedicines()) {
                medicinesValue.AddMember(
                    Value().SetString(item.first.c_str(), static_cast<SizeType>(item.first.length())),
                    Value().SetInt(item.second), allocator);
            }
            bagValue.AddMember("medicines", medicinesValue, allocator);

            Value weaponsValue(kObjectType);
            for (auto& item : king.GetBag().GetWeapons()) {
                Value weaponValue(kObjectType);
                weaponValue.AddMember("description",
                                      Value().SetString(item.second.GetDescription().c_str(),
                                                        static_cast<SizeType>(item.second.GetDescription().length())),
                                      allocator);
                weaponValue.AddMember("id", Value().SetInt(int(item.second.GetItemId())), allocator);
                weaponValue.AddMember("weight", Value().SetInt(item.second.GetWeight()), allocator);
                weaponValue.AddMember("attack", Value().SetInt(item.second.GetAttack()), allocator);
                weaponValue.AddMember("abrasion", Value().SetInt(item.second.GetAbrasion()), allocator);
                weaponValue.AddMember("abrasionLoss", Value().SetInt(item.second.GetAbrasionLoss()), allocator);

                weaponsValue.AddMember(
                    Value().SetString(item.first.c_str(), static_cast<SizeType>(item.first.length())), weaponValue,
                    allocator);
            }
            bagValue.AddMember("weapons", weaponsValue, allocator);
        }
        kingValue.AddMember("bag", bagValue, allocator);
    }

    {
        Value attackSkillsValue(kObjectType);
        for (auto& item : king.GetAttackSkills()) {
            Value attackSkillValue(kObjectType);
            attackSkillValue.AddMember("description",
                                      Value().SetString(item.second.GetDescription().c_str(),
                                                        static_cast<SizeType>(item.second.GetDescription().length())),
                                      allocator);
            attackSkillValue.AddMember("id", Value().SetInt(int(item.second.GetId())), allocator);
            attackSkillValue.AddMember("MPCost", Value().SetInt(item.second.GetMPCost()), allocator);
            attackSkillValue.AddMember("damageValue", Value().SetInt(item.second.GetDamageValue()), allocator);

            attackSkillsValue.AddMember(
                Value().SetString(item.first.c_str(), static_cast<SizeType>(item.first.length())), attackSkillValue,
                allocator);
        }
        kingValue.AddMember("attackSkills", attackSkillsValue, allocator);
    }
    {
        Value supportSkillsValue(kObjectType);
        for (auto& item : king.GetSupportSkills()) {
            Value supportSkillValue(kObjectType);
            supportSkillValue.AddMember("description",
                                      Value().SetString(item.second.GetDescription().c_str(),
                                                        static_cast<SizeType>(item.second.GetDescription().length())),
                                      allocator);
            supportSkillValue.AddMember("id", Value().SetInt(int(item.second.GetId())), allocator);
            supportSkillValue.AddMember("MPCost", Value().SetInt(item.second.GetMPCost()), allocator);
            supportSkillValue.AddMember("HPValue", Value().SetInt(item.second.GetHPValue()), allocator);

            supportSkillsValue.AddMember(
                Value().SetString(item.first.c_str(), static_cast<SizeType>(item.first.length())), supportSkillValue,
                allocator);
        }

        kingValue.AddMember("supportSkills", supportSkillsValue, allocator);
    }
    kings.PushBack(kingValue, allocator);
}
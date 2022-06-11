#include "role/RoleGen.h"
#include "bag/Bag.h"
#include "common/Global.h"
#include "common/Macro.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "text/TextGen.h"

#include <fstream>
using rapidjson::Document;
using rapidjson::kArrayType;
using rapidjson::kObjectType;
using rapidjson::SizeType;
using rapidjson::StringBuffer;
using rapidjson::Value;
using rapidjson::PrettyWriter;
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
 * @return true: login success
 * @throw HAS_PARSE_ERROR
 */
bool RoleGen::InitKing(Map& map) {
    string input, kingData, kingName;

    ifstream ifs(kingFile, ios::in);
    kingData = ReadFormatJson(ifs);
    ifs.close();
    PARSE_DOM_OBJECT(kingDocument, kingData.c_str())

    TextGen::Print(
        "欢迎来到国王排名大陆!在这里，国王需要对每一位子民负责");
    TextGen::Print("而国王自身是否像勇者一样强大就决定了王国的排名");
    TextGen::Print("所以每一位国王都想成为前七名的国王");
    TextGen::Print("以此展开了一次又一次国王之间的厮杀！而年轻的国王，欢迎来到国王排名的世界");
    TextGen::Print<request>("年轻的国王，您拥有自己的领土嘛?(yes/no)");
    while (1) {
        input = TextGen::Input();
        if (input == "yes") {
            TextGen::Print<request>("年轻的国王，我该怎么称呼您呢?");
            kingName = TextGen::Input();
            if (kingName == "quit") {
                TextGen::Print("欢迎下次再来!");
                return false;
            }
            if (LoadKing(kingName)) {
                TextGen::Print("欢迎! 国王." + king.GetName() + "!");
                break;
            } else {
                TextGen::Print<warning>("不好意思，国王，您的王国好像不存在!");
                TextGen::Print<request>("您真的有自己的王国嘛，年轻的国王?(yes/no)");
            }
        } else if (input == "no") {
            TextGen::Print<request>("年轻的国王，我该怎么称呼您呢?");
            kingName = TextGen::Input();
            if (kingName == "quit") {
                TextGen::Print("欢迎下次再来!");
                return false;
            }
            if (CreateKing(kingName, map))
                break;
            else {
                TextGen::Print<warning>("不好意思，没能给您分配一块王国!");
                TextGen::Print<request>("您是不是已经有自己的王国了，年轻的国王?(yes/no)");
            }
        } else if (input == "quit") {
            TextGen::Print("欢迎下次再来!");
            return false;
        } else {
            TextGen::Print<warning>("请输入正确的指令!");
        }
    }
    return true;
}

/**
 * @brief check whether the name is in the json file
 * @param name
 * @param index: if exist, return the index of kingDocument["kings"]
 * @return true: redundancy exists
 */
bool RoleGen::CheckRedundancy(const string& kingName, int& index) {
    string documentName;

    ASSERT_DOM_OBJECT_IS_OBJECT(kingDocument)
    const Value& kings = kingDocument["kings"];
    for (SizeType i = 0; i < kings.Size(); i++) {
        const Value& kingData = kings[i];
        ASSERT_DOM_OBJECT_IS_OBJECT(kingData)
        if (kingData.HasMember("name")) {
            DOM_OBJECT_MEMBER_TO_VAR_STRING(kingData, "name", documentName)
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
    /// @attention current weight don't need to set! just insert!
    king.SetBagCurWeight(0);
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
    TextGen::Print("欢迎, " + kingName + "!");
    TextGen::Print("您有了您自己的领土，这是属于您的王国!");
    TextGen::Print<request>("您的王国叫什么呢?");
    countryName = TextGen::Input();

    /// allocate a new land
    FieldPosition territoryPosition = map.MapExtend(countryName);

    /// randomly choose a birthplace
    Position birthPlace{territoryPosition.fieldX, territoryPosition.fieldY, rand() % fieldSize, rand() % fieldSize};

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
    PrettyWriter<StringBuffer> writer(sb);
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
        WRITE_DOM_OBJECT_MEMBER_STRING(kingData, "name")
        WRITE_DOM_OBJECT_MEMBER_INT(kingData, "level")
        WRITE_DOM_OBJECT_MEMBER_INT(kingData, "attack")
        WRITE_DOM_OBJECT_MEMBER_INT(kingData, "maxHP")
        WRITE_DOM_OBJECT_MEMBER_INT(kingData, "HP")
        WRITE_DOM_OBJECT_MEMBER_INT(kingData, "maxMP")
        WRITE_DOM_OBJECT_MEMBER_INT(kingData, "MP")

        /// position相关
        writer.String("position");
        {
            writer.StartObject();

            WRITE_DOM_OBJECT_MEMBER_INT(kingData["position"], "fieldX")
            WRITE_DOM_OBJECT_MEMBER_INT(kingData["position"], "fieldY")
            WRITE_DOM_OBJECT_MEMBER_INT(kingData["position"], "sceneX")
            WRITE_DOM_OBJECT_MEMBER_INT(kingData["position"], "sceneY")

            writer.EndObject();
        }

        /// king相关
        WRITE_DOM_OBJECT_MEMBER_INT(kingData, "experience")

        /// territory相关
        writer.String("territoryPosition");
        {
            writer.StartObject();

            WRITE_DOM_OBJECT_MEMBER_INT(kingData["territoryPosition"], "fieldX")
            WRITE_DOM_OBJECT_MEMBER_INT(kingData["territoryPosition"], "fieldY")

            writer.EndObject();
        }

        /// 继续king相关
        WRITE_DOM_OBJECT_MEMBER_STRING(kingData, "countryName")
        WRITE_DOM_OBJECT_MEMBER_INT(kingData, "money")

        /// bag相关
        writer.String("bag");
        {
            writer.StartObject();

            WRITE_DOM_OBJECT_MEMBER_INT(kingData["bag"], "level")
            WRITE_DOM_OBJECT_MEMBER_INT(kingData["bag"], "weightLimit")
            WRITE_DOM_OBJECT_MEMBER_INT(kingData["bag"], "curWeight")

            writer.String("medicines");
            {
                writer.StartObject();
                for (auto& m : kingData["bag"]["medicines"].GetObject()) {
                    writer.String(m.name.GetString());
                    writer.Int(m.value.GetInt());
                }
                writer.EndObject();
            }

            writer.String("weapons");
            {
                writer.StartObject();
                for (auto& m : kingData["bag"]["weapons"].GetObject()) {
                    writer.String(m.name.GetString());
                    {
                        /// Weapon相关
                        writer.StartObject();

                        WRITE_DOM_OBJECT_MEMBER_STRING(m.value, "description")
                        WRITE_DOM_OBJECT_MEMBER_INT(m.value, "weight")
                        WRITE_DOM_OBJECT_MEMBER_INT(m.value, "id")
                        WRITE_DOM_OBJECT_MEMBER_INT(m.value, "attack")
                        WRITE_DOM_OBJECT_MEMBER_INT(m.value, "abrasion")
                        WRITE_DOM_OBJECT_MEMBER_INT(m.value, "abrasionLoss")

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
                writer.String(m.name.GetString());
                {
                    writer.StartObject();

                    WRITE_DOM_OBJECT_MEMBER_STRING(m.value, "description")
                    WRITE_DOM_OBJECT_MEMBER_INT(m.value, "MPCost")
                    WRITE_DOM_OBJECT_MEMBER_INT(m.value, "damageValue")

                    writer.EndObject();
                }
            }
            writer.EndObject();
        }

        writer.String("supportSkills");
        {
            writer.StartObject();
            for (auto& m : kingData["supportSkills"].GetObject()) {
                writer.String(m.name.GetString());
                {
                    writer.StartObject();

                    WRITE_DOM_OBJECT_MEMBER_STRING(m.value, "description")
                    WRITE_DOM_OBJECT_MEMBER_INT(m.value, "MPCost")
                    WRITE_DOM_OBJECT_MEMBER_INT(m.value, "HPValue")

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
    ADD_MEMBER_STRING(kingValue, "name", king.GetName())
    ADD_MEMBER_INT(kingValue, "level", king.GetLevel())
    ADD_MEMBER_INT(kingValue, "attack", king.GetAttack())
    ADD_MEMBER_INT(kingValue, "maxHP", king.GetMaxHP())
    ADD_MEMBER_INT(kingValue, "HP", king.GetHP())
    ADD_MEMBER_INT(kingValue, "maxMP", king.GetMaxMP())
    ADD_MEMBER_INT(kingValue, "MP", king.GetMP()) 
    {
        Value positionValue(kObjectType);
        ADD_MEMBER_INT(positionValue, "fieldX", king.GetPosition().fieldX)
        ADD_MEMBER_INT(positionValue, "fieldY", king.GetPosition().fieldY)
        ADD_MEMBER_INT(positionValue, "sceneX", king.GetPosition().sceneX)
        ADD_MEMBER_INT(positionValue, "sceneY", king.GetPosition().sceneY)
        kingValue.AddMember("position", positionValue, allocator);
    }
    ADD_MEMBER_INT(kingValue, "experience", king.GetExperience()) 
    {
        Value territoryPositionValue(kObjectType);
        ADD_MEMBER_INT(territoryPositionValue, "fieldX", king.GetTerritoryPosition().fieldX)
        ADD_MEMBER_INT(territoryPositionValue, "fieldY", king.GetTerritoryPosition().fieldY)
        kingValue.AddMember("territoryPosition", territoryPositionValue, allocator);
    }
    ADD_MEMBER_STRING(kingValue, "countryName", king.GetCountryName())
    ADD_MEMBER_INT(kingValue, "money", king.GetMoney()) 
    {
        Value bagValue(kObjectType);
        ADD_MEMBER_INT(bagValue, "level", king.GetBag().GetLevel())
        ADD_MEMBER_INT(bagValue, "weightLimit", king.GetBag().GetWeightLimit())
        ADD_MEMBER_INT(bagValue, "curWeight", king.GetBag().GetCurWeight()) 
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
                ADD_MEMBER_STRING(weaponValue, "description", item.second.GetDescription())
                ADD_MEMBER_INT(weaponValue, "id", int(item.second.GetItemId()))
                ADD_MEMBER_INT(weaponValue, "weight", item.second.GetWeight())
                ADD_MEMBER_INT(weaponValue, "attack", item.second.GetAttack())
                ADD_MEMBER_INT(weaponValue, "abrasion", item.second.GetAbrasion())
                ADD_MEMBER_INT(weaponValue, "abrasionLoss", item.second.GetAbrasionLoss())

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
            ADD_MEMBER_STRING(attackSkillValue, "description", item.second.GetDescription())
            ADD_MEMBER_INT(attackSkillValue, "id", int(item.second.GetId()))
            ADD_MEMBER_INT(attackSkillValue, "MPCost", item.second.GetMPCost())
            ADD_MEMBER_INT(attackSkillValue, "damageValue", item.second.GetDamageValue())

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
            ADD_MEMBER_STRING(supportSkillValue, "description", item.second.GetDescription())
            ADD_MEMBER_INT(supportSkillValue, "id", int(item.second.GetId()))
            ADD_MEMBER_INT(supportSkillValue, "MPCost", item.second.GetMPCost())
            ADD_MEMBER_INT(supportSkillValue, "HPValue", item.second.GetHPValue())

            supportSkillsValue.AddMember(
                Value().SetString(item.first.c_str(), static_cast<SizeType>(item.first.length())), supportSkillValue,
                allocator);
        }

        kingValue.AddMember("supportSkills", supportSkillsValue, allocator);
    }
    kings.PushBack(kingValue, allocator);
}
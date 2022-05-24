#include "skill/SkillGen.h"
#include "rapidjson/document.h"
#include "common/Config.h"
#include "common/Global.h"

#include <fstream>
using std::ifstream;
using std::ios;
using std::string;
using std::make_pair;
using rapidjson::Document;
using rapidjson::Value;
using rapidjson::SizeType;


/// instantiation
map<string, AttackSkill> SkillGen::attackSkills;
map<string, SupportSkill> SkillGen::supportSkills;

/**
 * @brief Deserialize skills from json file
 * @throw OPEN_FILE_FAIL
 * @throw HAS_PARSE_ERROR
 */
void SkillGen::Init() {
    ifstream ifs(skillFile, ios::in);
    if (ifs.fail())
        throw OPEN_FILE_FAIL;
    string skillData;
    getline(ifs, skillData);

    Document d;
    if (d.Parse(skillData.c_str()).HasParseError())
        throw HAS_PARSE_ERROR;
    if (!d.IsObject())
        throw HAS_PARSE_ERROR;

    string name, description;
    int MPCost, damageValue, HPValue;

    // Attack Skills
    if (!d.HasMember("attackSkills"))
        throw HAS_PARSE_ERROR;
    if (!d["attackSkills"].IsArray())
        throw HAS_PARSE_ERROR;
    const Value& attackSkillsData = d["attackSkills"];
    for (SizeType i = 0; i < attackSkillsData.Size(); i++) {
        const Value& attackSkillData = attackSkillsData[i];
        if (!attackSkillData.IsObject())
            throw HAS_PARSE_ERROR;
        if (!attackSkillData.HasMember("name"))
            throw HAS_PARSE_ERROR;
        name = attackSkillData["name"].GetString();

        if (!attackSkillData.HasMember("description"))
            throw HAS_PARSE_ERROR;
        description = attackSkillData["description"].GetString();

        if (!attackSkillData.HasMember("MPCost"))
            throw HAS_PARSE_ERROR;
        MPCost = attackSkillData["MPCost"].GetInt();

        if (!attackSkillData.HasMember("damageValue"))
            throw HAS_PARSE_ERROR;
        damageValue = attackSkillData["damageValue"].GetInt();

        attackSkills.insert(make_pair(name, AttackSkill{name, description, MPCost, damageValue}));
    }
    

    // Support Skills
    if (!d.HasMember("supportSkills"))
        throw HAS_PARSE_ERROR;
    if (!d["supportSkills"].IsArray())
        throw HAS_PARSE_ERROR;
    const Value& supportSkillsData = d["supportSkills"];
    for (SizeType i = 0; i < supportSkillsData.Size(); i++) {
        const Value& supportSkillData = supportSkillsData[i];
        if (!supportSkillData.IsObject())
            throw HAS_PARSE_ERROR;
        if (!supportSkillData.HasMember("name"))
            throw HAS_PARSE_ERROR;
        name = supportSkillData["name"].GetString();

        if (!supportSkillData.HasMember("description"))
            throw HAS_PARSE_ERROR;
        description = supportSkillData["description"].GetString();

        if (!supportSkillData.HasMember("MPCost"))
            throw HAS_PARSE_ERROR;
        MPCost = supportSkillData["MPCost"].GetInt();

        if (!supportSkillData.HasMember("HPValue"))
            throw HAS_PARSE_ERROR;
        HPValue = supportSkillData["HPValue"].GetInt();

        supportSkills.insert(make_pair(name, SupportSkill{name, description, MPCost, HPValue}));
    }
    

    ifs.close();
}
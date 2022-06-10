#include "role/EnemyGen.h"
#include "role/Enemy.h"
#include "common/Global.h"

#include <string>
#include <fstream>
using std::string;
using std::ifstream;
using std::ios;
using std::getline;

#include "rapidjson/document.h"
using rapidjson::Document;
using rapidjson::Value;
using rapidjson::SizeType;

map<string, Enemy> EnemyGen::enemys;
vector<string> EnemyGen::enemyNames;

/**
 * @brief Deserialize json file into `enemy'
 * @throw OPEN_FILE_FAIL
 */
void EnemyGen::InitEnemy() {
    string enemyString;
    string name, skillName; 
    int MPCost, damageValue, HPValue;
    int level, attack, maxHP, HP, maxMP, MP, experienceVal, moneyVal;


    ifstream ifs(enemyFile, ios::in);
    if (ifs.fail())
        throw OPEN_FILE_FAIL;
    enemyString = ReadFormatJson(ifs);
    ifs.close();

    Document d;
    PARSE_DOM_OBJECT(d, enemyString.c_str())
    ASSERT_DOM_OBJECT_IS_OBJECT(d) 
    ASSERT_DOM_OBJECT_HAS_MEMBER(d, "enemys")

    const Value& enemysValue = d["enemys"];
    ASSERT_DOM_OBJECT_IS_ARRAY(enemysValue)
    for (SizeType i = 0; i < enemysValue.Size(); i++) {
        const Value& enemyValue = enemysValue[i];
        DOM_OBJECT_MEMBER_TO_VAR_STRING(enemyValue, "name", name)
        DOM_OBJECT_MEMBER_TO_VAR_INT(enemyValue, "level", level)
        DOM_OBJECT_MEMBER_TO_VAR_INT(enemyValue, "attack", attack)
        DOM_OBJECT_MEMBER_TO_VAR_INT(enemyValue, "maxHP", maxHP)
        DOM_OBJECT_MEMBER_TO_VAR_INT(enemyValue, "HP", HP)
        DOM_OBJECT_MEMBER_TO_VAR_INT(enemyValue, "maxMP", maxMP)
        DOM_OBJECT_MEMBER_TO_VAR_INT(enemyValue, "MP", MP)
        DOM_OBJECT_MEMBER_TO_VAR_INT(enemyValue, "moneyVal", moneyVal)
        DOM_OBJECT_MEMBER_TO_VAR_INT(enemyValue, "experienceVal", experienceVal)
        Enemy e{name, level, attack, maxHP, HP, maxMP, MP, experienceVal, moneyVal};

        ASSERT_DOM_OBJECT_HAS_MEMBER(enemyValue, "attackSkills")
        const Value& enemyAttackSkills = enemyValue["attackSkills"];
        ASSERT_DOM_OBJECT_IS_OBJECT(enemyAttackSkills)
        for (auto& skill : enemyAttackSkills.GetObject()) {
            skillName = skill.name.GetString();
            DOM_OBJECT_MEMBER_TO_VAR_INT(skill.value, "MPCost", MPCost)
            DOM_OBJECT_MEMBER_TO_VAR_INT(skill.value, "damageValue", damageValue)
            e.MasterAttackSkill(std::move(AttackSkill{skillName, "", MPCost, damageValue}));
        }

        ASSERT_DOM_OBJECT_HAS_MEMBER(enemyValue, "supportSkills")
        const Value& enemySupportSkills = enemyValue["supportSkills"];
        ASSERT_DOM_OBJECT_IS_OBJECT(enemySupportSkills)
        for (auto& skill : enemySupportSkills.GetObject()) {
            skillName = skill.name.GetString();
            DOM_OBJECT_MEMBER_TO_VAR_INT(skill.value, "MPCost", MPCost)
            DOM_OBJECT_MEMBER_TO_VAR_INT(skill.value, "HPValue", HPValue)
            e.MasterSupportSkill(std::move(SupportSkill{skillName, "", MPCost, HPValue}));
        }

        enemys.insert(make_pair(name, std::move(e)));
        enemyNames.push_back(name);
    }
}

const string EnemyGen::GetRandomEnemyName() {
    int index = rand() % (enemyNames.size() + 1);
    if (index == (int)enemyNames.size())
        return "";
    return enemyNames[index];
}
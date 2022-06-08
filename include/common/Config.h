#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
using std::pair;
using std::string;

// 地图相关
const int initialMapSize = 1;                   // 地图的边长(以土地作为单位)
const int extendPlain = 2;                      // 每次增加的平原数量(即无主人的领地)
const string initialFieldName = "Plain";        // 默认土地名:平原
const int fieldSize = 2;                        // 土地的边长
const int plainEnemyPossibilityMax = 100;       // 平原敌人最大概率
const int plainMoneyMax = 1000;                 // 平原金币最大值
const int plainMoneyPossibilityMax = 100;       // 平原金币最大概率
const int plainMedicinePossibilityMax = 100;    // 平原药品最大概率
const int countryMoneyMax = 100;                // 领地金币最大值
const int countryMoneyPossibilityMax = 100;     // 领地金币最大概率
const int countryMedicinePossibilityMax = 100;  // 领地药品最大概率

// 人物相关
const int initialAttack = 1;       // 初始攻击力
const int initialLevel = 1;        // 初始等级
const int initialMaxHP = 100;      // 初始最大生命
const int initialHP = 100;         // 初始生命
const int initialMaxMP = 100;      // 初始最大魔法
const int initialMP = 100;         // 初始魔法
const int initialExperience = 0;   // 初始经验
const int initialMoney = 100;      // 初始金钱
const int escapePossibility = 30;  // 逃跑概率

// 技能相关
const string initialAttackSkills[]{"普通攻击"};
const string initialSupportSkills[]{"治疗术"};

// 背包相关
const int initialBagLevel = 1;          // 初始背包等级
const int initialWeightLimit = 10;      // 初始重量上限
const int levelUpWeightExtend = 2;      // 背包升级增加重量上限值
const int maxWeightLimit = 30;          // 背包最大重量上限值
const int unitWeightLimitPrice = 1000;  // 背包单位容量价格

// 物品相关
const int maxAbrasion = 100;  // 武器的最大磨损量
const pair<string, int> initialMedicines[]{pair<string, int>("肉包", 1), pair<string, int>("魔法丸子", 1)};

// 战斗相关
const int kingFirst = 50;  // 国王先的概率

// 文件相关
#ifdef _WIN32
const string mapFile = "..\\..\\data\\map.json";
const string itemFile = "..\\..\\data\\item.json";
const string kingFile = "..\\..\\data\\king.json";
const string skillFile = "..\\..\\data\\skill.json";
const string enemyFile = "..\\..\\data\\enemy.json";
#else
const string mapFile = "../../data/map.json";
const string itemFile = "../../data/item.json";
const string kingFile = "../../data/king.json";
const string skillFile = "../../data/skill.json";
const string enemyFile = "../../data/enemy.json";
#endif

#endif  // CONFIG_H_
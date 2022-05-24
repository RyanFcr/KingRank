#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
using std::pair;
using std::string;

// 地图相关
const int initialMapSize = 1;  // 地图的边长（以土地作为单位）

/// @attention must be corresponding to the map field size in json!
const int fieldSize = 2;  // 土地的边长

// 人物相关
const int initialAttack = 1;        // 初始攻击力
const int initialLevel = 1;         // 初始等级
const int initialMaxHP = 100;       // 初始最大生命
const int initialHP = 100;          // 初始生命
const int initialMaxMP = 100;       // 初始最大魔法
const int initialMP = 100;          // 初始魔法
const int initialExperience = 100;  // 初始经验
const int initialMoney = 100;       // 初始金钱

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

// 文件相关
#ifdef _WIN32
const string mapFile = "..\\..\\data\\map.json";
const string itemFile = "..\\..\\data\\item.json";
const string kingFile = "..\\..\\data\\king.json";
const string skillFile = "..\\..\\data\\skill.json";
#else
const string mapFile = "../../data/map.json";
const string itemFile = "../../data/item.json";
const string kingFile = "../../data/king.json";
const string skillFile = "../../data/skill.json";
#endif

#endif  // CONFIG_H_
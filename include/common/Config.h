#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
using std::string;

// 地图相关
const int initialMapSize = 1;  // 地图的边长（以土地作为单位）

/// @attention must be corresponding to the map field size in json!
const int fieldSize = 2;  // 土地的边长

// 物品相关
const int maxAbrasion = 100; // 武器的最大磨损量

// 文件相关
#ifdef _WIN32
const string mapFile = "..\\..\\data\\map.json";
const string itemFile = "..\\..\\data\\item.json";
const string kingFile = "..\\..\\data\\king.json";
#else
const string mapFile = "../../data/map.json";
const string itemFile = "../../data/item.json";
const string kingFile = "../../data/king.json";
#endif

#endif  // CONFIG_H_
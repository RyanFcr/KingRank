#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
using std::string;

// 地图相关
const int initialMapSize = 1;  // 地图的边长（以土地作为单位）

/// @attention must be corresponding to the map field size in json!
const int fieldSize = 2;  // 土地的边长

// 文件相关
#ifdef _WIN32
const string mapFile = "..\\..\\data\\map.json";
#else
const string mapFile = "../../data/map.json";
#endif

#endif  // CONFIG_H_
#ifndef MAP_GEN_H
#define MAP_GEN_H

#include "Map.h"
#include "rapidjson/document.h"
using rapidjson::Document;

class MapGen {
   public:
    static void Init();
    static void Free();
    static void Save();

   public:
    static Map map;
};

#endif
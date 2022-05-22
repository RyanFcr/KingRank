#ifndef MAP_GEN_H
#define MAP_GEN_H

#include "Map.h"

class MapGen {
   public:
    static void Init();
    static void MapExend();
    static void Free();

   public:
    static Map map;
};

#endif
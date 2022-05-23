#ifndef ROLEGEN_H_
#define ROLEGEN_H_

#include "map/Map.h"
#include "role/King.h"

class RoleGen {
   public:
    static void InitKing(Map& map);

   private:
    static void SerializeKing();
    static bool LoadKing();
    static bool CreateKing(Map& map);

   public:
    static King king;
};

#endif
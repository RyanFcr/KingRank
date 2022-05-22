#ifndef ROLEGEN_H_
#define ROLEGEN_H_

#include "map/Map.h"
#include "role/King.h"

class RoleGen {
   public:
    static King InitKingGen(Map& map);

   private:
    static bool LoadKing(King& king);
    static bool CreateKing(King& king, Map& map);
};

#endif
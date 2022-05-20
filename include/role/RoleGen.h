#ifndef ROLEGEN_H_
#define ROLEGEN_H_

#include "role/King.h"
#include "map/Map.h"

class RoleGen {
public:
    static King InitKingGen(Map &map);
};

#endif
#ifndef ITEMGEN_H_
#define ITEMGEN_H_

#include "Item.h"
#include "Medicine.h"
#include "Weapon.h"

class ItemGen {
    public:
        static Medicine InitMedicineGen();
        static Weapon InitWeaponGen();
};
// #include "role/King.h"
// #include "map/Map.h"

// class RoleGen {
// public:
//     static King InitKingGen(Map &map);
// };

#endif
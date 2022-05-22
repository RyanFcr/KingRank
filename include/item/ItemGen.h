#ifndef ITEMGEN_H_
#define ITEMGEN_H_

#include "Item.h"
#include "Medicine.h"
#include "Weapon.h"

class ItemGen {
   public:
    static Medicine InitMedicineGen();
    static Weapon InitWeaponGen();
    static void test();
};

#endif
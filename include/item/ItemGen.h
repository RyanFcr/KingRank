#ifndef ITEMGEN_H_
#define ITEMGEN_H_

#include "Item.h"
#include "Medicine.h"
#include "Weapon.h"
#include "rapidjson/document.h"

#include <map>
#include <string>
using std::map;
using std::string;
using rapidjson::Value;

class ItemGen {
   public:
    static void Init();

   private:
    static void InitMedicine(const Value& data);
    static void InitWeapon(const Value& data);

   public:
    static map<string, Medicine> medicines;
    static map<string, Weapon> weapons;
};

#endif
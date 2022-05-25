#ifndef ITEMGEN_H_
#define ITEMGEN_H_

#include "Item.h"
#include "Medicine.h"
#include "Weapon.h"
#include "rapidjson/document.h"

#include <vector>
#include <map>
#include <string>
using std::map;
using std::vector;
using std::string;
using rapidjson::Value;

class ItemGen {
   public:
    static void Init();
    static bool IsMedicineExist(const string &name);
    static bool IsWeaponExist(const string &name);
    static Weapon GetWeapon(const string &name);
    static Medicine GetMedicine(const string &name);
    static string GetRandomMedicineName();
    static string GetRandomWeaponName();

   private:
    static void InitMedicine(const Value& data);
    static void InitWeapon(const Value& data);

   private:
    static map<string, Medicine> medicines;
    static map<string, Weapon> weapons;
    static vector<string> medicineNames;
    static vector<string> weaponNames;
};

#endif
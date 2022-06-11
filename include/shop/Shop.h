#ifndef SHOP_H_
#define SHOP_H_

#include "text/TextGen.h"

#include <string>
#include <vector>
using std::string;
using std::vector;

class Shop {
   public:
    Shop();
    void ShowShopItems() const;
    int GetItemNum() const { return medicines.size() + weapons.size(); }
    int GetMedicineNum() const { return medicines.size(); }
    int GetWeaponNum() const { return weapons.size(); }
    string GetMedicineByIndex(int idx) const { return medicines[idx]; }
    string GetWeaponByIndex(int idx) const { return weapons[idx]; }
    void SellOutMedicineByIndex(int idx) { medicines.erase(medicines.begin() + idx); }
    void SellOutWeaponByIndex(int idx) { weapons.erase(weapons.begin() + idx); }

   private:
    vector<string> medicines;
    vector<string> weapons;
};

#endif
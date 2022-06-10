#include "shop/Shop.h"
#include "item/ItemGen.h"
#include "common/Global.h"

#include <string>
using std::to_string;

Shop::Shop() {
    int medicineNum = NormalDistribution(shopMedicineNumExpect, shopMedicineNumSigma);
    int weaponNum = NormalDistribution(shopWeaponNumExpect, shopWeaponNumSigma);
    /// @attention the shop may be empty
    medicines.reserve(medicineNum);
    for (int i = 0; i < medicineNum; i++) {
        medicines.push_back(ItemGen::GetRandomMedicineName());
    }
    weapons.reserve(weaponNum);
    for (int i = 0; i < weaponNum; i++) {
        weapons.push_back(ItemGen::GetRandomWeaponName());
    }
}

void Shop::ShowShopItems() const {
    TextGen::Print("Medicines:");
    for (size_t i = 0; i < medicines.size(); i++) {
        TextGen::Print(to_string(i) + ". " + medicines[i] + ": ", "");
        TextGen::Print<reward>(to_string(ItemGen::GetMedicine(medicines[i]).GetPrice()), " ");
    }
    TextGen::Print("");
    TextGen::Print("Weapons:");
    for (size_t i = 0; i < weapons.size(); i++) {
        TextGen::Print(to_string(i) + ". " + weapons[i] + ": ", "");
        TextGen::Print<reward>(to_string(ItemGen::GetMedicine(weapons[i]).GetPrice()), " ");
    }
}
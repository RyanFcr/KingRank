#include "shop/Shop.h"
#include "item/ItemGen.h"
#include "common/Global.h"

#include <string>
using std::to_string;

Shop::Shop() {
    int medicineNum = NormalDistribution(shopMedicineNumExpect, shopMedicineNumSigma) + 1;
    int weaponNum = NormalDistribution(shopWeaponNumExpect, shopWeaponNumSigma) + 1;
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
    if (GetItemNum() == 0) {
        TextGen::Print("商店为空!");
        return;
    }

    int ofs1 = medicines.size();
    int ofs2 = ofs1 + weapons.size();

    // 药品
    TextGen::Print<GREEN_>("药品:");
    if (medicines.size()) {
        for (size_t i = 0; i < medicines.size(); i++) {
            TextGen::Print(to_string(i) + ". " + medicines[i] + ": ", "");
            TextGen::Print<reward>(to_string(ItemGen::GetMedicine(medicines[i]).GetPrice()), " ");
        }
    } else {
        TextGen::Print("空", "");
    }
    TextGen::Print("");
    
    // 武器
    TextGen::Print<RED_>("武器:");
    if (weapons.size()) {
        for (size_t i = 0; i < weapons.size(); i++) {
            TextGen::Print(to_string(i + ofs1) + ". " + weapons[i] + ": ", "");
            TextGen::Print<reward>(to_string(ItemGen::GetWeapon(weapons[i]).GetPrice()), " ");
        }
    } else {
        TextGen::Print("空", "");
    }
    TextGen::Print("");

    // 背包
    TextGen::Print<BLUE_>("背包扩容:");
    TextGen::Print(to_string(ofs2) + ". 单位容量: ", "");
    TextGen::Print<reward>(to_string(unitBagSpacePrice));
}
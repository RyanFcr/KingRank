#include "shop/Shop.h"
#include "item/ItemGen.h"

#include <string>
using std::to_string;

void Shop::ShowShopItems() const {
    TextGen::Print("药物:");
    for (size_t i = 0; i < medicines.size(); i++) {
        TextGen::Print(to_string(i) + ". " + medicines[i] + ": ", "");
        TextGen::Print<reward>(to_string(ItemGen::GetMedicine(medicines[i]).GetPrice()), " ");
    }
    TextGen::Print("");
    TextGen::Print("武器:");
    for (size_t i = 0; i < weapons.size(); i++) {
        TextGen::Print(to_string(i) + ". " + weapons[i] + ": ", "");
        TextGen::Print<reward>(to_string(ItemGen::GetMedicine(weapons[i]).GetPrice()), " ");
    }
}
#ifndef ITEM_H_
#define ITEM_H_

#include <string>
using std::string;

enum ItemId {
    WEAPON_ID,
    MEDICINE_ID
};

class Item {
   public:
    Item() {}
    Item(string n, string d, int w, ItemId id)
        : name(n), description(d), weight(w), id(id) {}

    const string& GetName() const { return name; }
    const string& GetDescription() const { return description; }
    int GetWeight() const { return weight; }
    ItemId GetItemId() const { return id; }

   protected:
    string name;         // 物品名称
    string description;  // 物品介绍
    int weight;          // 物品重量
    ItemId id;           // 物品类型
};

#endif  // ITEM_H_
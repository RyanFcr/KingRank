#ifndef ITEM_H_
#define ITEM_H_

#include <string>
using std::string;

#include "rapidjson/writer.h"
using rapidjson::SizeType;

enum ItemId { WEAPON_ID, MEDICINE_ID };

class Item {
   public:
    Item() {}
    Item(string n, string d, int w, ItemId id, int p) : name(n), description(d), weight(w), id(id), price(p) {}

    const string& GetName() const { return name; }
    const string& GetDescription() const { return description; }
    int GetWeight() const { return weight; }
    ItemId GetItemId() const { return id; }
    int GetPrice() const { return price; }

   protected:
    string name;         // 物品名称
    string description;  // 物品介绍
    int weight;          // 物品重量
    ItemId id;           // 物品类型
    int price;           // 物品价格
};

#endif  // ITEM_H_
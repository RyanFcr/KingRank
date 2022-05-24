#ifndef ITEM_H_
#define ITEM_H_

#include <string>
using std::string;

#include "rapidjson/writer.h"
using rapidjson::SizeType;

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

    template <typename Writer>
    void Serialize(Writer& writer) const {
        writer.String("name");
        writer.String(name.c_str(), static_cast<SizeType>(name.length()));
        writer.String("description");
        writer.String(description.c_str(), static_cast<SizeType>(description.length()));
        writer.String("weight");
        writer.Int(weight);
        writer.String("id");
        writer.Int(int(id));
    }

   protected:
    string name;         // 物品名称
    string description;  // 物品介绍
    int weight;          // 物品重量
    ItemId id;           // 物品类型
};

#endif  // ITEM_H_
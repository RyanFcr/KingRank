#ifndef ITEM_H_
#define ITEM_H_

#include <string>
using std::string;

enum ItemId {
    WEAPON_ID,
    MEDICINE_ID
};

class Item {
protected:
    string name; // 物品名称
    string description; //物品介绍 
    int weight; // 物品重量
    ItemId id; // 物品类型
};

#endif // ITEM_H_
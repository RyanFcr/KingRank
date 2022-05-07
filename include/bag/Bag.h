#ifndef BAG_H_
#define BAG_H_

#include <vector>
using std::vector;

#include "Item/Item.h"

class Bag {
private:
    int level; // 背包等级
    int weightLimit; // 重量上限
    int curWeight; // 当前重量
    vector<Item*> items; // 保存的物品
};

#endif // BAG_H_
#ifndef BAG_H_
#define BAG_H_

#include <vector>
using std::vector;

#include "Item/Item.h"

class Bag
{
private:
    int level;            // 背包等级
    int weightLimit;      // 重量上限
    int curWeight;        // 当前重量
    vector<Item *> items; // 保存的物品
    Bag(int _level = 1, int _weightLimit = 10, int _curWeight = 0) : level(_level), weightLimit(_weightLimit), curWeight(_curWeight) {}
};

#endif // BAG_H_
#ifndef BAG_H_
#define BAG_H_

#include <map>
using std::map;

#include "item/Medicine.h"
#include "item/Weapon.h"

class Bag {
   public:
    Bag(int level = 1, int weightLimit = 10, int curWeight = 0)
        : level(level), weightLimit(weightLimit), curWeight(curWeight) {}

    bool Insert(const string& name, int num = 1);
    bool Discard(const string& name, int num = 1);

   private:
    int level;                    // 背包等级
    int weightLimit;              // 重量上限
    int curWeight;                // 当前重量
    map<string, int> medicines;   // 存放的药瓶(数量不定)
    map<string, Weapon> weapons;  // 存放的武器(数量最多为1，但可以强化)
};

#endif  // BAG_H_
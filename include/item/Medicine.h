#ifndef MEDICINE_H_
#define MEDICINE_H_

#include "Item.h"

class Medicine : public Item {
private:
    int HPValue; // 回血量
    int MPValue; // 回魔量
};

#endif // MEDICINE_H_
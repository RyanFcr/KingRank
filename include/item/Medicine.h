#ifndef MEDICINE_H_
#define MEDICINE_H_

#include "Item.h"

class Medicine : public Item {
   public:
    Medicine(string n, string d, int w, int HP, int MP)
        : Item(n, d, w, MEDICINE_ID), HPValue(HP), MPValue(MP) {}

    int GetHPValue() const { return HPValue; }
    int GetMPValue() const { return MPValue; }
    void SetHPValue(int HP) { HPValue = HP; }
    void SetMPValue(int MP) { MPValue = MP; }

   private:
    int HPValue;  // 回血量(百分数)
    int MPValue;  // 回魔量(百分数)
};

#endif  // MEDICINE_H_
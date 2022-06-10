#ifndef EVENTSYSTEM_H_
#define EVENTSYSTEM_H_

#include "role/King.h"

class EventSystem {
   public:
    static void TriggerEvent(King& king, Map& m);

   private:
    static void MoneyEvent(King& king, Scene& s);
    static void MedicineEvent(King& king, Scene& s);
    static void CombatEvent(King& king, Scene& s);
    static void ShopEvent(King& king, Scene& s);
};

#endif
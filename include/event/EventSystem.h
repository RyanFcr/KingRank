#ifndef EVENTSYSTEM_H_
#define EVENTSYSTEM_H_

#include "role/King.h"

class EventSystem {
   public:
    static void TriggerEvent(King& king, const Map& m);

   private:
    static void MoneyEvent(King& king, const Scene& s);
    static void MedicineEvent(King& king, const Scene& s);
    static void CombatEvent(King& king, const Scene& s);
};

#endif
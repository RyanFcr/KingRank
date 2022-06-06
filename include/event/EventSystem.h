#ifndef EVENTSYSTEM_H_
#define EVENTSYSTEM_H_

#include "role/King.h"

class EventSystem {
   public:
    static void TriggerEvent(King& king, const Map& m);
};

#endif
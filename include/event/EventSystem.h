#ifndef EVENTSYSTEM_H_
#define EVENTSYSTEM_H_

#include "mission/MissionGen.h"
#include "role/King.h"

class EventSystem {
   public:
    static void TriggerEvent(King& king, Map& m, vector<Mission>& kingMissions, vector<Mission>& missions);

   private:
    static void MoneyEvent(King& king, Scene& s);
    static void MedicineEvent(King& king, Scene& s);
    static void CombatEvent(King& king, Scene& s, vector<Mission>& kingMissions);
    static void ShopEvent(King& king, Scene& s);
    static void NpcEvent(King& king, Scene& s, vector<Mission>& kingMissions, vector<Mission>& missions);
};

#endif
#ifndef COMBAT_SYSTEM_H_
#define COMBAT_SYSTEM_H_

#include "role/Enemy.h"
#include "role/King.h"
#include "mission/MissionGen.h"

class CombatSystem {
   public:
    static void Combat(King& king, Enemy& enemy, vector<Mission>& kingMissions);

   private:
    static bool CombatProcess(King& king, Enemy& enemy);
    static void CombatWin(King& king, Enemy& enemy);
    static void CombatLose(King& king);

    static void KingTurn(King& king, Enemy& enemy, bool& escape);
    static void EnemyTurn(King& king, Enemy& enemy);
};

#endif
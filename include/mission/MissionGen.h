#ifndef MISSIONGEN_H_
#define MISSIONGEN_H_

#include "mission/Mission.h"
#include <vector>

class MissionGen {
   public:
    static void InitMissions();
    static void InitKingMissions();
    static void ShowMission();

   public:
    static std::vector<Mission> missions;
    static std::vector<Mission> kingMissions;
};
#endif
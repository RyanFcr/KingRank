#ifndef MISSIONGEN_H_
#define MISSIONGEN_H_

#include "mission/Mission.h"
#include <vector>

class MissionGen {
   public:
    static void InitMissions();
    static void InitKingMissions();

   public:
    static std::vector<Mission> missions; // 所有任务
    static std::vector<Mission> kingMissions; // 当前king的任务
};
#endif
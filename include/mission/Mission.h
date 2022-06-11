#ifndef MISSION_H
#define MISSION_H

#include <string>
using std::string;

enum MissionType { NPCMissionType, EnemyMissionType };

class Mission {
   public:
    Mission() {}
    Mission(string kingName,
            string missionName,
            string description,
            int current,
            int total,
            int type,
            string targetName,
            int reward,
            int experience)
        : kingName(kingName),
          missionName(missionName),
          description(description),
          current(current),
          total(total),
          type(MissionType(type)),
          targetName(targetName),
          reward(reward),
          experience(experience) {}

    void IncreaseCurrent() { current++; }
    bool IsFinish() { return current == total; }
    int GetReward() const { return reward; }
    int GetExperience() const { return experience; }
    int GetCurrent() const { return current; }
    int GetTotal() const { return total; }
    string GetTargetName() const { return targetName; }
    string GetMissionName() const { return missionName; }
    string GetDescription() const { return description; }

   private:
    string kingName;     // 标记任务属于哪位国王
    string missionName;  // 任务名
    string description;  // 任务描述
    int current;         // 当前进度，默认为0
    int total;           // 总进度
    MissionType type;    // 任务类型
    string targetName;   // 目标人物名字
    int reward;          // 金币奖励
    int experience;      // 经验奖励
};

#endif
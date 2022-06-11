#ifndef MISSION_H
#define MISSION_H

#include <string>
using std::string;
class Mission {
   public:
    Mission() {}
    Mission(string missionName,
            string description,
            int current,
            int total,
            string kingName,
            string targetName,
            int reward)
        : missionName(missionName),
          description(description),
          current(current),
          total(total),
          kingName(kingName),
          targetName(targetName),
          reward(reward) {}

   public:
    string missionName;
    string description;
    int current;        //当前进度，默认为0
    int total;          //总进度
    string kingName;    //主键，标记任务属于哪位国王
    string targetName;  //任务完成目标名字
    int reward;         //目前只是金币奖励
};

#endif
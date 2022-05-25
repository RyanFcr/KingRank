#ifndef SCENE_H_
#define SCENE_H_

#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class Scene {
   public:
    void Init(string eN, int eP, int m, int mP, string meN, int meP) {
        enemyName = eN;
        enemyPossibility = eP;
        money = m;
        moneyPossibility = mP;
        medicineName = meN;
        medicinePossibility = meP;
    };

   private:
    string enemyName;  // 出现敌人的名字
    int enemyPossibility; // 出现敌人的概率
    int money; // 出现钱的数量
    int moneyPossibility; // 出现钱的概率
    string medicineName; // 出现药品的名字
    int medicinePossibility; // 出现药品的概率
};

#endif  // SCENE_H_
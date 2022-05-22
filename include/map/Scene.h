#ifndef SCENE_H_
#define SCENE_H_

#include <iostream>
using std::cout;
using std::endl;

class Scene {
   public:
    void Init(int id) {
        enemyId = id;
    };

    /// @note: DEBUG
    void display() { cout << enemyId; }

   private:
    int enemyId;  // 出现敌人的id
};

#endif  // SCENE_H_
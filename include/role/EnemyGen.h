#ifndef ENEMYGEN_H_
#define ENEMYGEN_H_

#include <map>
#include <string>
#include "role/Enemy.h"
using std::map;
using std::string;

class EnemyGen {
   public:
    static void InitEnemy();
    static const string GetRandomEnemyName();

   public:
    static map<string, Enemy> enemys;
    static vector<string> enemyNames;
};

#endif
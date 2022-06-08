#include "map/Scene.h"
#include "common/Config.h"
#include "item/ItemGen.h"
#include "role/EnemyGen.h"

void Scene::InitPlainScene() {
    /// @todo enemy!
    enemyName = EnemyGen::GetRandomEnemyName();
    enemyPossibility = rand() % plainEnemyPossibilityMax;
    money = rand() % plainMoneyMax;
    moneyPossibility = rand() % plainMoneyPossibilityMax;
    medicineName = ItemGen::GetRandomMedicineName();
    medicinePossibility = rand() % plainMedicinePossibilityMax;
}

void Scene::InitCountryScene() {
    enemyName = "";
    enemyPossibility = 0;
    money = rand() % countryMoneyMax;
    moneyPossibility = rand() % countryMoneyPossibilityMax;
    medicineName = ItemGen::GetRandomMedicineName();
    medicinePossibility = rand() % countryMedicinePossibilityMax;
}
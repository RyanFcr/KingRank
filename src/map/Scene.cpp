#include "map/Scene.h"
#include "common/Config.h"
#include "item/ItemGen.h"
#include "role/EnemyGen.h"
#include "common/Global.h"

void Scene::InitPlainScene() {
    /// @todo enemy!
    enemyName = EnemyGen::GetRandomEnemyName();
    enemyPossibility = NormalDistribution(plainEnemyExpect, plainEnemySigma);
    money = NormalDistribution(plainMoneyNumExpect, plainMoneyNumSigma);
    moneyPossibility = NormalDistribution(plainMoneyExpect, plainMoneySigma);
    medicineName = ItemGen::GetRandomMedicineName();
    medicinePossibility = NormalDistribution(plainMedicineExpect, plainMedicineSigma);
}

void Scene::InitCountryScene() {
    enemyName = "";
    enemyPossibility = 0;
    money = NormalDistribution(countryMoneyNumExpect, countryMoneyNumSigma);
    moneyPossibility = NormalDistribution(countryMoneyExpect, countryMoneySigma);
    medicineName = ItemGen::GetRandomMedicineName();
    medicinePossibility = NormalDistribution(countryMedicineExpect, countryMedicineSigma);
}
#ifndef SCENE_H_
#define SCENE_H_

#include "common/Macro.h"

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
using rapidjson::SizeType;
using rapidjson::StringBuffer;
using rapidjson::Value;
using rapidjson::Writer;

class Scene {
   public:
    void InitPlainScene();
    void InitCountryScene();
    void Load(const string& eN, int eP, int m, int mP, const string& meN, int meP, int shopP) {
        enemyName = eN;
        enemyPossibility = eP;
        money = m;
        moneyPossibility = mP;
        medicineName = meN;
        medicinePossibility = meP;
        shopPossibility = shopP;
    };

    const string& GetEnemyName() const { return enemyName; }
    int GetEnemyPossibility() const { return enemyPossibility; }
    int GetMoney() const { return money; }
    int GetMoneyPossibility() const { return moneyPossibility; }
    const string& GetMedicineName() const { return medicineName; }
    int GetMedicinePossibility() const { return medicinePossibility; }
    int GetShopPossibility() const { return shopPossibility; }

    void SetMoneyPossibility(int poss) { moneyPossibility = poss; }
    void SetMedicinePossibility(int poss) { medicinePossibility = poss; }

    template <typename Writer>
    void Serialize(Writer& writer) const {
        writer.StartObject();
        SERIALIZE_STRING("enemyName", enemyName)
        SERIALIZE_INT("enemyPossibility", enemyPossibility)
        SERIALIZE_INT("money", money)
        SERIALIZE_INT("moneyPossibility", moneyPossibility)
        SERIALIZE_STRING("medicineName", medicineName)
        SERIALIZE_INT("medicinePossibility", medicinePossibility)
        SERIALIZE_INT("shopPossibility", shopPossibility)
        writer.EndObject();
    }

   private:
    string enemyName;         // 出现敌人的名字
    int enemyPossibility;     // 出现敌人的概率
    int money;                // 出现钱的数量
    int moneyPossibility;     // 出现钱的概率
    string medicineName;      // 出现药品的名字
    int medicinePossibility;  // 出现药品的概率
    int shopPossibility;      // 出现商店的概率
};

#endif  // SCENE_H_
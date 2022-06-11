#include "common/Global.h"
#include "item/ItemGen.h"
#include "map/MapGen.h"
#include "role/RoleGen.h"
#include "role/EnemyGen.h"
#include "skill/SkillGen.h"
#include "text/TextGen.h"
#include "event/EventSystem.h"

int main() {
    srand((unsigned)time(NULL));
    string input;
    bool ret, login;

    ItemGen::Init();
    SkillGen::Init();
    EnemyGen::InitEnemy();
    MapGen::Init();
    TextGen::Init();
    TextGen::PrintTitle();
    login = RoleGen::InitKing(MapGen::map);
    while (login) {
        input = TextGen::Input();
        if (input == "quit") {
            TextGen::Print("欢迎下次再来!");
            RoleGen::SaveKing();
            MapGen::Save();
            break;
        } else if (input == "map") {
            RoleGen::king.ShowMap(MapGen::map);
        } else if (input == "up") {
            ret = RoleGen::king.GoUp(MapGen::map);
            if (ret) EventSystem::TriggerEvent(RoleGen::king, MapGen::map);
        } else if (input == "down") {
            ret = RoleGen::king.GoDown(MapGen::map);
            if (ret) EventSystem::TriggerEvent(RoleGen::king, MapGen::map);
        } else if (input == "right") {
            ret = RoleGen::king.GoRight(MapGen::map);
            if (ret) EventSystem::TriggerEvent(RoleGen::king, MapGen::map);
        } else if (input == "left") {
            ret = RoleGen::king.GoLeft(MapGen::map);
            if (ret) EventSystem::TriggerEvent(RoleGen::king, MapGen::map);
        } else if (input == "home") {
            RoleGen::king.GoHome(MapGen::map);
        } else if (input == "save") {
            RoleGen::SaveKing();
            MapGen::Save();
        } else if (input == "bag") {
            RoleGen::king.ShowBag();
        } else if (input == "money") {
            RoleGen::king.ShowMoney();
        } else if (input == "skill") {
            RoleGen::king.ShowSkills();
        } else if (input == "state") {
            RoleGen::king.ShowState();
        } else
            TextGen::Print<warning>("请输入正确的指令!");
    }
    MapGen::Free();
}
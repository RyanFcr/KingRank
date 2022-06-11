#include "common/Global.h"
#include "event/EventSystem.h"
#include "item/ItemGen.h"
#include "map/MapGen.h"
#include "mission/MissionGen.h"
#include "role/EnemyGen.h"
#include "role/NpcGen.h"
#include "role/RoleGen.h"
#include "skill/SkillGen.h"
#include "text/TextGen.h"

void Help();

int main() {
    srand((unsigned)time(NULL));
    string input;
    bool ret, login;

    TextGen::Init();
    ItemGen::Init();
    SkillGen::Init();
    EnemyGen::InitEnemy();
    MapGen::Init();
    NpcGen::Init();
    MissionGen::InitMissions();
    TextGen::PrintTitle();
    login = RoleGen::InitKing(MapGen::map);
    if (login)
        TextGen::Print<request>("输入help查看提示");
    while (login) {
        input = TextGen::Input();
        if (input == "quit") {
            TextGen::Print("年轻的国王再见!");
            RoleGen::SaveKing();
            MapGen::Save();
            break;
        } else if (input == "map") {
            RoleGen::king.ShowMap(MapGen::map);
        } else if (input == "up") {
            ret = RoleGen::king.GoUp(MapGen::map);
            if (ret)
                EventSystem::TriggerEvent(RoleGen::king, MapGen::map, MissionGen::kingMissions, MissionGen::missions);
        } else if (input == "down") {
            ret = RoleGen::king.GoDown(MapGen::map);
            if (ret)
                EventSystem::TriggerEvent(RoleGen::king, MapGen::map, MissionGen::kingMissions, MissionGen::missions);
        } else if (input == "right") {
            ret = RoleGen::king.GoRight(MapGen::map);
            if (ret)
                EventSystem::TriggerEvent(RoleGen::king, MapGen::map, MissionGen::kingMissions, MissionGen::missions);
        } else if (input == "left") {
            ret = RoleGen::king.GoLeft(MapGen::map);
            if (ret)
                EventSystem::TriggerEvent(RoleGen::king, MapGen::map, MissionGen::kingMissions, MissionGen::missions);
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
        } else if (input == "equip") {
            RoleGen::king.EquipWeapon();
        } else if (input == "drop") {
            RoleGen::king.DropItem();
        } else if (input == "help") {
            Help();
        } else if (input == "mission") {
            MissionGen::ShowMission();
        } else
            TextGen::Print<warning>("请输入正确的指令!");
    }
    MapGen::Free();
}
void Help() {
    TextGen::Print("你可以输入以下指令：");
    TextGen::Print("map: 显示目前你所在的位置以及地图");
    TextGen::Print("up: 在地图中向上走");
    TextGen::Print("down: 在地图中向下走");
    TextGen::Print("left: 在地图中向左走");
    TextGen::Print("right: 在地图中向右走");
    TextGen::Print("home: 回到国王您的王国里");
    TextGen::Print("save: 保存");
    TextGen::Print("bag: 查看您目前的背包");
    TextGen::Print("money: 查看您目前的金钱");
    TextGen::Print("skill: 查看您目前的技能");
    TextGen::Print("state: 查看您目前的状态");
    TextGen::Print("equip: 装备武器");
    TextGen::Print("quit: 退出游戏");
    TextGen::Print("mission:显示任务");
    TextGen::Print("help: 显示帮助");
}
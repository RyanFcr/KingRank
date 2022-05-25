#include "common/Global.h"
#include "item/ItemGen.h"
#include "map/MapGen.h"
#include "role/RoleGen.h"
#include "skill/SkillGen.h"
#include "text/TextGen.h"

int main() {
    srand((unsigned)time(NULL));
    string input;
    ItemGen::Init();
    SkillGen::Init();
    MapGen::Init();
    TextGen::Init();
    TextGen::PrintTitle();
    RoleGen::InitKing(MapGen::map);
    while (1) {
        input = TextGen::Input();
        if (input == "quit") {
            TextGen::Print("Bye!");
            RoleGen::SaveKing();
            MapGen::Save();
            break;
        } else if (input == "map") {
            RoleGen::king.ShowMap(MapGen::map);
        } else if (input == "up") {
            RoleGen::king.GoUp(MapGen::map);
        } else if (input == "down") {
            RoleGen::king.GoDown(MapGen::map);
        } else if (input == "right") {
            RoleGen::king.GoRight(MapGen::map);
        } else if (input == "left") {
            RoleGen::king.GoLeft(MapGen::map);
        } else if (input == "save") {
            RoleGen::SaveKing();
            MapGen::Save();
        } else if (input == "bag") {
            RoleGen::king.ShowBag();
        } else if (input == "money") {
            RoleGen::king.ShowMoney();
        } else if (input == "skill") {
            RoleGen::king.ShowSkill();
        } else
            TextGen::Print<warning>("Invalid Input!");
    }
    MapGen::Free();
}
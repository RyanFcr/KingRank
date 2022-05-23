#include "common/Global.h"
#include "role/RoleGen.h"
#include "text/TextGen.h"
#include "map/MapGen.h"
#include "item/ItemGen.h"

int main() {
    srand((unsigned)time(NULL));
    string input;
    ItemGen::Init();
    MapGen::Init();
    TextGen::Init();
    TextGen::PrintTitle();
    King player = RoleGen::InitKingGen(MapGen::map);
    while (1) {
        input = TextGen::Input();
        if (input == "quit") {
            TextGen::Print("Bye!");
            break;
        } else if (input == "map") {
            player.ShowMap(MapGen::map);
        } else if (input == "up") {
            player.GoUp(MapGen::map);
        } else if (input == "down") {
            player.GoDown(MapGen::map);
        } else if (input == "right") {
            player.GoRight(MapGen::map);
        } else if (input == "left") {
            player.GoLeft(MapGen::map);
        } else
            TextGen::Print<warning>("Invalid Input!");
    }
    MapGen::Free();
}
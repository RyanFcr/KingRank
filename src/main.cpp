#include "map/Map.h"
#include "text/TextGen.h"
#include "role/RoleGen.h"
#include "common/Global.h"

int main() {
    srand((unsigned)time(NULL));
    string input;
    Map map;
    map.Init();
    TextGen::Init();
    TextGen::PrintTitle();
    King player = RoleGen::InitKingGen(map);
    while (1) {
        input = TextGen::Input();
        if (input == "quit") {
            TextGen::Print("Bye!");
            break;
        }
        else if (input == "map") {
            player.ShowMap(map);
        }
        else
            TextGen::Print<warning>("Invalid Input!");
    }
}
#include "map/Map.h"
#include "text/TextGen.h"
#include "role/RoleGen.h"

int main() {
    srand((unsigned)time(NULL));
    string input;
    Map map;
    map.Init();
    // TextGen::PrintTitle();
    // King player = RoleGen::InitKingGen(map);
    // while (1) {
    //     input = TextGen::Input();
    //     if (input == "quit") {
    //         TextGen::PrintText("Bye!");
    //         break;
    //     }
    //     else
    //         TextGen::PrintWarning("hello world!");
    // }
}
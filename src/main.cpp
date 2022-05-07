#include "map/MapGen.h"
#include "text/TextGen.h"
#include "role/RoleGen.h"

int main() {
    string input;
    MapGen mapGen;
    TextGen::PrintTitle();
    King player = RoleGen::InitKingGen();
    while (1) {
        input = TextGen::Input();
        if (input == "quit") {
            TextGen::PrintText("Bye!");
            break;
        }
        else
            TextGen::PrintWarning("hello world!");
    }
}
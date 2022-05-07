#include "map/MapGen.h"
#include "text/TextGen.h"

int main() {
    string input;
    MapGen mapGen;
    TextGen::PrintTitle();
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
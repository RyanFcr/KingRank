#include "role/RoleGen.h"
#include "text/TextGen.h"

King RoleGen::InitKingGen(Map &map) {
    string name;

    /// set king name
    TextGen::PrintRequest("What's your name, young King?");
    name = TextGen::Input();
    /// set kingdom name
    TextGen::PrintText("Welcome, " + name + "!");
    TextGen::PrintText("You have your own territory, your Kingdom!");
    TextGen::PrintRequest("What's country's name?");
    name = TextGen::Input();
    /// allocate a new land
    map.MapExtend(name);
    /// randomly choose a birthplace
    Position birthPlace{fieldNum - 1, rand() % fieldSize, rand() % fieldSize};
    return King(name, birthPlace, fieldNum - 1);
}
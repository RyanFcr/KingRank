#include "role/RoleGen.h"
#include "text/TextGen.h"
#include "common/Global.h"

King RoleGen::InitKingGen(Map &map) {
    string name;

    /// set king name
    TextGen::Print<request>("What's your name, young King?");
    name = TextGen::Input();
    /// set kingdom name
    TextGen::Print("Welcome, " + name + "!");
    TextGen::Print("You have your own territory, your Kingdom!");
    TextGen::Print<request>("What's country's name?");
    name = TextGen::Input();
    /// allocate a new land
    map.MapExtend(name);
    /// randomly choose a birthplace
    Position birthPlace{rand() % initialMapSize, rand() % initialMapSize, rand() % fieldSize, rand() % fieldSize};

    Bag bag;
    
    return King(name, birthPlace, fieldNum - 1);
}
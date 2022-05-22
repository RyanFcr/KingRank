#include "role/RoleGen.h"
#include "text/TextGen.h"
#include "common/Global.h"
#include "bag/Bag.h"

King RoleGen::InitKingGen(Map &map) {
    string input;
    King king{};

    TextGen::Print("Welcome to the world of Kings!");
    TextGen::Print<request>("Do you have your own territory, young King?");
    while (1) {
        input = TextGen::Input();
        if (input == "yes") {
            if (LoadKing(king))
                break;
            else {
                TextGen::Print<warning>("Sorry, your territory doesn't exist!");
                TextGen::Print<request>("Do you really have your own territory, young King?");
            }
        } else if (input == "no") {
            if (CreateKing(king, map))
                break;
            else {
                TextGen::Print<warning>("Sorry, fail to register your territory!");
                TextGen::Print<request>("Have you already had your own territory, young King?");
            }
        } else {
            TextGen::Print<warning>("Invalid Input!");
        }
    }
    return king;
}

bool RoleGen::LoadKing(King &king) {

}

bool RoleGen::CreateKing(King &king, Map &map) {
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
    // map.MapExtend(name);
    /// randomly choose a birthplace
    Position birthPlace{rand() % initialMapSize, rand() % initialMapSize, rand() % fieldSize, rand() % fieldSize};
    FieldPosition territoryPosition{birthPlace.fieldX, birthPlace.fieldY};
    Bag bag;

    king = King{name, birthPlace, territoryPosition, bag};
    return true;
}
#include "role/RoleGen.h"
#include "text/TextGen.h"
#include "common/Global.h"
#include "bag/Bag.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <fstream>
using std::ofstream;
using std::ios;
using rapidjson::Writer;
using rapidjson::StringBuffer;
using rapidjson::SizeType;

/// instantiation
King RoleGen::king;

void RoleGen::InitKing(Map &map) {
    string input;

    TextGen::Print("Welcome to the world of Kings!");
    TextGen::Print<request>("Do you have your own territory, young King?");
    while (1) {
        input = TextGen::Input();
        if (input == "yes") {
            if (LoadKing())
                break;
            else {
                TextGen::Print<warning>("Sorry, your territory doesn't exist!");
                TextGen::Print<request>("Do you really have your own territory, young King?");
            }
        } else if (input == "no") {
            if (CreateKing(map))
                break;
            else {
                TextGen::Print<warning>("Sorry, fail to register your territory!");
                TextGen::Print<request>("Have you already had your own territory, young King?");
            }
        } else {
            TextGen::Print<warning>("Invalid Input!");
        }
    }
}

bool RoleGen::LoadKing() {
    return false;
}

/**
 * @brief create a new king and allocate him with a territory
 * @param map 
 * @return false: creation fail (exist king name) 
 * @throw EXIST_KING
 */
bool RoleGen::CreateKing(Map &map) {
    string kingName, countryName;

    /// set king name
    TextGen::Print<request>("What's your name, young King?");
    kingName = TextGen::Input();

    /// set kingdom name
    TextGen::Print("Welcome, " + kingName + "!");
    TextGen::Print("You have your own territory, your Kingdom!");
    TextGen::Print<request>("What's your country's name?");
    countryName = TextGen::Input();

    /// allocate a new land
    // map.MapExtend(name);

    /// randomly choose a birthplace and territory
    Position birthPlace{rand() % initialMapSize, rand() % initialMapSize, rand() % fieldSize, rand() % fieldSize};
    FieldPosition territoryPosition{birthPlace.fieldX, birthPlace.fieldY};

    /// construct king
    king = King{kingName, countryName, birthPlace, territoryPosition};

    // Serialize `king' into json file
    SerializeKing();

    return true;
}

/**
 * @brief Serialize `king' into the json file
 * @throw OPEN_FILE_FAIL
 */
void RoleGen::SerializeKing() {
    ofstream ofs(kingFile, ios::out);
    if (ofs.fail())
        throw OPEN_FILE_FAIL;
    
    StringBuffer sb;
    Writer<StringBuffer> writer(sb);

    king.Serialize(writer);
    string kingData = sb.GetString();
    ofs << kingData;
    
    ofs.close();
}
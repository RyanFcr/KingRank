#include "role/NpcGen.h"
#include "role/Npc.h"

#include <map>
#include <string>
#include <vector>
using std::map;
using std::string;
using std::vector;

map<Position, Npc, decltype(PositionCmp)*> NpcGen::Npcs;
vector<string> NpcGen::NpcNames;

bool PositionCmp(const Position& p1, const Position& p2) {
    return p1.fieldX > p2.fieldX && p1.fieldY > p2.fieldY && p1.sceneX > p2.sceneX && p1.sceneY > p2.sceneY;
}

/**
 * @brief Deserialize json file into `Npc'
 * @throw OPEN_FILE_FAIL
 */
void NpcGen::InitNpc() {}
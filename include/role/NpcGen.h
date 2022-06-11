#ifndef NPCGEN_H
#define NPCGEN_H

#include <string>
#include <utility>
#include <vector>
#include "common/Global.h"
#include "role/Npc.h"

using std::pair;
using std::string;
using std::vector;

bool PositionCmp(const Position& p1, const Position& p2);

class NpcGen {
   public:
    static void InitNpc();

   public:
    static map<Position, Npc, decltype(PositionCmp)*> Npcs;
    static vector<string> NpcNames;
};

#endif
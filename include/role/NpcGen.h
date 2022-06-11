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

struct KeyCmp {
    bool operator()(const Position& p1, const Position& p2) const {
        if (p1.fieldX != p2.fieldX) return p1.fieldX < p2.fieldX;
        if (p1.fieldY != p2.fieldY) return p1.fieldY < p2.fieldY;
        if (p1.sceneX != p2.sceneX) return p1.sceneX < p2.sceneX;
        if (p1.sceneY != p2.sceneY) return p1.sceneY < p2.sceneY;
        return false;
    }
};

class NpcGen {
   public:
    static void Init();

   public:
    static map<Position, Npc, KeyCmp> Npcs;
    static vector<string> NpcNames;
};

#endif
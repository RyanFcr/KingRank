#ifndef NPC_H
#define NPC_H
#include <map>
#include <string>
#include "common/Global.h"

using std::map;
using std::string;

class Npc {
   public:
    Npc() {}
    Npc(string name) : name(name) {}
    void SetPosition(const Position& p) { position = p; }
    void InsertStatement(const string& input, const string& output) { 
        NpcStatements.insert(std::make_pair(input, output));
    }

    void NpcSpeak(string key);

   private:
    string name;
    map<string, string> NpcStatements;  // 0对应的是NPC讲的第一句话
    Position position;
};

#endif

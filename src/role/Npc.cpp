#include "role/Npc.h"
#include "text/TextGen.h"
#include <map>
#include <string>

/**
 * @brief communicate with Npcs
 * 
 * @param key 
 */
void Npc::NpcSpeak(string key) {
    map<string, string>::iterator it_find;
    it_find = Npc::NpcStatements.find(key);
    if (it_find != Npc::NpcStatements.end()) {
        string s = Npc::NpcStatements[key];
        TextGen::Print<reward>(s);
    }else
    {
        TextGen::Print<reward>("麻麻和我说不要和陌生人说话");
    }
}
#ifndef ROLEGEN_H_
#define ROLEGEN_H_

#include "map/Map.h"
#include "role/King.h"
#include "role/Enemy.h"

#include "rapidjson/document.h"
using rapidjson::Document;

class RoleGen {
   public:
    static void InitKing(Map& map);
    static void InitEnemy();
    static void SaveKing();

   private:
    static bool LoadKing(const string& kingName);
    static bool CreateKing(const string& kingName, Map& map);
    static bool CheckRedundancy(const string& name, int& index);
    static void AppendKing();

   public:
    static King king;
    static map<string, Enemy> enemys;

   private:
    static Document kingDocument;
};

#endif
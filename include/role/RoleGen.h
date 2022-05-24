#ifndef ROLEGEN_H_
#define ROLEGEN_H_

#include "map/Map.h"
#include "role/King.h"

#include "rapidjson/document.h"
using rapidjson::Document;

class RoleGen {
   public:
    static void InitKing(Map& map);
    static void SaveKing();

   private:
    static bool LoadKing();
    static bool CreateKing(Map& map);
    static bool CheckRedundancy(string name);
    static void AppendKing();

   public:
    static King king;

   private:
    static Document kingDocument;
};

#endif
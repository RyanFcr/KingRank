#include "role/NpcGen.h"
#include "role/Npc.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "text/TextGen.h"
#include "common/Config.h"

#include <map>
#include <string>
#include <vector>
#include <fstream>
using std::map;
using std::string;
using std::vector;
using std::ifstream;
using std::ios;
using rapidjson::Document;
using rapidjson::SizeType;
using rapidjson::Value;

map<Position, Npc, KeyCmp> NpcGen::Npcs;
vector<string> NpcGen::NpcNames;

/**
 * @brief Deserialize json file into `Npc'
 * @throw OPEN_FILE_FAIL
 */
void NpcGen::Init() {
    string npcData;
    Document npcDocument;

    ifstream ifs(npcFile, ios::in);
    npcData = ReadFormatJson(ifs);
    ifs.close();
    PARSE_DOM_OBJECT(npcDocument, npcData.c_str())
    ASSERT_DOM_OBJECT_HAS_MEMBER(npcDocument, "Npcs")
    ASSERT_DOM_OBJECT_IS_ARRAY(npcDocument["Npcs"])

    const Value& npcsValue = npcDocument["Npcs"];
    for (SizeType i = 0; i < npcsValue.Size(); i++) {
        const Value& npcValue = npcsValue[i];
        ASSERT_DOM_OBJECT_IS_OBJECT(npcValue)

        string name;
        Position p;
        // name
        ASSERT_DOM_OBJECT_HAS_MEMBER(npcValue, "name")
        DOM_OBJECT_MEMBER_TO_VAR_STRING(npcValue, "name", name)
        Npc npc{name};
        // position
        ASSERT_DOM_OBJECT_HAS_MEMBER(npcValue, "position")
        ASSERT_DOM_OBJECT_IS_OBJECT(npcValue["position"])
        {
            ASSERT_DOM_OBJECT_HAS_MEMBER(npcValue["position"], "fieldX")
            DOM_OBJECT_MEMBER_TO_VAR_INT(npcValue["position"], "fieldX", p.fieldX)
            ASSERT_DOM_OBJECT_HAS_MEMBER(npcValue["position"], "fieldY")
            DOM_OBJECT_MEMBER_TO_VAR_INT(npcValue["position"], "fieldY", p.fieldY)
            ASSERT_DOM_OBJECT_HAS_MEMBER(npcValue["position"], "sceneX")
            DOM_OBJECT_MEMBER_TO_VAR_INT(npcValue["position"], "sceneX", p.sceneX)
            ASSERT_DOM_OBJECT_HAS_MEMBER(npcValue["position"], "sceneY")
            DOM_OBJECT_MEMBER_TO_VAR_INT(npcValue["position"], "sceneY", p.sceneY)
        }
        // statement
        ASSERT_DOM_OBJECT_HAS_MEMBER(npcValue, "NpcStatements")
        ASSERT_DOM_OBJECT_IS_OBJECT(npcValue["NpcStatements"])
        for (auto& m : npcValue["NpcStatements"].GetObject()) {
            string input = m.name.GetString();
            string output = m.value.GetString();
            npc.InsertStatement(input, output);
        }
        npc.SetPosition(p);
        Npcs.insert(std::make_pair(p, npc));
    }
}
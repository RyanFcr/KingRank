#include "mission/MissionGen.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "common/Config.h"
#include "common/Global.h"

#include <fstream>
using std::ifstream;
using std::ios;
using rapidjson::Document;
using rapidjson::SizeType;
using rapidjson::Value;

std::vector<Mission> MissionGen::missions;
std::vector<Mission> MissionGen::kingMissions;

void MissionGen::InitMissions() {
    string missionData;
    Document missionDocument;

    ifstream ifs(missionFile, ios::in);
    missionData = ReadFormatJson(ifs);
    ifs.close();
    PARSE_DOM_OBJECT(missionDocument, missionData.c_str())
    ASSERT_DOM_OBJECT_HAS_MEMBER(missionDocument, "missions")
    ASSERT_DOM_OBJECT_IS_ARRAY(missionDocument["missions"])

    for (SizeType i = 0; i < missionDocument["missions"].Size(); i++) {
        const Value& missionVal = missionDocument["missions"][i];
        ASSERT_DOM_OBJECT_IS_OBJECT(missionVal)
        std::string missionName, description, targetName;
        int current, total, type, reward, experience; 
        // missionName
        ASSERT_DOM_OBJECT_HAS_MEMBER(missionVal, "missionName")
        DOM_OBJECT_MEMBER_TO_VAR_STRING(missionVal, "missionName", missionName)
        // description
        ASSERT_DOM_OBJECT_HAS_MEMBER(missionVal, "description")
        DOM_OBJECT_MEMBER_TO_VAR_STRING(missionVal, "description", description)
        // current
        ASSERT_DOM_OBJECT_HAS_MEMBER(missionVal, "current")
        DOM_OBJECT_MEMBER_TO_VAR_INT(missionVal, "current", current)
        // total
        ASSERT_DOM_OBJECT_HAS_MEMBER(missionVal, "total")
        DOM_OBJECT_MEMBER_TO_VAR_INT(missionVal, "total", total)
        // type
        ASSERT_DOM_OBJECT_HAS_MEMBER(missionVal, "type")
        DOM_OBJECT_MEMBER_TO_VAR_INT(missionVal, "type", type)
        // targetName
        ASSERT_DOM_OBJECT_HAS_MEMBER(missionVal, "targetName")
        DOM_OBJECT_MEMBER_TO_VAR_STRING(missionVal, "targetName", targetName)
        // reward
        ASSERT_DOM_OBJECT_HAS_MEMBER(missionVal, "reward")
        DOM_OBJECT_MEMBER_TO_VAR_INT(missionVal, "reward", reward)
        // experience
        ASSERT_DOM_OBJECT_HAS_MEMBER(missionVal, "experience")
        DOM_OBJECT_MEMBER_TO_VAR_INT(missionVal, "experience", experience)

        missions.emplace_back(Mission{"", missionName, description, current, total, type, targetName, reward, experience});
    }
}
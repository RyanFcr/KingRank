# recursive files
FILE(GLOB_RECURSE KingRank_SOURCE ${PROJECT_SOURCE_DIR}/src/*/*.cpp
        )

ADD_LIBRARY(KingRank_obj OBJECT ${KingRank_SOURCE})
TARGET_LINK_LIBRARIES(KingRank_obj)

ADD_EXECUTABLE(main main.cpp)
TARGET_LINK_LIBRARIES(main KingRank_obj)
# recursive files
FILE(GLOB_RECURSE ${PROJECT_SOURCE_DIR}/src/*/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*/*/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*/*.c
        ${PROJECT_SOURCE_DIR}/src/*/*/*.c
        )
ADD_EXECUTABLE(main main.cpp)
TARGET_LINK_LIBRARIES(main)
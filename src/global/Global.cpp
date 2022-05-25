#include "common/Global.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using rapidjson::Writer;
using rapidjson::StringBuffer;

/**
 * @brief Normalize the position
 */
void Position::Normalize() {
    while (sceneX < 0) {
        sceneX += fieldSize;
        fieldX -= 1;
    }
    while (sceneX >= fieldSize) {
        sceneX -= fieldSize;
        fieldX += 1;
    }

    while (sceneY < 0) {
        sceneY += fieldSize;
        fieldY -= 1;
    }
    while (sceneY >= fieldSize) {
        sceneY -= fieldSize;
        fieldY += 1;
    }
}

void Position::GoUp() {
    sceneX++;
    Normalize();
}

void Position::GoDown() {
    sceneX--;
    Normalize();
}

void Position::GoLeft() {
    sceneY--;
    Normalize();
}

void Position::GoRight() {
    sceneY++;
    Normalize();
}
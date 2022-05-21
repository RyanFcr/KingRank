#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "Config.h"
#include "Macro.h"

static int fieldNum = initialMapSize * initialMapSize;

const int maxTerminalLenghth = 100;

/// Text Type
const int plain = RESET_;
const int request = CYAN_;
const int reward = YELLOW_;
const int warning = RED_;
const int buff = GREEN_;
const int title = YELLOW_;

/// Error Type
enum KRerror {
    OPEN_FILE_FAIL,
    HAS_PARSE_ERROR

};

/// Position Type
struct Position {
    int fieldX;
    int fieldY;
    int sceneX;
    int sceneY;

    void Normalize();
    void GoUp();
    void GoDown();
    void GoLeft();
    void GoRight();
};

#endif
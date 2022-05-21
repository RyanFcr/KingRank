#include "common/Global.h"

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
    sceneY++; 
    Normalize(); 
}

void Position::GoDown() { 
    sceneY--; 
    Normalize(); 
}

void Position::GoLeft() { 
    sceneX--; 
    Normalize();
}

void Position::GoRight() { 
    sceneX++; 
    Normalize(); 
}
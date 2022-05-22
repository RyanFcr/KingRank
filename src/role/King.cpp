#include "role/King.h"

void King::ShowMap(const Map &m) const {
    TextGen::PrintDirection(m, position);
}

void King::GoUp(const Map &m) {
    position.GoUp();
    if (!(m.IsValidPosition(position))) {
        position.GoDown();
        TextGen::Print<warning>("Can't go up!");
    }
}

void King::GoDown(const Map &m) {
    position.GoDown();
    if (!(m.IsValidPosition(position))) {
        position.GoUp();
        TextGen::Print<warning>("Can't go down!");
    }
}

void King::GoLeft(const Map &m) {
    position.GoLeft();
    if (!(m.IsValidPosition(position))) {
        position.GoRight();
        TextGen::Print<warning>("Can't go left!");
    }
}

void King::GoRight(const Map &m) {
    position.GoRight();
    if (!(m.IsValidPosition(position))) {
        position.GoLeft();
        TextGen::Print<warning>("Can't go right!");
    }
}
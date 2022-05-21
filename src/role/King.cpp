#include "role/King.h"

void King::ShowMap(const Map &m) {
    TextGen::PrintDirection(m, position);
}
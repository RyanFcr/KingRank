#include "map/Field.h"

void Field::InitScenes() {
    if (name != initialFieldName) {
        for (int i = 0; i < fieldSize; i++)
            for (int j = 0; j < fieldSize; j++)
                field[i][j].InitCountryScene();
    } else {
        for (int i = 0; i < fieldSize; i++)
            for (int j = 0; j < fieldSize; j++)
                field[i][j].InitPlainScene();
    }
}
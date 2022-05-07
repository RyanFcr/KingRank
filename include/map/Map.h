#ifndef MAP_H_
#define MAP_H_

#include <vector>
using std::vector;

#include "Field.h"

class Map {
public:
    Map() : fields(vector<Field*>{initialFieldNum}) {
        
    }
private:
    vector<Field*> fields;
};

#endif // MAP_H_
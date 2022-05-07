#include "role/RoleGen.h"
#include "text/TextGen.h"

#include <sstream>
using std::stringstream;

King RoleGen::InitKingGen() {
    stringstream ss;
    string name;
    TextGen::PrintRequest("What's your name, young King?");
    name = TextGen::Input();
    return King(name);
}
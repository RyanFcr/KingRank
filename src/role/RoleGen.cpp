#include "role/RoleGen.h"
#include "text/TextGen.h"

King RoleGen::InitKingGen() {
    string name;
    TextGen::PrintRequest("What's your name, young King?");
    name = TextGen::Input();
    return King(name);
}
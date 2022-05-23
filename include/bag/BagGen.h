#ifndef BAG_GEN_H
#define BAG_GEN_H

#include "bag/Bag.h"
/**
 * @brief Generate Bag (only call in the `RoleGen' )
 */
class BagGen {
   public:
    static void Init(Bag &bag);
};

#endif
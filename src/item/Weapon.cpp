#include "item/Weapon.h"

/**
 * @brief decrease the abrsion each time the weapon is used
 * @return true: the weapon is broken
 * @return false: the weapon can still be used
 */
bool Weapon::Abrase() {
    abrasion -= abrasionLoss;
    if (abrasion <= 0)
        return true;
    return false;
}
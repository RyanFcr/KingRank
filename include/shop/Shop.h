#ifndef SHOP_H_
#define SHOP_H_

#include "text/TextGen.h"

#include <string>
#include <vector>
using std::string;
using std::vector;

class Shop {
   public:
    Shop();
    void ShowShopItems() const;
   private:
    vector<string> medicines;
    vector<string> weapons;
};

#endif
//
//  Spear.h
//  TactiX
//
//  Created by giginet on 2013/6/10.
//
//

#ifndef __TactiX__Spear__
#define __TactiX__Spear__

#include <iostream>
#include "Weapon.h"

class Spear :public Weapon {
  public:
    Spear();
    bool canAttack(CCPoint relPos);
    std::string getWeaponName();
};

#endif /* defined(__TactiX__Spear__) */

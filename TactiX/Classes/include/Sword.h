//
//  Sword.h
//  TactiX
//
//  Created by giginet on 2013/6/10.
//
//

#ifndef __TactiX__Sword__
#define __TactiX__Sword__

#include <iostream>
#include "Weapon.h"

class Sword :public Weapon {
  public:
    Sword();
    bool canAttack(CCPoint relPos);
    int getMoveCapacity();
};

#endif /* defined(__TactiX__Sword__) */

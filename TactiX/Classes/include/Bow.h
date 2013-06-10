//
//  Bow.h
//  TactiX
//
//  Created by giginet on 2013/6/10.
//
//

#ifndef __TactiX__Bow__
#define __TactiX__Bow__

#include <iostream>
#include "Weapon.h"

class Bow :public Weapon {
  public:
    Bow();
    bool canAttack(CCPoint relPos);
};

#endif /* defined(__TactiX__Bow__) */

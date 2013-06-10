//
//  Sword.cpp
//  TactiX
//
//  Created by giginet on 2013/6/10.
//
//

#include "Sword.h"

Sword::Sword() {
}

bool Sword::canAttack(cocos2d::CCPoint relPos) {
    return true;
}

int Sword::getMoveCapacity() {
    return 1;
}
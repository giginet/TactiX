//
//  Sword.cpp
//  TactiX
//
//  Created by giginet on 2013/6/10.
//
//

#include "Sword.h"

Sword::Sword(WeaponType type) :Weapon(type) {
}

bool Sword::canAttack(cocos2d::CCPoint relPos) {
    // 周囲8方向のみ
    return (abs(relPos.x) == 1 ^ abs(relPos.y) == 1);
}

int Sword::getMoveCapacity() {
    return 1;
}

std::string Sword::getWeaponName() {
    return "剣";
}
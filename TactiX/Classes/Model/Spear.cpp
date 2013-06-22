//
//  Spear.cpp
//  TactiX
//
//  Created by giginet on 2013/6/10.
//
//

#include "Spear.h"

Spear::Spear(WeaponType type) :Weapon(type) {
}

bool Spear::canAttack(cocos2d::CCPoint relPos) {
    // 自分の隣２マス（十字）の相手に攻撃可能
    return (relPos.x == 0 && abs(relPos.y) <= 2) || (abs(relPos.x) <= 2 && relPos.y == 0);
}

std::string Spear::getWeaponName() {
    return "槍";
}
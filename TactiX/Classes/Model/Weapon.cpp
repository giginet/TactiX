//
//  Weapon.cpp
//  TactiX
//
//  Created by giginet on 2013/6/10.
//
//

#include "Weapon.h"

Weapon::Weapon() : _type(WeaponTypeNone) {
}

Weapon::~Weapon() {
}

bool Weapon::canAttack(CCPoint relPos) {
    return false;
}

int Weapon::getMoveCapacity() {
    return 0;
}

WeaponType Weapon::getType() {
    return _type;
}

void Weapon::setType(WeaponType type) {
    _type = type;
}

bool Weapon::canWin(Weapon *other) {
    //固体＜液体＜プラズマ＜固体
    return _type == WeaponTypeSolid && other->getType() == WeaponTypeLiquid &&
    _type == WeaponTypeLiquid && other->getType() == WeaponTypePlasma &&
    _type == WeaponTypePlasma && other->getType() == WeaponTypeSolid;
}
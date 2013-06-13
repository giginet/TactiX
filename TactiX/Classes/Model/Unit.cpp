//
//  Unit.cpp
//  TactiX
//
//  Created by giginet on 2013/6/10.
//
//

#include "Unit.h"

Unit::Unit(const char *characterName) {
    if (this->initWithFile("unit.png")) {
        _weapons = CCArray::create();
        _weapons->retain();
        
    }
}

Unit::~Unit() {
    if (_weapons) {
        _weapons->release();
    }
}

int Unit::getMoveCapacity() {
    return 5;
}

CCArray *Unit::getWeapons() {
    return _weapons;
}

Weapon *Unit::getWeapon(int currentTurn) {
    return dynamic_cast<Weapon *>(_weapons->objectAtIndex(currentTurn % 3));
}

void Unit::setWeapons(cocos2d::CCArray *weapons) {
    if (_weapons) {
        _weapons->release();
    }
    _weapons = weapons;
    CCAssert(weapons && weapons->count() == 3, "a length of weapons must be 3.");
    if (weapons) {
        weapons->retain();
    }
}
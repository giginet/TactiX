//
//  Unit.cpp
//  TactiX
//
//  Created by giginet on 2013/6/10.
//
//

#include "Unit.h"
#include <boost/lexical_cast.hpp>

using namespace boost;

Unit::Unit(const char *characterName, int ownerID) : _ownerID(ownerID) {
    if (this->initWithFile((string("unit") + lexical_cast<string>(ownerID) + ".png").c_str())) {
        _weapons = CCArray::create();
        _weapons->retain();
        _currentWeaponIndex = 0;
    }
}

Unit::~Unit() {
    if (_weapons) {
        _weapons->release();
    }
}

Unit *Unit::create(const char *characterName, int ownerID) {
    Unit *unit = new Unit(characterName, ownerID);
    unit->autorelease();
    return unit;
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

int Unit::getOwnerID() {
    return _ownerID;
}

void Unit::setOwnerID(int ownerID) {
    _ownerID = ownerID;
}

void Unit::nextWeapon() {
    _currentWeaponIndex = (_currentWeaponIndex + 1) % 3;
}

Weapon *Unit::getCurrentWeapon() {
    return dynamic_cast<Weapon *>(_weapons->objectAtIndex(_currentWeaponIndex));
}
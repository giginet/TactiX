//
//  Unit.cpp
//  TactiX
//
//  Created by giginet on 2013/6/10.
//
//

#include "Unit.h"
#include <boost/lexical_cast.hpp>
#include "Bow.h"
#include "Sword.h"
#include "Spear.h"

using namespace boost;

Unit::Unit(const char *characterName, int ownerID) : _ownerID(ownerID) {
    if (this->initWithFile((string("unit") + lexical_cast<string>(ownerID) + ".png").c_str())) {
        _weapons = CCArray::create();
        _weapons->retain();
        _currentWeaponIndex = 0;
        
        // 仮で適当なWeaponを作る
        Weapon *random0 = new Bow((WeaponType)(rand() % 3));
        Weapon *random1 = new Sword((WeaponType)(rand() % 3));
        Weapon *random2 = new Spear((WeaponType)(rand() % 3));
        CCArray *weapons = CCArray::create(random0, random1, random2, NULL);
        this->setWeapons(weapons);
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
//
//  Character.cpp
//  TactiX
//
//  Created by giginet on 2013/6/10.
//
//

#include "Character.h"
#include "Weapon.h"
#include "Sword.h"
#include "Bow.h"
#include "Spear.h"
#include <boost/shared_ptr.hpp>

using namespace boost;

Character::Character(const char *characterName) :_name("") {
    _lua = LuaObject::create(characterName);
    _lua->retain();
    _name = _lua->getString("name");
    _defaultWeapons = CCArray::create();
    _defaultWeapons->retain();
    boost::shared_ptr<CCLuaValueArray> array = _lua->getArray("defaultWeapons");
    for (CCLuaValueArrayIterator it = array->begin(); it != array->end(); ++it) {
        CCLuaValueArray weaponInfo = it->arrayValue();
        int i = 0;
        WeaponKind kind = WeaponKindNone;
        WeaponType type = WeaponTypeNone;
        for (CCLuaValueArrayIterator itt = weaponInfo.begin(); itt != weaponInfo.end(); ++itt) {
            if (i == 0) {
                kind = (WeaponKind)itt->intValue();
            } else {
                type = (WeaponType)itt->intValue();
            }
        }
        if (kind == WeaponKindSword) {
            Sword *sword = new Sword(type);
            sword->autorelease();
            _defaultWeapons->addObject(sword);
        } else if (kind == WeaponKindSpear) {
            Spear *spear = new Spear(type);
            spear->autorelease();
            _defaultWeapons->addObject(spear);
        } else if (kind == WeaponKindBow) {
            Bow *bow = new Bow(type);
            bow->autorelease();
            _defaultWeapons->addObject(bow);
        }
    }
}

Character::~Character() {
    _lua->release();
    _defaultWeapons->release();
}

string Character::getName() {
    return _name;
}

CCArray *Character::getDefaultWeapons() {
    return _defaultWeapons;
}


//
//  UnitManager.cpp
//  TactiX
//
//  Created by giginet on 2013/6/22.
//
//

#include "UnitManager.h"
#include "Match.h"

using namespace cocos2d;

UnitManager::UnitManager() {
    _units = CCArray::create();
    _units->retain();
}

UnitManager::~UnitManager() {
    _units->release();
}

void UnitManager::addUnit(Unit *unit, const CCPoint &mapPoint) {
    Map *map = Match::getCurrentMatch()->getMap();
    CCPoint position = map->convertToWorld(mapPoint);
    unit->setPosition(position);
    _units->addObject(unit);
    map->getTiledMap()->addChild(unit, MapZOrderUnit);
}

void UnitManager::moveUnit(Unit *unit, const cocos2d::CCPoint &mapPoint) {
    Map *map = Match::getCurrentMatch()->getMap();
    if (this->canMove(unit, mapPoint)) {
        unit->setPosition(map->convertToWorld(mapPoint));
    }
}

void UnitManager::removeUnit(Unit *unit) {
    if (_units->containsObject(unit)) {
        Map *map = Match::getCurrentMatch()->getMap();
        map->getTiledMap()->removeChild(unit);
        _units->removeObject(unit);
    }
}

bool UnitManager::canMove(Unit *unit, const cocos2d::CCPoint &mapPoint) {
    Map *map = Match::getCurrentMatch()->getMap();
    if (_units->containsObject(unit)) {
        CCPoint unitPoint = map->convertToMapSpace(unit->getPosition());
        return (Map::getManhattanDistance(mapPoint, unitPoint) <= unit->getMoveCapacity());
    }
    return false;
}

Unit *UnitManager::getUnitOn(CCPoint mapPoint) {
    Map *map = Match::getCurrentMatch()->getMap();
    CCObject* obj = NULL;
    CCARRAY_FOREACH(_units, obj) {
        Unit *unit = dynamic_cast<Unit *>(obj);
        CCPoint unitMapPosition = map->convertToMapSpace(unit->getPosition());
        if (unitMapPosition.x == mapPoint.x && unitMapPosition.y == mapPoint.y) {
            return unit;
        }
    }
    return NULL;
}

CCArray *UnitManager::getAttackTargets(Unit *unit) {
    CCArray *array = CCArray::create();
    Map *map = Match::getCurrentMatch()->getMap();
    CCObject* obj = NULL;
    CCPoint mapPos = map->convertToMapSpace(unit->getPosition());
    CCARRAY_FOREACH(_units, obj) {
        Unit *other = dynamic_cast<Unit *>(obj);
        if (other != unit) {
            CCPoint otherMapPos = map->convertToMapSpace(other->getPosition());
            CCPoint rel = ccpSub(otherMapPos, mapPos);
            if (unit->getCurrentWeapon()->canAttack(rel) ) {
                array->addObject(unit);
            }
        }
    }
    return array;
}

CCArray *UnitManager::getUnitsByPlayerID(int playerID) {
    CCArray *array = CCArray::create();
    CCObject* obj = NULL;
    CCARRAY_FOREACH(_units, obj) {
        Unit *unit = dynamic_cast<Unit *>(obj);
        if (playerID == unit->getOwnerID()) {
            array->addObject(unit);
        }
    }
    return array;
}

CCArray *UnitManager::getUnits() {
    return _units;
}

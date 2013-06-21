//
//  Map.cpp
//  TactiX
//
//  Created by giginet on 2013/6/11.
//
//

#include "Map.h"

#include "Match.h"
#include "Player.h"
#include <boost/lexical_cast.hpp>

typedef enum {
    MapZOrderUnit,
    MapZOrderCursor
} MapZOrder;

using namespace boost;

Map::Map(const char *mapID) {
    _scrollView = cocos2d::extension::CCScrollView::create();
    _scrollView->retain();
    
    _units = CCArray::create();
    _units->retain();
    
    _map = CCTMXTiledMap::create("desert.tmx");
    _map->retain();
    
    _scrollView->setPosition(CCPointZero);
    _scrollView->setContentOffset(CCPointZero);
    
    CCSize size = _map->getMapSize();
    CCSize tile = _map->getTileSize();
    _scrollView->setContentSize(_map->getContentSize());
    
    _scrollView->setContainer(_map);
    _scrollView->setContentOffset(ccp(0, 0));
    _scrollView->setViewSize(CCDirector::sharedDirector()->getWinSize());
    _scrollView->setDirection(kCCScrollViewDirectionBoth);
    _scrollView->setBounceable(false);
    this->addChild(_scrollView);
    this->setTouchEnabled(true);
    
    _cursors = CCArray::create();
    _cursors->retain();
    
    _delegate = NULL;
    
    for (int i = 0; i < 2; ++i) {
        CCSprite *cursor = CCSprite::create(string("cursor" + lexical_cast<string>(i) + ".png").c_str());
        _cursors->addObject(cursor);
        _map->addChild(cursor, MapZOrderCursor);
    }
    
}

Map::~Map() {
    _map->release();
    _scrollView->release();
    _cursors->release();
    _units->release();
}

void Map::onEnter() {
    CCLayer::onEnter();
}

CCPoint Map::convertToMapSpace(const cocos2d::CCPoint &worldSpacePoint) {
    CCSize size = _map->getTileSize();
    CCSize mapSize = _map->getMapSize();
    int x = (int)(worldSpacePoint.x / size.width);
    int y = (int)(worldSpacePoint.y / size.height);
    return CCPointMake(x, mapSize.height - y - 1);
}

void Map::moveTo(const cocos2d::CCPoint &mapPoint) {
}

CCSprite *Map::getCursor(int playerID) {
    return dynamic_cast<CCSprite *>(_cursors->objectAtIndex(playerID));
}

CCSprite *Map::getTileAt(const cocos2d::CCPoint &mapPoint) {
    CCTMXLayer *mapLayer = _map->layerNamed("Map");
    return mapLayer->tileAt(mapPoint);
}

void Map::addUnit(Unit *unit, const CCPoint &mapPoint) {
    CCPoint position = this->convertToWorld(mapPoint);
    unit->setPosition(position);
    _units->addObject(unit);
    _map->addChild(unit, MapZOrderUnit);
}

void Map::moveUnit(Unit *unit, const cocos2d::CCPoint &mapPoint) {
    if (this->canMove(unit, mapPoint)) {
        unit->setPosition(this->convertToWorld(mapPoint));
    }
}

bool Map::canMove(Unit *unit, const cocos2d::CCPoint &mapPoint) {
    if (_units->containsObject(unit)) {
        CCPoint unitPoint = this->convertToMapSpace(unit->getPosition());
        return (Map::getManhattanDistance(mapPoint, unitPoint) <= unit->getMoveCapacity());
    }
    return false;
}

Unit *Map::getUnitOn(CCPoint mapPoint) {
    CCObject* obj = NULL;
    CCARRAY_FOREACH(_units, obj) {
        Unit *unit = dynamic_cast<Unit *>(obj);
        CCPoint unitMapPosition = this->convertToMapSpace(unit->getPosition());
        if (unitMapPosition.x == mapPoint.x && unitMapPosition.y == mapPoint.y) {
            return unit;
        }
    }
    return NULL;
}

CCArray *Map::getUnitsByPlayerID(int playerID) {
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

CCArray *Map::getUnits() {
    return _units;
}

CCArray *Map::tilesInRange(const cocos2d::CCPoint &from, int mapDistance) {
    /**
     本当は再帰を使った方が早いけど、
     パフォーマンス的にも問題なさそうなので
     全探索します
     */
    CCSize size = _map->getMapSize();
    CCArray *list = CCArray::create();
    for (int x = 0; x < size.width; ++ x) {
        for (int y = 0; y < size.height; ++y) {
            CCPoint p = ccp(x, y);
            if (Map::getManhattanDistance(p, from) <= mapDistance) {
                CCSprite *tile = this->getTileAt(p);
                list->addObject(tile);
            }
        }
    }
    return list;
}

#pragma private

bool Map::ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent) {
    CCPoint point = _map->convertTouchToNodeSpace(pTouch);
    CCPoint mapPoint = this->convertToMapSpace(point);
    // カーソルの処理
    Unit *unit = this->getUnitOn(mapPoint);
    if (unit != NULL) {
        CCSprite *cursor = dynamic_cast<CCSprite *>(_cursors->objectAtIndex(unit->getOwnerID()));
        cursor->setPosition(unit->getPosition());
    }
    
    // delegateの呼び出し
    if (_delegate) {
        _delegate->onTapMapPoint(this, mapPoint, unit);
    }
    return true;
}

void Map::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

CCPoint Map::convertToWorld(const CCPoint &mapPoint) {
    CCSize size = _map->getTileSize();
    CCSize mapSize = _map->getMapSize();
    float x = size.width * (mapPoint.x + 0.5);
    float y = size.height * ((mapSize.height - mapPoint.y - 1) + 0.5);
    return CCPointMake(x, y);
}

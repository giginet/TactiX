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

using namespace cocos2d;
using namespace boost;

Map::Map(const char *mapID) {
    _scrollView = cocos2d::extension::CCScrollView::create();
    _scrollView->retain();
    
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
    
    _effectLayer = CCLayer::create();
    _effectLayer->retain();
    _map->addChild(_effectLayer);
    
    _unitManager = new UnitManager();
    
    _delegate = NULL;
    
    for (int i = 0; i < 2; ++i) {
        CCSprite *cursor = CCSprite::create(string("cursor" + lexical_cast<string>(i) + ".png").c_str());
        _cursors->addObject(cursor);
        _map->addChild(cursor, MapZOrderCursor);
    }
    
}

Map::~Map() {
    _unitManager->release();
    _map->release();
    _scrollView->release();
    _cursors->release();
    _effectLayer->release();
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

cocos2d::CCSprite *Map::getCursor(int playerID) {
    return dynamic_cast<CCSprite *>(_cursors->objectAtIndex(playerID));
}

CCSprite *Map::getTileAt(const cocos2d::CCPoint &mapPoint) {
    CCTMXLayer *mapLayer = _map->layerNamed("Map");
    return mapLayer->tileAt(mapPoint);
}

CCArray *Map::tilesInRange(const cocos2d::CCPoint &from, int mapDistance) {
    return this->tilesInRange(from, 0, mapDistance);
}

CCArray *Map::tilesInRange(const cocos2d::CCPoint &from, int minDistance, int maxDistance) {
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
            int distance = Map::getManhattanDistance(p, from);
            if (minDistance <= distance && distance <= maxDistance) {
                CCSprite *tile = this->getTileAt(p);
                if (tile) {
                    list->addObject(tile);
                }
            }
        }
    }
    return list;
}

CCArray *Map::tilesInAttackRange(Unit *unit) {
    Weapon *weapon = unit->getCurrentWeapon();
    CCPoint mapPoint = this->convertToMapSpace(unit->getPosition());
    return this->tilesInAttackRange(weapon, mapPoint);
}

CCArray *Map::tilesInAttackRange(Weapon *weapon, const cocos2d::CCPoint &mapPoint) {
    CCSize size = _map->getMapSize();
    CCArray *list = CCArray::create();
    for (int x = 0; x < size.width; ++ x) {
        for (int y = 0; y < size.height; ++y) {
            CCPoint p = ccp(x, y);
            if (weapon->canAttack(ccpSub(p, mapPoint))) {
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
    Unit *unit = _unitManager->getUnitOn(mapPoint);
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

CCPoint Map::convertToWorld(const cocos2d::CCPoint &mapPoint) {
    CCSize size = _map->getTileSize();
    CCSize mapSize = _map->getMapSize();
    float x = size.width * (mapPoint.x + 0.5);
    float y = size.height * ((mapSize.height - mapPoint.y - 1) + 0.5);
    return CCPointMake(x, y);
}

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
    
    for (int i = 0; i < 2; ++i) {
        CCSprite *cursor = CCSprite::create(string("cursor" + lexical_cast<string>(i) + ".png").c_str());
        _cursors->addObject(cursor);
        _map->addChild(cursor);
    }
    
}

Map::~Map() {
    _map->release();
    _scrollView->release();
    _cursors->release();
}

void Map::onEnter() {
    CCLayer::onEnter();
    Match *match = Match::getCurrentMatch();
    for (int i = 0; i < 2; ++i) {
        Player *player = match->getPlayer(i);
        CCSprite *cursor = dynamic_cast<CCSprite *>(_cursors->objectAtIndex(i));
        Unit *unit = dynamic_cast<Unit *>(player->getUnits()->objectAtIndex(0));
        cursor->setPosition(unit->getPosition());
    }
}

CCPoint Map::convertToMapSpace(const cocos2d::CCPoint worldSpacePoint) {
    CCPoint offset = _scrollView->getContentOffset();
    CCSize size = _map->getTileSize();
    int x = (int)((worldSpacePoint.x + offset.x) / size.width);
    int y = (int)((worldSpacePoint.y + offset.y) / size.height);
    return CCPointMake(x, y);
}

void Map::moveTo(const cocos2d::CCPoint mapPoint) {
}

CCSprite *Map::getTileAt(const cocos2d::CCPoint mapPoint) {
    CCTMXLayer *mapLayer = _map->layerNamed("Map");
    return mapLayer->tileAt(mapPoint);
}

void Map::addUnit(Unit *unit, const CCPoint mapPoint) {
    CCPoint position = this->convertToWorld(mapPoint);
    unit->setPosition(position);
    _map->addChild(unit);
}

#pragma private

bool Map::ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent) {
    return true;
}

void Map::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

CCPoint Map::convertToWorld(const CCPoint mapPoint) {
    CCSize size = _map->getTileSize();
    float x = size.width * (mapPoint.x + 0.5);
    float y = size.height * (mapPoint.y + 0.5);
    return CCPointMake(x, y);
}
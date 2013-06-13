//
//  Map.cpp
//  TactiX
//
//  Created by giginet on 2013/6/11.
//
//

#include "Map.h"

Map::Map(const char *mapID) {
    _scrollView = CCScrollView::create();
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
}

Map::~Map() {
    _map->release();
    _scrollView->release();
}

CCPoint Map::convertToMapSpace(const cocos2d::CCPoint worldSpacePoint) {
    CCPoint offset = _scrollView->getContentOffset();
    CCSize size = _map->getTileSize();
    int x = (int)((worldSpacePoint.x + offset.x) / size.width);
    int y = (int)((worldSpacePoint.y + offset.y) / size.height);
    return CCPointMake(x, y);
}

CCPoint Map::convertToWorld(const CCPoint mapPoint) {
    CCSize size = _map->getTileSize();
    float x = size.width * (mapPoint.x + 0.5);
    float y = size.height * (mapPoint.y + 0.5);
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
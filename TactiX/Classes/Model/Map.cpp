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

CCPoint Map::convertToMapSpace(cocos2d::CCPoint worldSpacePoint) {
    return CCPointZero;
}

void Map::moveTo(cocos2d::CCPoint mapPoint) {
}

CCSprite *Map::getTileAt(cocos2d::CCPoint mapPoint) {
    CCTMXLayer *mapLayer = _map->layerNamed("Map");
    return mapLayer->tileAt(mapPoint);
}
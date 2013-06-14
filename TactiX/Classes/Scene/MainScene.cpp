//
//  MainScene.cpp
//  TactiX
//
//  Created by giginet on 2013/6/9.
//
//

#include "cocos-ext.h"
#include "MainScene.h"

using namespace cocos2d::extension;

MainScene::MainScene() :LuaScene("main.lua") {
    _match = Match::startMatch();
    _match->retain();
    this->addChild(_match->getMap());
    
    // テスト用にユニット追加
    Player *player0 = _match->getPlayer(0);
    Player *player1 = _match->getPlayer(1);
    Unit *unit = Unit::create("test", 0);
    player0->addUnit(unit);
    _match->getMap()->addUnit(unit, ccp(6, 6));
    
    Unit *unit2 = Unit::create("test", 1);
    player1->addUnit(unit2);
    _match->getMap()->addUnit(unit2, ccp(8, 8));
    
}

MainScene::~MainScene() {
    _match->release();
}

void MainScene::onEnter() {
    LuaScene::onEnter();
}

#pragma mark CCScrollViewDelegate

void MainScene::scrollViewDidScroll(cocos2d::extension::CCScrollView *view) {
}

void MainScene::scrollViewDidZoom(cocos2d::extension::CCScrollView *view) {
}


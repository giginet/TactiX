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
    Unit *unit = new Unit("test");
    unit->autorelease();
    player0->addUnit(unit);
    _match->getMap()->addUnit(unit, ccp(6, 6));
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


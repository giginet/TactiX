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
    
    // テスト用にユニット追加
    Player *player0 = _match->getPlayer(0);
    Player *player1 = _match->getPlayer(1);
    
    for (int i = 0; i < 5; ++i) {
        Unit *unit = Unit::create("test", 0);
        _match->getMap()->addUnit(unit, ccp(6 + i * 5, 6));
    
        Unit *unit2 = Unit::create("test", 1);
        _match->getMap()->addUnit(unit2, ccp(6 + i * 5, 15));
    }
    
    this->addChild(_match->getMap());
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


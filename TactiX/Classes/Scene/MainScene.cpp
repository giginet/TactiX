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
    for (int i = 0; i < 5; ++i) {
        Unit *unit = Unit::create("test", 0);
        _match->getMap()->addUnit(unit, ccp(6 + i * 5, 6));
    
        Unit *unit2 = Unit::create("test", 1);
        _match->getMap()->addUnit(unit2, ccp(6 + i * 5, 15));
    }
    
    this->addChild(_match->getMap());
    
    _commandMenu = new CommandMenu();
    
    _state = MainSceneStateOperation;
    
}

MainScene::~MainScene() {
    _match->release();
    _commandMenu->release();
}

void MainScene::onEnter() {
    LuaScene::onEnter();
}

void MainScene::onEnterTransitionDidFinish() {
    this->onTurnStart(1);
}

void MainScene::onTurnStart(int turn) {
    Unit *unit = _match->getCurrentUnit();
    CCSize size = unit->getContentSize();
    _commandMenu->setPosition(ccp(size.width / 2.0, size.height / 2.0f));
    unit->addChild(_commandMenu);
    CCPoint from = _match->getMap()->convertToMapSpace(unit->getPosition());
    CCArray *tiles = _match->getMap()->tilesInRange(from, 5);
    CCObject* obj = NULL;
    CCARRAY_FOREACH(tiles, obj) {
        CCSprite *tile = dynamic_cast<CCSprite *>(obj);
    }
}

void MainScene::onPhaseStart(int phase) {
}

void MainScene::onCommandInputed() {
}

#pragma mark CCScrollViewDelegate

void MainScene::scrollViewDidScroll(cocos2d::extension::CCScrollView *view) {
}

void MainScene::scrollViewDidZoom(cocos2d::extension::CCScrollView *view) {
}


//
//  MainScene.cpp
//  TactiX
//
//  Created by giginet on 2013/6/9.
//
//

#include "MainScene.h"

MainScene::MainScene() :LuaScene("main.lua") {
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
    _scrollView->setDelegate(this);
}

MainScene::~MainScene() {
    _map->release();
    _scrollView->release();
}

void MainScene::onEnter() {
    CCLayer::onEnter();
}

#pragma mark CCScrollViewDelegate

void MainScene::scrollViewDidScroll(cocos2d::extension::CCScrollView *view) {
    CCLog("exp");
}

void MainScene::scrollViewDidZoom(cocos2d::extension::CCScrollView *view) {
}


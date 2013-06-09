//
//  MainScene.cpp
//  TactiX
//
//  Created by giginet on 2013/6/9.
//
//

#include "MainScene.h"

bool MainScene::init() {
    if (LuaScene::init()) {
        return true;
    }
    return false;
}

MainScene::MainScene() :LuaScene("main.lua") {
}

void MainScene::onEnter() {
    _map = CCTMXTiledMap::create("desert.tmx");
    this->addChild(_map);
}
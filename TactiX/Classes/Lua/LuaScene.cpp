//
//  LuaScene.cpp
//  TactiX
//
//  Created by giginet on 2013/6/9.
//
//

#include "LuaScene.h"

LuaScene * LuaScene::create(const char *filename) {
    LuaScene *scene = new LuaScene(filename);
    scene->autorelease();
    return scene;
}

CCScene * LuaScene::createScene(const char *filename) {
    CCScene *scene = CCScene::create();
    LuaScene *layer = LuaScene::create(filename);
    scene->addChild(layer);
    return scene;
}

LuaScene::LuaScene(const char *filename) {
    _obj = shared_ptr<LuaObject>(new LuaObject(filename));
}

LuaScene::~LuaScene() {
}

void LuaScene::onEnter() {
    _obj->getLuaEngineWithLoad()->getLuaStack()->executeGlobalFunction("onEnter");
}

void LuaScene::onExit() {
    _obj->getLuaEngineWithLoad()->getLuaStack()->executeGlobalFunction("onExit");
}

void LuaScene::onEnterTransitionDidFinish() {
    _obj->getLuaEngineWithLoad()->getLuaStack()->executeGlobalFunction("onEnterTransitionDidFinish");
}
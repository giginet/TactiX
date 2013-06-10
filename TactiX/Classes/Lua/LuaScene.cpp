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
    _obj = boost::shared_ptr<LuaObject>(new LuaObject(filename));
    this->scheduleUpdate();
}

LuaScene::~LuaScene() {
}

bool LuaScene::init() {
    if (CCLayer::init()) {
        _obj->getLuaEngineWithLoad()->getLuaStack()->executeGlobalFunction("init");
        return true;
    }
    return false;
}

void LuaScene::onEnter() {
    CCLayer::onEnter();
    _obj->getLuaEngineWithLoad()->getLuaStack()->executeGlobalFunction("onEnter");
}

void LuaScene::onExit() {
    CCLayer::onExit();
    _obj->getLuaEngineWithLoad()->getLuaStack()->executeGlobalFunction("onExit");
}

void LuaScene::onEnterTransitionDidFinish() {
    CCLayer::onExitTransitionDidStart();
    _obj->getLuaEngineWithLoad()->getLuaStack()->executeGlobalFunction("onEnterTransitionDidFinish");
}

void LuaScene::update(float dt) {
    lua_State *L = _obj->getLuaEngineWithLoad()->getLuaStack()->getLuaState();
    lua_getglobal(L, "update");
    if (lua_isfunction(L, lua_gettop(L))) {
        lua_pushnumber(L, dt);
        if (lua_pcall(L, 1, 0, 0)) {
            CCLog("%s", lua_tostring(L, lua_gettop(L)));
        }
    }
}
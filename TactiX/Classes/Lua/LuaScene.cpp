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

LuaScene::LuaScene(const char *filename) :_className("CCLayer") {
    _obj = boost::shared_ptr<LuaObject>(new LuaObject(filename));
    this->scheduleUpdate();
}

LuaScene::~LuaScene() {
}

bool LuaScene::init() {
    if (CCLayer::init()) {
        CCLuaEngine *engine = _obj->getLuaEngineWithLoad();
        lua_State *L = engine->getLuaStack()->getLuaState();
        lua_getglobal(L, "init");
        if (lua_isfunction(L, lua_gettop(L))) {
            engine->getLuaStack()->pushCCObject(this, _className.c_str());
            if (lua_pcall(L, 1, 0, 0)) {
                CCLog("%s", lua_tostring(L, lua_gettop(L)));
            }
        }
        return true;
    }
    return false;
}

void LuaScene::onEnter() {
    CCLayer::onEnter();
    CCLuaEngine *engine = _obj->getLuaEngineWithLoad();
    lua_State *L = engine->getLuaStack()->getLuaState();
    lua_getglobal(L, "onEnter");
    if (lua_isfunction(L, lua_gettop(L))) {
        engine->getLuaStack()->pushCCObject(this, _className.c_str());
        if (lua_pcall(L, 1, 0, 0)) {
            CCLog("%s", lua_tostring(L, lua_gettop(L)));
        }
    }
}

void LuaScene::onExit() {
    CCLayer::onExit();
    CCLuaEngine *engine = _obj->getLuaEngineWithLoad();
    lua_State *L = engine->getLuaStack()->getLuaState();
    lua_getglobal(L, "onExit");
    if (lua_isfunction(L, lua_gettop(L))) {
        engine->getLuaStack()->pushCCObject(this, _className.c_str());
        if (lua_pcall(L, 1, 0, 0)) {
            CCLog("%s", lua_tostring(L, lua_gettop(L)));
        }
    }
}

void LuaScene::onEnterTransitionDidFinish() {
    CCLayer::onEnterTransitionDidFinish();
    CCLuaEngine *engine = _obj->getLuaEngineWithLoad();
    lua_State *L = engine->getLuaStack()->getLuaState();
    lua_getglobal(L, "onEnterTransitionDidFinish");
    if (lua_isfunction(L, lua_gettop(L))) {
        engine->getLuaStack()->pushCCObject(this, _className.c_str());
        if (lua_pcall(L, 1, 0, 0)) {
            CCLog("%s", lua_tostring(L, lua_gettop(L)));
        }
    }
}

void LuaScene::update(float dt) {
    CCLuaEngine *engine = _obj->getLuaEngineWithLoad();
    lua_State *L = engine->getLuaStack()->getLuaState();
    lua_getglobal(L, "onEnterTransitionDidFinish");
    if (lua_isfunction(L, lua_gettop(L))) {
        engine->getLuaStack()->pushCCObject(this, _className.c_str());
        lua_pushnumber(L, dt);
        if (lua_pcall(L, 2, 0, 0)) {
            CCLog("%s", lua_tostring(L, lua_gettop(L)));
        }
    }
}
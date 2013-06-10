//
//  LuaScene.h
//  TactiX
//
//  Created by giginet on 2013/6/9.
//
//

#ifndef __TactiX__LuaScene__
#define __TactiX__LuaScene__

#include <iostream>

#include <boost/shared_ptr.hpp>

#include "cocos2d.h"
#include "LuaObject.h"

using namespace cocos2d;
using namespace boost;

class LuaScene :public CCLayer {
private:
    boost::shared_ptr<LuaObject> _obj;
public:
    static LuaScene *create(const char *filename);
    static CCScene *createScene(const char *filename);
    LuaScene(const char *filename);
    virtual ~LuaScene();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void onEnterTransitionDidFinish();
    virtual void update(float dt);
};

#endif /* defined(__TactiX__LuaScene__) */

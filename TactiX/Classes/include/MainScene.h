//
//  MainScene.h
//  TactiX
//
//  Created by giginet on 2013/6/9.
//
//

#ifndef __TactiX__MainScene__
#define __TactiX__MainScene__

#include "LuaScene.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Match.h"
#include <iostream>

using namespace cocos2d;
using namespace cocos2d::extension;

typedef enum {
    MainSceneStateMove,
    MainSceneStateMoved,
    MainSceneStateBattle
} MainSceneState;

class MainScene :public LuaScene, public CCScrollViewDelegate {
  private:
    Match *_match;
  public:
    MainScene();
    virtual ~MainScene();
    virtual void onEnter();
    void scrollViewDidScroll(CCScrollView *view);
    void scrollViewDidZoom(CCScrollView *view);
};

#endif /* defined(__TactiX__MainScene__) */

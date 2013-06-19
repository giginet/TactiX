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
#include "CommandMenu.h"
#include <iostream>

using namespace cocos2d;
using namespace cocos2d::extension;

typedef enum {
    MainSceneStateOperation,
    MainSceneStateMoving,
    MainSceneStateMoved,
    MainSceneStateBattle
} MainSceneState;

class MainScene :public LuaScene, public CCScrollViewDelegate, CommandMenuDelegate {
  private:
    MainSceneState _state;
    Match *_match;
    CommandMenu *_commandMenu;
    void onTurnStart(int turn);
    void onPhaseStart(int phase);
    void onCommandInputed();
  public:
    MainScene();
    virtual ~MainScene();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    void scrollViewDidScroll(CCScrollView *view);
    void scrollViewDidZoom(CCScrollView *view);
};

#endif /* defined(__TactiX__MainScene__) */

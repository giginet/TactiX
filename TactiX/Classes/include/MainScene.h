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
#include <iostream>

class MainScene :public LuaScene {
  private:
    CCTMXTiledMap *_map;
    virtual bool init();
  public:
    MainScene();
    virtual void onEnter();
};

#endif /* defined(__TactiX__MainScene__) */

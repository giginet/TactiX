//
//  CommandMenu.h
//  TactiX
//
//  Created by giginet on 2013/6/18.
//
//

#ifndef __TactiX__CommandMenu__
#define __TactiX__CommandMenu__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class CommandMenuDelegate {
  public:
    void onMoveButtonPressed(CCObject *menu);
    void onAttackButtonPressed(CCObject *menu);
    void onStayButtonPressed(CCObject *menu);
};

class CommandMenu :public CCNode {
  private:
    CCMenu *_sideMenu;
    CCMenu *_topMenu;
    CommandMenuDelegate *_delegate;
    void onMoveButtonPressed(CCObject *sender);
    void onAttackButtonPressed(CCObject *sender);
    void onStayButtonPressed(CCObject *sender);
  public:
    CommandMenu();
    virtual ~CommandMenu();
    void *setDelegate(CommandMenuDelegate *delegate);
};

#endif /* defined(__TactiX__CommandMenu__) */

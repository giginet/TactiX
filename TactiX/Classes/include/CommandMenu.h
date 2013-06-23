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

typedef enum {
    CommandMenuStateTop,
    CommandMenuStateMoved,
    CommandMenuStateAttack,
    CommandMenuStateMove,
    CommandMenuStateStay
} CommandMenuState;

class CommandMenuDelegate;

class CommandMenu :public CCNode {
  private:
    CommandMenuState _state;
    CCMenu *_sideMenu;
    CCMenu *_topMenu;
    CCMenuItem *_move;
    CCMenuItem *_attack;
    CCMenuItem *_stay;
    CommandMenuDelegate *_delegate;
    void onMoveButtonPressed(CCObject *sender);
    void onAttackButtonPressed(CCObject *sender);
    void onStayButtonPressed(CCObject *sender);
  public:
    CommandMenu();
    virtual ~CommandMenu();
    void setDelegate(CommandMenuDelegate *delegate);
    CommandMenuState getState();
    void changeState(CommandMenuState state);
    
    inline CCMenuItem *getMoveItem() {
        return _move;
    }
    
    inline CCMenuItem *getAttackItem() {
        return _attack;
    }
    
    inline CCMenuItem *getStayItem() {
        return _stay;
    }
};

class CommandMenuDelegate {
  public:
    virtual void onMoveButtonPressed(CommandMenu *menu) {};
    virtual void onAttackButtonPressed(CommandMenu *menu) {};
    virtual void onStayButtonPressed(CommandMenu *menu) {};
};

#endif /* defined(__TactiX__CommandMenu__) */

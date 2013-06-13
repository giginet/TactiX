//
//  Player.h
//  TactiX
//
//  Created by giginet on 2013/6/10.
//
//

#ifndef __TactiX__Player__
#define __TactiX__Player__

#include <iostream>
#include "cocos2d.h"
#include "Unit.h"

using namespace cocos2d;

class Player :public CCObject {
  private:
    int _playerID;
    CCArray *_units;
  public:
    Player(int playerID);
    ~Player();
    int getPlayerID();
    CCArray *getUnits();
    void addUnit(Unit *unit);
};

#endif /* defined(__TactiX__Player__) */

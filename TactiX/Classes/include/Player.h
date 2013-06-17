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
    int _currentUnit;
  public:
    Player(int playerID);
    ~Player();
    int getPlayerID();
    int getCurrentUnit();
    void setCurrentUnit(int currentUnit);
};

#endif /* defined(__TactiX__Player__) */

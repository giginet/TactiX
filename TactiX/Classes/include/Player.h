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

class Player :public CCObject {
  private:
    int _playerID;
    CCArray *_units;
  public:
    Player(int playerID);
    ~Player();
    int getPlayerID();
};

#endif /* defined(__TactiX__Player__) */

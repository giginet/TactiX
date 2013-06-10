//
//  Character.h
//  TactiX
//
//  Created by giginet on 2013/6/10.
//
//

#ifndef __TactiX__Character__
#define __TactiX__Character__

#include <iostream>
#include "cocos2d.h"
#include "LuaObject.h"

using namespace std;
using namespace cocos2d;

class Character :public CCObject {
  private:
    string _name;
    CCArray *_defaultWeapons;
    LuaObject *_lua;
  public:
    Character(const char *characterID);
    ~Character();
    
    string getName();
    CCArray *getDefaultWeapons();
};

#endif /* defined(__TactiX__Character__) */

//
//  Unit.h
//  TactiX
//
//  Created by giginet on 2013/6/10.
//
//

#ifndef __TactiX__Unit__
#define __TactiX__Unit__

#include <iostream>
#include "cocos2d.h"
#include "LuaObject.h"
#include "Weapon.h"

using namespace cocos2d;

/**
 マップ上のユニットを表現するクラスです
 キャラ情報などはCharacterクラスなどに委譲させるつもり
 */
class Unit :public CCObject {
  private:
    /** 移動力 **/
    int _moveCapacity;
    /** マップ上の現在座標 **/
    CCPoint _mapPosition;
    /** 装備中の武器 **/
    CCArray *_weapons;
  public:
    Unit();
    virtual ~Unit();
    CCPoint getMapPosition();
    void setMapPosition(CCPoint position);
    
    int getMoveCapacity();
    
    CCArray *getWeapons();
    Weapon *getWeapon(int currentTurn);
    void setWeapons(CCArray *weapons);
};

#endif /* defined(__TactiX__Unit__) */

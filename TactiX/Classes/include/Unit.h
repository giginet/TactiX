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
    
    /**
     キャラクター名から新規ユニットを生成します
     */
    Unit(const char *characterName);
    
    virtual ~Unit();
    
    /**
     ユニットの現在のマップ上の位置を返します
     @return 現在のマップ上の位置
     */
    CCPoint getMapPosition();
    
    /**
     ユニットの現在のマップ上の位置を設定します
     @param mapPosition 現在のマップ上の位置
     */
    void setMapPosition(CCPoint mapPosition);
    
    /**
     このユニットの移動力を返します
     @return 移動力
     */
    int getMoveCapacity();
    
    /**
     このユニットが所持している装備の一覧を返します。
     長さは3になるはず
     @return 装備の一覧
     */
    CCArray *getWeapons();
    
    /**
     ターン数を渡した時、このターンで使用可能な武器を返します
     @param currentTurn 現在のターン数
     @return 使用可能な武器
     */
    Weapon *getWeapon(int currentTurn);
    
    /**
     ユニットに武器の一覧をセットします
     長さ3以外の武器をセットした時、例外返します
     @param 武器の一覧
     */
    void setWeapons(CCArray *weapons);
};

#endif /* defined(__TactiX__Unit__) */

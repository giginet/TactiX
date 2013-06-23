//
//  UnitManager.h
//  TactiX
//
//  Created by giginet on 2013/6/22.
//
//

#ifndef __TactiX__UnitManager__
#define __TactiX__UnitManager__

#include <iostream>
#include "cocos2d.h"
#include "Unit.h"

using namespace cocos2d;

class UnitManager :public CCObject {
  private:
    CCArray *_units;
  public:
    UnitManager();
    virtual ~UnitManager();
    
    /**
     マップ上にUnitを配置します
     @param unit 配置するUnit
     @param mapPoint マップ座標
     */
    void addUnit(Unit *unit, const CCPoint &mapPoint);
    
    /**
     マップ上のUnitを動かします
     @param unit 移動させるUnit
     @param mapPoint 移動させる座標
     */
    void moveUnit(Unit *unit, const CCPoint &mapPoint);
    
    /**
     マップ上のユニットを削除します
     @param unit 削除するUnit
     */
    void removeUnit(Unit *unit);
    
    /**
     マップ上のUnitが指定座標に動けるかを判別します
     @param unit 移動させるUnit
     @param mapPoint 移動させる座標
     @return 動けるかどうか
     */
    bool canMove(Unit *unit, const CCPoint &mapPoint);
    
    /**
     指定したマップ座標上にあるユニットを取り出します
     その座標上に何もいない時はNULLを返します
     @param mapPoint マップ座標
     @return ユニット、もしくはNULL
     */
    Unit *getUnitOn(CCPoint mapPoint);
    
    /**
     あるUnitが現在装備中の武器で攻撃できる相手を返します。
     自分は含まれません
     @param unit 攻撃するユニット
     @return ユニット一覧
     */
    CCArray *getAttackTargets(Unit *unit);
    
    /**
     指定したPlayerのユニットを取り出します
     @param playerID プレイヤーID
     @return ユニット一覧
     */
    CCArray *getUnitsByPlayerID(int playerID);
    
    /**
     全ユニットを返します
     @return 全ユニット一覧
     */
    CCArray *getUnits();
    
};

#endif /* defined(__TactiX__UnitManager__) */

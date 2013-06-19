//
//  Map.h
//  TactiX
//
//  Created by giginet on 2013/6/11.
//
//

#ifndef __TactiX__Map__
#define __TactiX__Map__

#include <iostream>
#include <cmath>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Unit.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;

/**
 マップを表すクラスです
 マップを描画したり、操作を提供します
 */
class Map :public CCLayer {
  private:
    string _mapID;
    string _name;
    string _mapFilePath;
    
    CCArray *_units;
    CCArray *_cursors;
    CCTMXTiledMap *_map;
    CCScrollView *_scrollView;
    
    CCPoint convertToWorld(const CCPoint mapPoint);
    virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    virtual void registerWithTouchDispatcher();
  public:
    Map(const char *mapID);
    ~Map();
    
    virtual void onEnter();
    
    /**
     グローバル座標からその点の示すマップ座標を返します
     @param worldSpacePoint グローバル座標
     @return マップ座標
     */
    CCPoint convertToMapSpace(const CCPoint worldSpacePoint);
    
    /**
     スクロールの中心が指定されたタイルの中心になるようにします
     @param mapPoint マップ座標
     */
    void moveTo(CCPoint mapPoint);
    
    /**
     指定座標にあるタイルを取り出します
     見つからない場合はNULLが返ります
     @param mapPoint マップ座標
     @return その座標のTileまたはNULL
     */
    CCSprite *getTileAt(const CCPoint mapPoint);
    
    /**
     マップ上にUnitを配置します
     @param unit 配置するUnit
     @param mapPoint マップ座標
     */
    void addUnit(Unit *unit, const CCPoint mapPoint);
    
    /**
     指定したマップ座標上にあるユニットを取り出します
     その座標上に何もいない時はNULLを返します
     @param mapPoint マップ座標
     @return ユニット、もしくはNULL
     */
    Unit *getUnitOn(CCPoint mapPoint);

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
    
    /**
     指定したマップ座標から指定距離にあるタイルを取り出します
     @params CCPoint& 原点
     @params int マンハッタン距離
     @return タイル一覧
     */
    CCArray *tilesInRange(CCPoint &from, int mapDistance);
    
    /**
     指定した2点間のマンハッタン距離を計算します
     @params point0 点1
     @params point1 点2
     @return マンハッタン距離
     */
    inline static int getManhattanDistance(CCPoint &point0, CCPoint &point1) {
        int x = abs(point0.x - point1.x);
        int y = abs(point0.y - point1.y);
        return (x + y);
    }

};

#endif /* defined(__TactiX__Map__) */

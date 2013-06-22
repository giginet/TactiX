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
#include "UnitManager.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;

typedef enum {
    MapZOrderUnit,
    MapZOrderCursor
} MapZOrder;

class MapDelegate;

/**
 マップを表すクラスです
 マップを描画したり、操作を提供します
 */
class Map :public CCLayer {
  private:
    string _mapID;
    string _name;
    string _mapFilePath;
    
    UnitManager *_unitManager;
    CCArray *_cursors;
    CCLayer *_effectLayer;
    CCTMXTiledMap *_map;
    CCScrollView *_scrollView;
    
    MapDelegate *_delegate;
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
    CCPoint convertToMapSpace(const CCPoint &worldSpacePoint);
    
    CCPoint convertToWorld(const CCPoint &mapPoint);
    
    /**
     スクロールの中心が指定されたタイルの中心になるようにします
     @param mapPoint マップ座標
     */
    void moveTo(const CCPoint &mapPoint);
    
    
    /**
     カーソルを取り出します
     @param playerID プレイヤー番号
     @return カーソル
     */
    CCSprite *getCursor(int playerID);
    
    /**
     指定座標にあるタイルを取り出します
     見つからない場合はNULLが返ります
     @param mapPoint マップ座標
     @return その座標のTileまたはNULL
     */
    CCSprite *getTileAt(const CCPoint &mapPoint);
    
    /**
     指定したマップ座標から指定距離にあるタイルを取り出します
     @params CCPoint& 原点
     @params int マンハッタン距離
     @return タイル一覧
     */
    CCArray *tilesInRange(const CCPoint &from, int mapDistance);
    
    /**
     指定したマップ座標から指定距離にあるタイルを取り出します
     @params CCPoint& 原点
     @params minDistance 最小マンハッタン距離
     @params maxDistance 最大マンハッタン距離
     @return タイル一覧
     */
    CCArray *tilesInRange(const CCPoint &from, int minDistance, int maxDistance);
    
    /**
     指定した2点間のマンハッタン距離を計算します
     @params point0 点1
     @params point1 点2
     @return マンハッタン距離
     */
    inline static int getManhattanDistance(const CCPoint &point0, const CCPoint &point1) {
        int x = abs(point0.x - point1.x);
        int y = abs(point0.y - point1.y);
        return (x + y);
    }
    
    /**
     delegateを取り出します
     @return delegate
     */
    inline MapDelegate *getDelegate() {
        return _delegate;
    }
    
    /**
     delegateを設定します
     @param delegate delegate
     */
    inline void setDelegate(MapDelegate *delegate) {
        _delegate = delegate;
    }
    
    /**
     エフェクトレイヤーを取り出します
     @return effectLayer
     */
    inline CCLayer *getEffectLayer() {
        return _effectLayer;
    }
    
    inline CCTMXTiledMap *getTiledMap() {
        return _map;
    }
    
    inline UnitManager *getUnitManager() {
        return _unitManager;
    }


};

class MapDelegate {
  public:
    /**
     マップ上の座標をタッチした時に呼び出されます
     @param &mapPoint タッチしたマップ座標
     */
    virtual void onTapMapPoint(Map *map, const CCPoint &mapPoint, Unit *unit) {};
};

#endif /* defined(__TactiX__Map__) */

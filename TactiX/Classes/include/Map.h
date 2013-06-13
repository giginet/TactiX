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
class Map :public CCNode {
  private:
    string _mapID;
    string _name;
    string _mapFilePath;
    CCTMXTiledMap *_map;
    CCScrollView *_scrollView;
    CCPoint convertToWorld(const CCPoint mapPoint);
  public:
    Map(const char *mapID);
    ~Map();
    
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
     @param mapLocation マップ座標
     */
    void addUnit(Unit *unit, const CCPoint mapPoint);

};

#endif /* defined(__TactiX__Map__) */
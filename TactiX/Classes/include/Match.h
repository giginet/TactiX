//
//  Match.h
//  TactiX
//
//  Created by giginet on 2013/6/10.
//
//

#ifndef __TactiX__Match__
#define __TactiX__Match__

#include <iostream>
#include "cocos2d.h"
#include "Player.h"

using namespace cocos2d;

/**
 現在のゲームを管理するクラスです
 スクリプトから利用したいためシングルトンになってます
 */
class Match :public CCObject {
  private:
    /** 現在進行中のゲーム **/
    static Match *_currentMatch;
    /** 現在のターン数 **/
    int _currentTurn;
    /** 現在のフェーズ
     フェーズとはターン中において、どちらのプレイヤーが操作中かを表す概念です。
     0ならプレイヤー1, 1ならプレイヤー2
     **/
    int _currentPhase;
    /** 現在対戦中のプレイヤー **/
    CCArray *_players;
  public:
    Match();
    ~Match();
    /**
     新しいゲームを生成して返します。
     既に進行中のゲームがある時に呼ぶと例外が返されます
     @return 新しいゲーム
     */
    static Match *startMatch();
    
    /**
     現在進行中のゲームを返します
     @return 現在進行中のゲーム
     */
    static Match *getCurrentMatch();
    
    /**
     現在進行中のゲームを削除します
     */
    static void deleteMatch();
    
    /**
     プレイヤーを返します
     @param playerID プレイヤーID(0/1)
     @return プレイヤー
     */
    Player *getPlayer(int playerID);
    
    /**
     現在のフェーズのプレイヤーを返します
     @return 現在のフェーズのプレイヤー
     */
    Player *getCurrentPlayer();
    
    /**
     現在のターン数を返します
     @return 現在のターン数
     */
    int getCurrentTurn();
    
    /**
     今のフェーズを終了して、次のフェーズに移行します
     */
    void endPhase();
};

#endif /* defined(__TactiX__Match__) */

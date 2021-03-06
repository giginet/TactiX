//
//  Match.cpp
//  TactiX
//
//  Created by giginet on 2013/6/10.
//
//

#include "Match.h"
#include "Map.h"

using namespace cocos2d;

Match *Match::_currentMatch = NULL;

Match::Match() : _currentTurn(1) ,_currentPhase(0) {
    _players = CCArray::create();
    _players->retain();
    _map = new Map("desert.tmx");
    
    // 仮にプレイヤー生成
    Player *player0 = new Player(0);
    player0->autorelease();
    Player *player1 = new Player(1);
    player1->autorelease();
    _players->addObject(player0);
    _players->addObject(player1);
    
    _currentPhase = 0;
    _currentTurn = 1;
}

Match::~Match() {
    _players->release();
    _map->release();
}

Match *Match::startMatch() {
    CCAssert(_currentMatch == NULL, "Match::startMatch must be called when currentMatch is null.");
    _currentMatch = new Match();
    _currentMatch->retain();
    return _currentMatch;
}

Match *Match::getCurrentMatch() {
    return _currentMatch;
}

void Match::deleteMatch() {
    _currentMatch->release();
    _currentMatch = NULL;
}

Player *Match::getPlayer(int playerID) {
    return dynamic_cast<Player *>(_players->objectAtIndex(playerID));
}

Player *Match::getCurrentPlayer() {
    return this->getPlayer(_currentPhase);
}

Unit *Match::getCurrentUnit() {
    return this->getCurrentUnitByPlayer(_currentPhase);
}

int Match::getCurrentTurn() {
    return _currentTurn;
}

Unit *Match::getCurrentUnitByPlayer(int playerID) {
    CCArray *units = _map->getUnitManager()->getUnitsByPlayerID(playerID);
    Player *player = this->getPlayer(playerID);
    return dynamic_cast<Unit *>(units->objectAtIndex(player->getCurrentUnitIndex()));
}

bool Match::endPhase() {
    Player *currentPlayer = this->getCurrentPlayer();
    CCArray *units = this->getMap()->getUnitManager()->getUnitsByPlayerID(currentPlayer->getPlayerID());
    currentPlayer->setCurrentUnitIndex((currentPlayer->getCurrentUnitIndex() + 1) % units->count());
    _currentPhase = (_currentPhase + 1) % 2;
    
    if (_currentPhase == 0) {
        _currentTurn += 1;
        return true;
    }
    return false;
}

Map *Match::getMap() {
    return _map;
}
//
//  Match.cpp
//  TactiX
//
//  Created by giginet on 2013/6/10.
//
//

#include "Match.h"

Match *Match::_currentMatch = NULL;

Match::Match() : _currentTurn(1) ,_currentPhase(0) {
    _players = CCArray::create();
    _players->retain();
    _map = new Map("desert.tmx");
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

int Match::getCurrentTurn() {
    return _currentTurn;
}

void Match::endPhase() {
    _currentPhase = (_currentPhase + 1) % 2;
    if (_currentPhase == 0) {
        _currentTurn += 1;
    }
}

Map *Match::getMap() {
    return _map;
}
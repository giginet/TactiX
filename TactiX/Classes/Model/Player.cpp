//
//  Player.cpp
//  TactiX
//
//  Created by giginet on 2013/6/10.
//
//

#include "Player.h"

Player::Player(int playerID) : _playerID(playerID) {
    _currentUnitIndex = 0;
}

Player::~Player() {
}

int Player::getPlayerID() {
    return _playerID;
}

int Player::getCurrentUnitIndex() {
    return _currentUnitIndex;
}

void Player::setCurrentUnitIndex(int currentUnitIndex) {
    _currentUnitIndex = currentUnitIndex;
}

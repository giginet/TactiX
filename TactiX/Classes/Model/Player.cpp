//
//  Player.cpp
//  TactiX
//
//  Created by giginet on 2013/6/10.
//
//

#include "Player.h"

Player::Player(int playerID) : _playerID(playerID) {
    _currentUnit = 0;
}

Player::~Player() {
}

int Player::getPlayerID() {
    return _playerID;
}

int Player::getCurrentUnit() {
    return _currentUnit;
}

void Player::setCurrentUnit(int currentUnit) {
    _currentUnit = currentUnit;
}
//
//  Player.cpp
//  TactiX
//
//  Created by giginet on 2013/6/10.
//
//

#include "Player.h"

Player::Player(int playerID) : _playerID(playerID) {
}

Player::~Player() {
}

int Player::getPlayerID() {
    return _playerID;
}

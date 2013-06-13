//
//  Player.cpp
//  TactiX
//
//  Created by giginet on 2013/6/10.
//
//

#include "Player.h"

Player::Player(int playerID) : _playerID(playerID) {
    _units = CCArray::create();
    _units->retain();
}

Player::~Player() {
    _units->release();
}

int Player::getPlayerID() {
    return _playerID;
}

CCArray *Player::getUnits() {
    return _units;
}

void Player::addUnit(Unit *unit) {
    unit->setOwnerID(_playerID);
    _units->addObject(unit);
}
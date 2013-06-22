//
//  Bow.cpp
//  TactiX
//
//  Created by giginet on 2013/6/10.
//
//

#include "Bow.h"

Bow::Bow() {
}

bool Bow::canAttack(cocos2d::CCPoint relPos) {
    // 自分中心のひし形に３～４マス遠方（１～２マスは攻撃不可）
    // →マンハッタン距離が3~4の時
    int manhattan = relPos.x + relPos.y;
    return (3 <= manhattan && manhattan <= 4);
}

std::string Bow::getWeaponName() {
    return "弓";
}
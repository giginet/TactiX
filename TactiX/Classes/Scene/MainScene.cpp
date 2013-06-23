//
//  MainScene.cpp
//  TactiX
//
//  Created by giginet on 2013/6/9.
//
//

#include "cocos-ext.h"
#include "MainScene.h"

using namespace cocos2d;
using namespace cocos2d::extension;

MainScene::MainScene() :LuaScene("main.lua") {
    _match = Match::startMatch();
    _match->retain();
    
    // テスト用にユニット追加
    for (int i = 0; i < 5; ++i) {
        Unit *unit = Unit::create("test", 0);
        _match->getMap()->getUnitManager()->addUnit(unit, ccp(6 + i * 5, 6));
        
        Unit *unit2 = Unit::create("test", 1);
        _match->getMap()->getUnitManager()->addUnit(unit2, ccp(6 + i * 5, 15));
    }
    
    this->addChild(_match->getMap());
    
    _commandMenu = new CommandMenu();
    _commandMenu->setDelegate(this);
    
    _state = MainSceneStateOperation;
    
    _match->getMap()->setDelegate(this);
    
}

MainScene::~MainScene() {
    _match->release();
    _commandMenu->release();
}

void MainScene::onEnter() {
    LuaScene::onEnter();
}

void MainScene::onEnterTransitionDidFinish() {
    this->onTurnStart(1);
    Unit *unit = _match->getCurrentUnit();
    this->onPhaseStart(unit);
}

void MainScene::onTurnStart(int turn) {
    
}

void MainScene::onPhaseStart(Unit *unit) {
    if (_commandMenu->getParent()) {
        _commandMenu->removeFromParent();
    }
    _match->getMap()->getEffectLayer()->removeAllChildrenWithCleanup(true);
    _commandMenu->changeState(CommandMenuStateTop);
    this->updateCursor();
    CCSize size = unit->getContentSize();
    _commandMenu->setPosition(ccp(size.width / 2.0, size.height / 2.0f));
    unit->addChild(_commandMenu);
    CCLog("%s, %s", unit->getCurrentWeapon()->getWeaponName().c_str(), unit->getCurrentWeapon()->getTypeName().c_str());
    
    CCArray *targets = _match->getMap()->getUnitManager()->getAttackTargets(_match->getCurrentUnit());
    CCLog("targets = %d", targets->count());
    _commandMenu->getAttackItem()->setEnabled(targets->count() > 0); // 攻撃対象がいるときのみ攻撃メニューを有効化
}

void MainScene::onMoved() {
    CCArray *targets = _match->getMap()->getUnitManager()->getAttackTargets(_match->getCurrentUnit());
    _commandMenu->getAttackItem()->setEnabled(targets->count() > 0); // 攻撃対象がいるときのみ攻撃メニューを有効化
    _commandMenu->changeState(CommandMenuStateMoved);
    if (targets->count() == 0) {
        this->nextPhase();
    } else {
        CCLog("can Attack");
    }
}

void MainScene::onAttacked() {
    this->nextPhase();
}

void MainScene::nextPhase() {
    Unit *currentUnit = _match->getCurrentUnit();
    currentUnit->nextWeapon(); // 武器を送る
    if (_match->endPhase()) {
        this->onTurnStart(_match->getCurrentTurn());
    }
    Unit *unit = _match->getCurrentUnit();
    this->onPhaseStart(unit);
}

void MainScene::updateCursor() {
    for (int i = 0; i < 2; ++i) {
        CCSprite *cursor = _match->getMap()->getCursor(i);
        Unit *unit = _match->getCurrentUnitByPlayer(i);
        cursor->setPosition(unit->getPosition());
    }
}

#pragma mark CCScrollViewDelegate

void MainScene::scrollViewDidScroll(cocos2d::extension::CCScrollView *view) {
}

void MainScene::scrollViewDidZoom(cocos2d::extension::CCScrollView *view) {
}

#pragma mark CommandMenuDelegate

void MainScene::onAttackButtonPressed(CommandMenu *menu) {
    if (menu->getState() == CommandMenuStateMove || menu->getState() == CommandMenuStateMoved) {
        Unit *unit = dynamic_cast<Unit *>(menu->getParent());
        CCArray *tiles = _match->getMap()->tilesInAttackRange(unit);
        CCObject* obj = NULL;
        CCARRAY_FOREACH(tiles, obj) {
            CCSprite *tile = dynamic_cast<CCSprite *>(obj);
            CCSprite *range = CCSprite::create("target.png");
            range->setAnchorPoint(tile->getAnchorPoint());
            range->setPosition(tile->getPosition());
            _match->getMap()->getEffectLayer()->addChild(range);
        }
    }
    menu->changeState(CommandMenuStateAttack);
}

void MainScene::onMoveButtonPressed(CommandMenu *menu) {
    if (menu->getState() == CommandMenuStateTop) {
        Unit *unit = dynamic_cast<Unit *>(menu->getParent());
        CCPoint from = _match->getMap()->convertToMapSpace(unit->getPosition());
        CCArray *tiles = _match->getMap()->tilesInRange(from, unit->getMoveCapacity());
        CCObject* obj = NULL;
        CCARRAY_FOREACH(tiles, obj) {
            CCSprite *tile = dynamic_cast<CCSprite *>(obj);
            CCSprite *range = CCSprite::create("range.png");
            range->setAnchorPoint(tile->getAnchorPoint());
            range->setPosition(tile->getPosition());
            _match->getMap()->getEffectLayer()->addChild(range);
        }
    }
    menu->changeState(CommandMenuStateMove);
}

void MainScene::onStayButtonPressed(CommandMenu *menu) {
    menu->changeState(CommandMenuStateStay);
    this->nextPhase();
}

#pragma mark MapDelegate

void MainScene::onTapMapPoint(Map *map, const CCPoint &mapPoint, Unit *unit) {
    if (_commandMenu->getState() == CommandMenuStateMove) { // 移動メニューの時
        Unit *currentUnit = _match->getCurrentUnit();
        if (map->getUnitManager()->canMove(currentUnit, mapPoint)) {
            map->getUnitManager()->moveUnit(currentUnit, mapPoint);
            this->onMoved();
        }
    } else if (_commandMenu->getState() == CommandMenuStateAttack) { // 攻撃メニューの時
        Unit *currentUnit = _match->getCurrentUnit();
        if (unit) {
            CCPoint relPos = ccpSub(currentUnit->getPosition(), unit->getPosition());
            currentUnit->getCurrentWeapon()->canAttack(relPos);
            bool win = currentUnit->getCurrentWeapon()->canWin(unit->getCurrentWeapon());
            bool lose = unit->getCurrentWeapon()->canWin(currentUnit->getCurrentWeapon());
            if (!win && !lose) { // 引き分けの時
                CCLog("draw");
            } else if (win) { // 攻撃側が勝つ時
                CCLog("win");
                _match->getMap()->getUnitManager()->removeUnit(unit); // 敵を殺す
            } else if (lose) { // 攻撃側が負ける時
                CCLog("lose");
                if (unit->getCurrentWeapon()->canAttack(relPos)) { // 相手の武器がこっちに当たるかどうか
                    _match->getMap()->getUnitManager()->removeUnit(currentUnit); // 自分が死ぬ
                }
            }
        }
        this->onAttacked();
    }
}


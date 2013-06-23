//
//  CommandMenu.cpp
//  TactiX
//
//  Created by giginet on 2013/6/18.
//
//

#include "CommandMenu.h"

CommandMenu::CommandMenu() {
    _move = CCMenuItemLabel::create(CCLabelTTF::create("Move", "Helvetica", 24), this, menu_selector(CommandMenu::onMoveButtonPressed));
    _attack = CCMenuItemLabel::create(CCLabelTTF::create("Attack", "Helvetica", 24), this, menu_selector(CommandMenu::onAttackButtonPressed));
    _stay = CCMenuItemLabel::create(CCLabelTTF::create("Stay", "Helvetica", 24), this, menu_selector(CommandMenu::onStayButtonPressed));
    
    _move->retain();
    _attack->retain();
    _stay->retain();
    
    _sideMenu = CCMenu::create(_attack, _stay, NULL);
    _sideMenu->retain();
    _topMenu = CCMenu::create(_move, NULL);
    _topMenu->retain();
    _delegate = NULL;
    
    _state = CommandMenuStateTop;
    
    _topMenu->setPosition(ccp(0, 80));
    _sideMenu->setPosition(ccp(0, 0));
    _sideMenu->alignItemsHorizontallyWithPadding(120);
    this->addChild(_topMenu);
    this->addChild(_sideMenu);
}

CommandMenu::~CommandMenu() {
    _move->release();
    _attack->release();
    _stay->release();
    _sideMenu->release();
    _topMenu->release();
}

void CommandMenu::onMoveButtonPressed(cocos2d::CCObject *sender) {
    if (_delegate) {
        _delegate->onMoveButtonPressed(this);
    }
}

void CommandMenu::onStayButtonPressed(cocos2d::CCObject *sender) {
    if (_delegate) {
        _delegate->onStayButtonPressed(this);
    }
}

void CommandMenu::onAttackButtonPressed(cocos2d::CCObject *sender) {
    if (_delegate) {
        _delegate->onAttackButtonPressed(this);
    }
}

void CommandMenu::setDelegate(CommandMenuDelegate *delegate) {
    _delegate = delegate;
}

CommandMenuState CommandMenu::getState() {
    return _state;
}

void CommandMenu::changeState(CommandMenuState state) {
    _state = state;
    if (state == CommandMenuStateAttack) {
        _topMenu->setVisible(false);
    } else {
        _topMenu->setVisible(true);
    }
}
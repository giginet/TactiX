//
//  CommandMenu.cpp
//  TactiX
//
//  Created by giginet on 2013/6/18.
//
//

#include "CommandMenu.h"

void CommandMenuDelegate::onMoveButtonPressed(cocos2d::CCObject *menu) {
}

void CommandMenuDelegate::onAttackButtonPressed(cocos2d::CCObject *menu) {
}

void CommandMenuDelegate::onStayButtonPressed(cocos2d::CCObject *menu) {
}

CommandMenu::CommandMenu() {
    CCMenuItemLabel *move = CCMenuItemLabel::create(CCLabelTTF::create("Move", "Helvetica", 24), this, menu_selector(CommandMenu::onMoveButtonPressed));
    CCMenuItemLabel *attack = CCMenuItemLabel::create(CCLabelTTF::create("Attack", "Helvetica", 24), this, menu_selector(CommandMenu::onAttackButtonPressed));
    CCMenuItemLabel *stay = CCMenuItemLabel::create(CCLabelTTF::create("Stay", "Helvetica", 24), this, menu_selector(CommandMenu::onStayButtonPressed));
    
    _sideMenu = CCMenu::create(attack, stay, NULL);
    _sideMenu->retain();
    _topMenu = CCMenu::create(move, NULL);
    _topMenu->retain();
    _delegate = NULL;
    
    _topMenu->setPosition(ccp(0, 80));
    _sideMenu->setPosition(ccp(0, 0));
    _sideMenu->alignItemsHorizontallyWithPadding(120);
    this->addChild(_topMenu);
    this->addChild(_sideMenu);
}

CommandMenu::~CommandMenu() {
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
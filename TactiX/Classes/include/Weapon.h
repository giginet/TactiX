//
//  Weapon.h
//  TactiX
//
//  Created by giginet on 2013/6/10.
//
//

#ifndef __TactiX__Weapon__
#define __TactiX__Weapon__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

typedef enum {
    WeaponTypeNone,
    WeaponTypeSolid,
    WeaponTypeLiquid,
    WeaponTypePlasma
} WeaponType;

typedef enum {
    WeaponKindNone,
    WeaponKindSword,
    WeaponKindSpear,
    WeaponKindBow
} WeaponKind;

/**
 武器を定義する抽象クラスです
 */
class Weapon :public CCObject {
  protected:
    Weapon();
    /** 属性 **/
    WeaponType _type;
  public:
    virtual ~Weapon();
    
    /**
     自分との相対位置を受け取って、攻撃可能かどうかを返します
     @param relPos マップ上での相対位置
     @return 攻撃可能かどうか
     */
    virtual bool canAttack(CCPoint relPos);
    
    /**
     武器装備時に加算される移動力を返します
     @return 移動力
     */
    virtual int getMoveCapacity();
    
    /**
     この武器の属性を返します
     @return 属性
     */
    WeaponType getType();
    
    /**
     この武器の属性をセットします
     @param 属性
     */
    void setType(WeaponType type);
    
    /**
     他の武器と戦闘して勝っているかどうかを返します
     @params other 対戦相手の武器
     @return 勝ってたらtrue、負けか引き分けならfalse
     */
    bool canWin(Weapon *other);

    /**
     武器の名前を取り出します
     @return 武器の名前
    */
    virtual std::string getWeaponName() {};

    /**
     武器属性名を取り出します
     @return 属性名
     */
    inline std::string getTypeName();
};

#endif /* defined(__TactiX__Weapon__) */

#pragma once

#ifndef __CARROT_H__
#define __CARROT_H__

#include "cocos2d.h"
#include"ui/CocosGUI.h"
#include<string.h>
#include"Enemy.h"
#include "cocos-ext.h"

class Carrot : public cocos2d::Sprite
{
public:
    //static cocos2d::Scene* createScene();
    int num = 0;
    Sprite* spcarrot;
    virtual bool init();
    void biteAnimation();
    bool Carrot::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void menuCloseCallback(cocos2d::Ref* pSender);

    void setHealth(int health);
    int getHealth ()const;

    void setPosition(const cocos2d::Vec2& position);

    void increaseHealth(int value);

    // 获取萝卜的动画精灵
    Sprite* getCarrotSprite() const { return spcarrot; }

    // 更新萝卜的动画
    void updateCarrotAnimation();

    CREATE_FUNC(Carrot);
private:
    int health_;  // 萝卜的生命值
    cocos2d::Vec2 customPosition;  //  用于存储位置信息
};

#endif // __CARROT_H__


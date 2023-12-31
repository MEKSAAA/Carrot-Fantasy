#pragma once
#ifndef __WIN_SCENE_H__
#define __WIN_SCENE_H__

#include "cocos2d.h"

class WinScene1 : public cocos2d::Scene {
public:
    virtual bool init();
    void onNextButtonClicked(cocos2d::Ref* sender);
    void onMainMenuButtonClicked(cocos2d::Ref* sender);
    static WinScene1* create(int carrotHealth);
    void setCarrotHealth(int health) { carrotHealth = health; }
    int getCarrotHealth() const { return carrotHealth; }

    CREATE_FUNC(WinScene1);
private:
    // 添加星星精灵
    cocos2d::Sprite* star1;
    cocos2d::Sprite* star2;
    cocos2d::Sprite* star3;

    // 星星的初始位置
    cocos2d::Vec2 starPosition;

    // 新添加的纹理变量
    cocos2d::Texture2D* starTexture1;
    cocos2d::Texture2D* starTexture2;

    // 新添加的函数
    void loadStarTextures();
    void updateStarsTexture();

    int carrotHealth;
};

#endif // __WIN_SCENE_H__

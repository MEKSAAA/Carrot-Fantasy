#pragma once
#ifndef __WIN_SCENE_H__
#define __WIN_SCENE_H__

#include "cocos2d.h"

class WinScene2 : public cocos2d::Scene {
public:
    virtual bool init();
    void onMainMenuButtonClicked(cocos2d::Ref* sender);
    static WinScene2* create(int carrotHealth);
    void setCarrotHealth(int health) { carrotHealth = health; }
    int getCarrotHealth() const { return carrotHealth; }

    CREATE_FUNC(WinScene2);
private:
    // ������Ǿ���
    cocos2d::Sprite* star1;
    cocos2d::Sprite* star2;
    cocos2d::Sprite* star3;

    // ���ǵĳ�ʼλ��
    cocos2d::Vec2 starPosition;

    // ����ӵ��������
    cocos2d::Texture2D* starTexture1;
    cocos2d::Texture2D* starTexture2;

    // ����ӵĺ���
    void loadStarTextures();
    void updateStarsTexture();

    int carrotHealth;
};

#endif // __WIN_SCENE_H__

#pragma once
#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene {
public:
    virtual bool init();
    void onRetryButtonClicked(cocos2d::Ref* sender);
    void onMainMenuButtonClicked(cocos2d::Ref* sender);

    CREATE_FUNC(GameOverScene);
private:
    // ������Ǿ���
    cocos2d::Sprite* star1;
    cocos2d::Sprite* star2;
    cocos2d::Sprite* star3;

    // ���ǵĳ�ʼλ��
    cocos2d::Vec2 starPosition;
};

#endif // __GAME_OVER_SCENE_H__

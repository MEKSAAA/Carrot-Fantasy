#pragma once
#ifndef __GAME_OVER_SCENE2_H__
#define __GAME_OVER_SCENE2_H__

#include "cocos2d.h"

class GameOverScene2 : public cocos2d::Scene {
public:
    virtual bool init();
    void onRetryButtonClicked(cocos2d::Ref* sender);
    void onMainMenuButtonClicked(cocos2d::Ref* sender);

    CREATE_FUNC(GameOverScene2);
private:
    // 添加星星精灵
    cocos2d::Sprite* star1;
    cocos2d::Sprite* star2;
    cocos2d::Sprite* star3;

    // 星星的初始位置
    cocos2d::Vec2 starPosition;
};

#endif // __GAME_OVER_SCENE2_H__

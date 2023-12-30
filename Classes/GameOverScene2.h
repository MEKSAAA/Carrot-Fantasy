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
};

#endif // __GAME_OVER_SCENE2_H__

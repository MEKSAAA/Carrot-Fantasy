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
};

#endif // __GAME_OVER_SCENE_H__

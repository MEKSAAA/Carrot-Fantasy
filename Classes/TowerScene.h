#pragma once
#ifndef __TOWER_SCENE_H__
#define __TOWER_SCENE_H__

#include "cocos2d.h"

class TowerScene : public cocos2d::Sprite
{
public:

    virtual bool init();
    int level;
    bool onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event);   //´¥Ãþ½¨Ëþ
    void loadTowrPositions();
    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(TowerScene);
};

#endif // __TOWER_SCENE_H__

#pragma once
#pragma once
#pragma once
#ifndef __Map1_Scene_H__
#define __Map1_Scene_H__

#include "cocos2d.h"
#include"ui/CocosGUI.h"
#include<string.h>

class Map1Scene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void Map1Scene::createTower(const cocos2d::Vec2& position);
    void menuCloseCallback(cocos2d::Ref* pSender);
    bool Map1Scene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

    CREATE_FUNC(Map1Scene);
};

#endif // __HELLOWORLD_SCENE_H__



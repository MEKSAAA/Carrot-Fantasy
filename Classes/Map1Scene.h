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

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Map1Scene);
};

#endif // __HELLOWORLD_SCENE_H__



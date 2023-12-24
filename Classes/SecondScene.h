#pragma once
#ifndef __Second_SCENE_H__
#define __Second_SCENE_H__

#include "cocos2d.h"
#include"ui/CocosGUI.h"
#include<string.h>

class SecondScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void Map_1(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    void Map_2(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    // implement the "static create()" method manually
    CREATE_FUNC(SecondScene);
};

#endif // __HELLOWORLD_SCENE_H__

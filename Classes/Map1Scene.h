#pragma once
#pragma once
#pragma once
#ifndef __Map1_Scene_H__
#define __Map1_Scene_H__

#include "cocos2d.h"
#include"ui/CocosGUI.h"
#include<string.h>
#include <deque>

class Map1Scene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    //void Map1Scene::createTower(const cocos2d::Vec2& position);
    void menuCloseCallback(cocos2d::Ref* pSender);
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    //Vec2 Map1Scene::tileCoordForPosition(const Vec2& position);

    CREATE_FUNC(Map1Scene);
private:
    cocos2d::TMXTiledMap* map;
    cocos2d::TMXObjectGroup* objectGroup;
    cocos2d::ValueVector objs;

    void createTowerButton(const cocos2d::Vec2& position);
    void buttonClickCallBack(cocos2d::Ref* sender, const cocos2d::Vec2 & pos);

    bool selecting = false;//当前是否正在选择状态
    cocos2d::Sprite* selection;//储存半透明矩形选中框

    cocos2d::ui::Button* towerButton1;
};

#endif // __HELLOWORLD_SCENE_H__



//#pragma once
//#pragma once
//#pragma once
#ifndef __Map1_Scene_H__
#define __Map1_Scene_H__

#include "cocos2d.h"
#include"ui/CocosGUI.h"
#include "Tower.h"
#include<string.h>
#include<vector>
#include"Carrot.h"
#include<Enemy.h>
#include"PauseLayer.h"

class Carrot;


extern class Tower;

class Map1Scene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

    CREATE_FUNC(Map1Scene);


    void spawnMonsters(float dt);    // 生成第一种敌人
    void spawnSecondTypeMonsters(float dt);  //  生成第二种敌人
    void spawnThirdTypeMonsters(float dt);  //  生成第三种敌人
    void createMonster(EnemyType type, const Vec2& position, float delay);

    Carrot* carrot;
    int carrotHealth;//  萝卜的生命值
    cocos2d::Sprite* carrotHealthBarBackground;
    cocos2d::ProgressTimer* carrotHealthBarForeground;

    // 创建萝卜
    void createCarrot();

    // 更新萝卜的生命值条
    void updateCarrotHealthBar();

    void hideCarrotHealthBar();//  用于移除萝卜的生命值条

    ~Map1Scene();

    //  处理暂停按钮点击事件
    void onPauseButtonClicked(Ref* sender);

    //  处理继续按钮点击事件
    void onResumeButtonClicked(Ref* sender);

    //  游戏失败事件处理函数
    void onGameFailed();


private:
    PauseLayer* pauseLayer;

    cocos2d::TMXTiledMap* map;
    cocos2d::TMXObjectGroup* objectGroup;
    cocos2d::ValueVector objs;//存放可以建塔的空地
    //cocos2d::ValueVector tws;//存放已经建了塔的地方
    //std::vector<Tower*> existedTW;

    void createTowerButton(const cocos2d::Vec2& position);
    void buttonClickCallBack(cocos2d::Ref* sender, const cocos2d::Vec2& pos, const int towerType);
    void buttonClickCallBack1(cocos2d::Ref* sender, const cocos2d::Vec2& pos);
    void buttonClickCallBackDLT(cocos2d::Ref* sender);

    bool selecting = false;//当前是否正在选择状态
    cocos2d::Sprite* selection;//储存半透明矩形选中框

    cocos2d::ui::Button* towerButton1;
    cocos2d::ui::Button* towerButton2;
    cocos2d::ui::Button* towerButton3;

    cocos2d::ui::Button* dltButton;
    cocos2d::ui::Button* upgButton;
};

#endif // __HELLOWORLD_SCENE_H__



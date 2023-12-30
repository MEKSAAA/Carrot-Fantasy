#pragma once
#ifndef __Map2_Scene_H__
#define __Map2_Scene_H__

#include "cocos2d.h"
#include"ui/CocosGUI.h"
#include<string.h>
#include<Enemy.h>
#include"Carrot.h"
#include"PauseLayer.h"

class Carrot;

class Map2Scene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(Map2Scene);

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

    ~Map2Scene();

    //  处理暂停按钮点击事件
    void onPauseButtonClicked(Ref* sender);

    //  处理继续按钮点击事件
    void onResumeButtonClicked(Ref* sender);

    //  游戏失败事件处理函数
    void onGameFailed();

private:
    PauseLayer* pauseLayer;
};

#endif // __HELLOWORLD_SCENE_H__



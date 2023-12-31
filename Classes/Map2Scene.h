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
    void shootFinish(Node* pNode);  //射击
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    void onEnter();
    void resetCarrot();

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

    //  处理升级萝卜点击事件
    void onAddHealthButtonClicked(cocos2d::Ref* sender);

    //  更新按钮的状态（是否可用）
    void updateAddHealthButtonState();

    //  更新按钮图片
    void updateAddHealthButtonImage();

private:
    PauseLayer* pauseLayer;
    Label* carrotHealthLabel;
    MenuItemImage* addHealthButton;
    int addHealthButtonCount;//  用于追踪升级按钮使用次数

    cocos2d::TMXTiledMap* map;
    cocos2d::TMXObjectGroup* objectGroup;
    cocos2d::ValueVector objs;//存放可以建塔的空地
    //cocos2d::ValueVector tws;//存放已经建了塔的地方
    //std::vector<Tower*> existedTW;
    //对于触摸建塔、塔的升级、删除等操作
    void createTowerButton(const cocos2d::Vec2& position);
    void buttonClickCallBack(cocos2d::Ref* sender, const cocos2d::Vec2& pos, const int towerType);
    void buttonClickCallBack1(cocos2d::Ref* sender, const cocos2d::Vec2& pos);
    void buttonClickCallBackDLT(cocos2d::Ref* sender);
    //对于触摸建塔、塔的升级、删除等操作

    bool selecting = false;//当前是否正在选择状态
    cocos2d::Sprite* selection;//储存半透明矩形选中框

    cocos2d::ui::Button* towerButton1;
    cocos2d::ui::Button* towerButton2;
    cocos2d::ui::Button* towerButton3;
    //升级和删除
    cocos2d::ui::Button* dltButton;
    cocos2d::ui::Button* upgButton;

};

#endif // __HELLOWORLD_SCENE_H__



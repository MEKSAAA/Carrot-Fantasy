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
    //void Map1Scene::update(float dt);
    virtual bool init();
    void shootBullet(std::shared_ptr<Tower> tower);
    void shootFinish(Node* pNode);  //射击
    void menuCloseCallback(cocos2d::Ref* pSender);
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onEnter();
    void resetCarrot();

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

    //  处理升级萝卜点击事件
    void onAddHealthButtonClicked(cocos2d::Ref* sender);

    //  更新按钮的状态（是否可用）
    void updateAddHealthButtonState();

    //  萝卜升级更新按钮图片
    void updateAddHealthButtonImage();


    std::vector< std::shared_ptr<Tower> > mTowerList;
    std::vector<Enemy*> mEnemyList;

private:
    PauseLayer* pauseLayer;
    Label* carrotHealthLabel;
    MenuItemImage* addHealthButton;
    int addHealthButtonCount;//  用于追踪升级按钮使用次数

    cocos2d::TMXTiledMap* map;
    cocos2d::TMXObjectGroup* objectGroup;
    cocos2d::ValueVector objs;//存放可以建塔的空地


    //对于触摸建塔、塔的升级、删除等操作

    bool selecting = false;//当前是否正在选择状态
    cocos2d::Sprite* selection;//储存半透明矩形选中框

    cocos2d::ui::Button* towerButton1;
    cocos2d::ui::Button* towerButton2;
    cocos2d::ui::Button* towerButton3;
    //升级和删除
    cocos2d::ui::Button* dltButton;
    cocos2d::ui::Button* upgButton;
    cocos2d::ui::Button* noupgButton;
};

#endif // __HELLOWORLD_SCENE_H__



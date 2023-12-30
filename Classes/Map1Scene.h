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


    void spawnMonsters(float dt);    // ���ɵ�һ�ֵ���
    void spawnSecondTypeMonsters(float dt);  //  ���ɵڶ��ֵ���
    void spawnThirdTypeMonsters(float dt);  //  ���ɵ����ֵ���
    void createMonster(EnemyType type, const Vec2& position, float delay);

    Carrot* carrot;
    int carrotHealth;//  �ܲ�������ֵ
    cocos2d::Sprite* carrotHealthBarBackground;
    cocos2d::ProgressTimer* carrotHealthBarForeground;

    // �����ܲ�
    void createCarrot();

    // �����ܲ�������ֵ��
    void updateCarrotHealthBar();

    void hideCarrotHealthBar();//  �����Ƴ��ܲ�������ֵ��

    ~Map1Scene();

    //  ������ͣ��ť����¼�
    void onPauseButtonClicked(Ref* sender);

    //  ���������ť����¼�
    void onResumeButtonClicked(Ref* sender);

    //  ��Ϸʧ���¼�������
    void onGameFailed();


private:
    PauseLayer* pauseLayer;

    cocos2d::TMXTiledMap* map;
    cocos2d::TMXObjectGroup* objectGroup;
    cocos2d::ValueVector objs;//��ſ��Խ����Ŀյ�
    //cocos2d::ValueVector tws;//����Ѿ��������ĵط�
    //std::vector<Tower*> existedTW;

    void createTowerButton(const cocos2d::Vec2& position);
    void buttonClickCallBack(cocos2d::Ref* sender, const cocos2d::Vec2& pos, const int towerType);
    void buttonClickCallBack1(cocos2d::Ref* sender, const cocos2d::Vec2& pos);
    void buttonClickCallBackDLT(cocos2d::Ref* sender);

    bool selecting = false;//��ǰ�Ƿ�����ѡ��״̬
    cocos2d::Sprite* selection;//�����͸������ѡ�п�

    cocos2d::ui::Button* towerButton1;
    cocos2d::ui::Button* towerButton2;
    cocos2d::ui::Button* towerButton3;

    cocos2d::ui::Button* dltButton;
    cocos2d::ui::Button* upgButton;
};

#endif // __HELLOWORLD_SCENE_H__



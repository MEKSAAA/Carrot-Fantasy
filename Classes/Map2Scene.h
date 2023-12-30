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

    ~Map2Scene();

    //  ������ͣ��ť����¼�
    void onPauseButtonClicked(Ref* sender);

    //  ���������ť����¼�
    void onResumeButtonClicked(Ref* sender);

    //  ��Ϸʧ���¼�������
    void onGameFailed();

private:
    PauseLayer* pauseLayer;
};

#endif // __HELLOWORLD_SCENE_H__



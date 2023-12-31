#pragma once
#ifndef __Map2_Scene_H__
#define __Map2_Scene_H__

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

class Map2Scene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    //void Map1Scene::update(float dt);
    virtual bool init();
    void shootBullet(std::shared_ptr<Tower> tower);
    void shootFinish(Node* pNode);  //���
    void menuCloseCallback(cocos2d::Ref* pSender);
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onEnter();
    void resetCarrot();

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

    std::vector< std::shared_ptr<Tower> > mTowerList;
    std::vector<Enemy*> mEnemyList;

    //  ���������ܲ�����¼�
    void onAddHealthButtonClicked(cocos2d::Ref* sender);

    //  ���°�ť��״̬���Ƿ���ã�
    void updateAddHealthButtonState();

    //  �ܲ����°�ťͼƬ
    void updateAddHealthButtonImage();

private:
    PauseLayer* pauseLayer;
    Label* carrotHealthLabel;
    MenuItemImage* addHealthButton;
    int addHealthButtonCount;//  ����׷��������ťʹ�ô���

    cocos2d::TMXTiledMap* map;
    cocos2d::TMXObjectGroup* objectGroup;
    cocos2d::ValueVector objs;//��ſ��Խ����Ŀյ�
    void createTowerButton(const cocos2d::Vec2& position);
    void buttonClickCallBack(cocos2d::Ref* sender, const cocos2d::Vec2& pos, const int towerType);
    void buttonClickCallBack1(cocos2d::Ref* sender,Vec2 pos);
    void buttonClickCallBackDLT(cocos2d::Ref* sender);
    //���ڴ�������������������ɾ���Ȳ���

    bool selecting = false;//��ǰ�Ƿ�����ѡ��״̬
    cocos2d::Sprite* selection;//�����͸������ѡ�п�

    cocos2d::ui::Button* towerButton1;
    cocos2d::ui::Button* towerButton2;
    cocos2d::ui::Button* towerButton3;
    //������ɾ��
    cocos2d::ui::Button* dltButton;
    cocos2d::ui::Button* upgButton;
    cocos2d::ui::Button* noupgButton;
};

#endif // __HELLOWORLD_SCENE_H__



//#pragma once
#ifndef __TOWER_H__
#define __TOWER_H__
#include "cocos2d.h"
#include"ui/CocosGUI.h"
#include "Map1Scene.h"
#include <cmath>
#include<vector>
#include <string.h>
#include"Bullet.h"
#include "Enemy.h"

USING_NS_CC;

enum TOWERTYPE { bottle, ice, fire };

class Tower : public cocos2d::Sprite {
protected:	
	float shootInterval;
	float damage;
	Enemy* target;
	int towerType;
	Vec2 loca;
	Sprite* oriTower;
	Sprite* atkTower;
	ui::Button* bottom;
	int atk, spd, rng, lv;
	int cost;
	std::string bulletname;

public:
	CREATE_FUNC(Tower);
	virtual bool init();
	virtual void lvUP() {};
	virtual void PlaceTower(const Vec2 & pos);
	virtual void Rotate(const Vec2 & enePos);
	//virtual void Attack(Sprite* t);
	//virtual void Shoot(Sprite* bullet);
	ui::Button* getBottom()const { return bottom; }
	Vec2 getPosition() { return loca; }
	Sprite* getOri() const { return oriTower; }
	Sprite* getAtk() const{ return atkTower; }
	Enemy* getTarget() const { return target; };
	int getTowerType() const { return towerType; }
	int getAtkV() const { return atk; }
	int getSpdV() const { return spd; }
	int getrngV() const { return rng; }
	int getLV() const { return lv; }
	int getCost() const { return cost; }
	std::string getBltName() { return bulletname; }
	Tower() {};
	Tower(Tower* t)
	{
		loca = t->getPosition();
		oriTower = t->getOri();
		atkTower = t->getAtk();
		target = t->getTarget();
		bottom = t->getBottom();
		atk = t->getAtkV();
		spd = t->getSpdV();
		rng = t->getrngV();
		lv = t->getLV();
		cost = t->getCost();
		bulletname = t->getBltName();
	}
};

class BottleTower :public Tower {
public:
	CREATE_FUNC(BottleTower);
	BottleTower() {};
	BottleTower(Tower* t)//构造函数
	{
		loca = t->getPosition();
		oriTower = t->getOri();
		atkTower = t->getAtk();
		target = t->getTarget();
		bottom = t->getBottom();
		atk = t->getAtkV();
		spd = t->getSpdV();
		rng = t->getrngV();
		lv = t->getLV();
		cost = t->getCost();
		bulletname = t->getBltName();
	}
	bool init()
	{
		if (!Tower::init())
		{
			return false;
		}
		towerType = bottle;
		bottom = ui::Button::create("Bottle_3.png");
		bottom->setZoomScale(0.0f);//禁用底座作为按钮时，点到的缩放效果
		oriTower= Sprite::create("Bottle11.png");
		atkTower = Sprite::create("Bottle12.png");
		bulletname = "PBottle11.png";
		atk = 20;
		cost = 100;
		rng = 150;
		return true;
	}
	void lvUP ()override
	{
		lv++;
		oriTower->removeFromParent();
		oriTower = Sprite::create("Bottle" + std::to_string(lv) + "1.png");
		atkTower = Sprite::create("Bottle" + std::to_string(lv) + "2.png");
		oriTower->setPosition(30, 35);
		bottom->addChild(oriTower);
	}
};

class IceTower :public Tower {
public:
	CREATE_FUNC(IceTower);
	IceTower() {};
	IceTower(Tower* t)
	{
		loca = t->getPosition();
		oriTower = t->getOri();
		atkTower = t->getAtk();
		target = t->getTarget();
		bottom = t->getBottom();
		atk = t->getAtkV();
		spd = t->getSpdV();
		rng = t->getrngV();
		lv = t->getLV();
		cost = t->getCost();
		bulletname = t->getBltName();
	}
	bool init()
	{
		if (!Tower::init())
		{
			return false;
		}
		towerType = ice;
		bottom = ui::Button::create("Ice_3.png");
		bottom->setZoomScale(0.0f);//禁用底座作为按钮时，点到的缩放效果
		oriTower = Sprite::create("Ice11.png");
		atkTower = Sprite::create("Ice12.png");
		bulletname = "Ice12.png";
		atk = 20;
		cost = 120;
		rng = 150;
		return true;
	}
	void lvUP()override
	{
		lv++;
		oriTower->removeFromParent();
		oriTower = Sprite::create("Ice" + std::to_string(lv) + "1.png");
		atkTower = Sprite::create("Ice" + std::to_string(lv) + "2.png");
		oriTower->setPosition(30, 35);
		bottom->addChild(oriTower);
	}
	void Rotate(const Vec2& enePos) override{}//星星不需要旋转，用空函数覆盖掉virtual函数
};

class FireTower :public Tower {
public:
	CREATE_FUNC(FireTower);
	FireTower() {};
	FireTower(Tower* t)
	{
		loca = t->getPosition();
		oriTower = t->getOri();
		atkTower = t->getAtk();
		target = t->getTarget();
		bottom = t->getBottom();
		atk = t->getAtkV();
		spd = t->getSpdV();
		rng = t->getrngV();
		lv = t->getLV();
		cost = t->getCost();
		bulletname = t->getBltName();
	}
	bool init()
	{
		if (!Tower::init())
		{
			return false;
		}
		towerType = bottle;
		bottom = ui::Button::create("Fire_3.png");
		bottom->setZoomScale(0.0f);//禁用底座作为按钮时，点到的缩放效果
		oriTower = Sprite::create("Fire11.png");
		atkTower = Sprite::create("Fire11.png");
		bulletname = "PBottle33.png";
		atk = 25;
		cost = 150;
		rng = 150;
		return true;
	}
	void lvUP()override
	{
		lv++;
		oriTower->removeFromParent();
		oriTower = Sprite::create("Fire" + std::to_string(lv) + "1.png");
		atkTower = Sprite::create("Fire" + std::to_string(lv) + "1.png");
		oriTower->setPosition(30, 35);
		bottom->addChild(oriTower);
	}
};
#endif
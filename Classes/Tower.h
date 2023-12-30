//#pragma once
#ifndef __TOWER_H__
#define __TOWER_H__
#include "cocos2d.h"
#include"ui/CocosGUI.h"
#include "Map1Scene.h"
#include <cmath>
#include<vector>

USING_NS_CC;

enum TOWERTYPE { bottle, ice, fire };

class Tower : public cocos2d::Sprite {
protected:	
	Vec2 loca;
	Sprite* oriTower;
	Sprite* atkTower;
	std::vector <Sprite*> bullets;
	Sprite* target;
	ui::Button* bottom;
	int atk, spd, rng, lv;
public:
	CREATE_FUNC(Tower);
	virtual bool init();
	//virtual void lvUP();
	virtual void PlaceTower(const Vec2 & pos);
	virtual void Rotate(const Vec2 & enePos);
	virtual void Attack(Sprite* t);
	virtual void Shoot(Sprite* bullet);
	ui::Button* getBottom() { return bottom; }
	Vec2 getPosition() { return loca; }
	Sprite* getOri() { return oriTower; }
	Sprite* getAtk() { return atkTower; }
	Sprite* getTarg() { return target; }
	int getAtkV() { return atk; }
	int getSpdV() { return spd; }
	int getrngV() { return rng; }
	int getLV() { return lv; }
	Tower() {};
	Tower(Tower* t)
	{
		loca = t->getPosition();
		oriTower = t->getOri();
		atkTower = t->getAtk();
		target = t->getTarg();
		bottom = t->getBottom();
		atk = t->getAtkV();
		spd = t->getSpdV();
		rng = t->getrngV();
		lv = t->getLV();
	}
};

class BottleTower :public Tower {
public:
	CREATE_FUNC(BottleTower);
	bool init()
	{
		if (!Tower::init())
		{
			return false;
		}
		bottom = ui::Button::create("Bottle_3.png");
		oriTower= Sprite::create("Bottle11.png");
		atkTower = Sprite::create("Bottle12.png");
		rng = 150;
		return true;
	}
};

class IceTower :public Tower {
public:
	CREATE_FUNC(IceTower);
	bool init()
	{
		if (!Tower::init())
		{
			return false;
		}
		bottom = ui::Button::create("Ice_3.png");
		oriTower = Sprite::create("Ice11.png");
		atkTower = Sprite::create("Ice12.png");
		rng = 150;
		return true;
	}
	void Rotate(const Vec2& enePos) override{}//星星不需要旋转，用空函数覆盖掉virtual函数
};

class FireTower :public Tower {
public:
	CREATE_FUNC(FireTower);
	bool init()
	{
		if (!Tower::init())
		{
			return false;
		}
		bottom = ui::Button::create("Fire_3.png");
		oriTower = Sprite::create("Fire11.png");
		atkTower = Sprite::create("Fire11.png");
		rng = 150;
		return true;
	}
};
#endif
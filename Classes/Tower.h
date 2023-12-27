#pragma once
#include "cocos2d.h"
#include"ui/CocosGUI.h"

USING_NS_CC;

enum TOWERTYPE { bottle, ice, fire };

class Tower : public cocos2d::Sprite {
protected:
	Sprite* bottom;
	Sprite* oriTower;
	Sprite* atkTower;
	Sprite* bullets;
	Vec2 loca;
	int atk, spd, rng, lv;
public:
	CREATE_FUNC(Tower);
	virtual bool init();
	//virtual void lvUP();
	virtual void PlaceTower(const Vec2 & pos, int type);
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
		bottom = Sprite::create("Bottle_3.png");
		oriTower= Sprite::create("Bottle11.png");
		atkTower = Sprite::create("Bottle12.png");

		return true;
	}
};
#pragma once
#ifndef __TOWER_BUTTON_H__
#define __TOWER_BUTTON_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class TowerButton :public cocos2d::Node {
public:
	CREATE_FUNC(TowerButton);
	virtual bool init();

	bool onButtonClick(Ref* sender, cocos2d::ui::Widget::TouchEventType type);//����ť����¼�
	int getButtonType() const;
private:
	int buttonType = 0;
};
#endif
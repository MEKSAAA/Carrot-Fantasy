/*#include "TowerButton.h"
USING_NS_CC;

bool TowerButton::init()
{
	if (!Node::init())
		return false;
	//���ð�ť�ص�����
	auto button = ui::Button::create("select_01.png", "select_01.png");
	button->setPosition(Vec2(420 + 35, 350 + 35));
	button->setTouchEnabled(true);
	button->addTouchEventListener(CC_CALLBACK_2(onButtonClick, this));
	addChild(button);

	return true;
}

void onButtonClick(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {

	}
}*/

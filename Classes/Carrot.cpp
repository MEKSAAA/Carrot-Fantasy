#include"Carrot.h"
#include"Enemy.h"
#include "SimpleAudioEngine.h"

using namespace std;

USING_NS_CC;

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Carrot::init()
{
	if (!Sprite::create())
	{
		return false;
	}
	//设置初始位置
	//setPosition(Vec2(820, 460));

	Vector<SpriteFrame*>allFrame;
	for (int i = 0; i < 3; i++)
	{
		string name = "hlb1_" + to_string(21 + i) + ".png";
		SpriteFrame* sf = SpriteFrame::create(name, Rect(0, 0, 200, 140));
		allFrame.pushBack(sf);
	}
	Animation* animation = Animation::createWithSpriteFrames(allFrame);
	animation->setDelayPerUnit(0.1);
	Animate* animate = Animate::create(animation);
	spcarrot = Sprite::create();
	spcarrot->runAction(RepeatForever::create(animate));
	this->addChild(spcarrot, 2);
	spcarrot->setPosition(customPosition);
	//this->schedule(schedule_selector(Map1Scene::))

	//触摸监听器，模拟被咬
	//auto Listener = cocos2d::EventListenerTouchOneByOne::create();
	//Listener->onTouchBegan = CC_CALLBACK_2(Carrot::onTouchBegan, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(Listener, this);

	return true;
}
//被咬的时候的动作
void Carrot::biteAnimation()
{
	//if(spcarrot)
	    this->removeChild(spcarrot, false);

	//string carrot = "hlb1_" + to_string(9 - num) + ".png";
	Vector<SpriteFrame*>allFrame;
	for (int i = 0; i < 2; i++)
	{
		string name = "hlb1_" + to_string(10-num-i) + ".png";
		SpriteFrame* sf = SpriteFrame::create(name, Rect(0, 0, 200, 140));
		allFrame.pushBack(sf);
	}
	Animation* animation = Animation::createWithSpriteFrames(allFrame);
	animation->setDelayPerUnit(0.1);
	Animate* animate = Animate::create(animation);
	spcarrot = Sprite::create();
	spcarrot->runAction(Repeat::create(animate,1));
	this->addChild(spcarrot, 2);
	spcarrot->setPosition(customPosition);
	num++;
	/*auto hlb = Sprite::create(carrot);
	auto scaleDown = cocos2d::ScaleTo::create(0.1f, 0.8f);
	auto scaleUp = cocos2d::ScaleTo::create(0.1f, 1.0f);
	auto sequence = cocos2d::Sequence::create(scaleDown, scaleUp, nullptr);
	runAction(sequence);
	if (hlb == nullptr)
	{
		problemLoading("carrot");
	}
	else
	{
		hlb->setPosition(Vec2(820,460));
		this->addChild(hlb, 2);
	}
	num++;*/

}

//模拟被咬
bool Carrot::onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event)
{
	biteAnimation();
	return true;
}

void Carrot::setHealth(int health)
{
	health_ = health;
}

int Carrot::getHealth()
{
	return health_;
}

void Carrot::setPosition(const cocos2d::Vec2& position)
{
	customPosition = position;

	// 更新萝卜的位置
	if (spcarrot)
	{
		spcarrot->setPosition(customPosition);
	}
}


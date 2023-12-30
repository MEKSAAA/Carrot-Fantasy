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
	//���ó�ʼλ��
	//setPosition(Vec2(820, 460));
/*-------------------------------------------------------------�ܲ���ʼ����-------------------------------------------------------------*/
	Vector<SpriteFrame*>allFrame;
	for (int i = 0; i < 3; i++)
	{
		string name = "hlb1_" + to_string(21 + i) + ".png";
		SpriteFrame* sf = SpriteFrame::create(name, Rect(0, 0, 200, 140));
		allFrame.pushBack(sf);
	}
	Animation* animation = Animation::createWithSpriteFrames(allFrame);
	animation->setDelayPerUnit(0.3);
	Animate* animate = Animate::create(animation);
	spcarrot = Sprite::create();
	spcarrot->runAction(RepeatForever::create(animate));
	this->addChild(spcarrot, 2);
	spcarrot->setPosition(customPosition);
	/*-------------------------------------------------------------�ܲ���ʼ����-------------------------------------------------------------*/

	return true;
}
//��ҧ��ʱ��Ķ���
void Carrot::biteAnimation()
{
	//if(spcarrot)
	    this->removeChild(spcarrot, false);

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
}

//ģ�ⱻҧ---------------touch_test
bool Carrot::onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event)
{
	biteAnimation();
	return true;
}
//��������ֵ
void Carrot::setHealth(int health)
{
	health_ = health;
}
//�õ�����ֵ
int Carrot::getHealth()
{
	return health_;
}
//�ܲ�λ��
void Carrot::setPosition(const cocos2d::Vec2& position)
{
	customPosition = position;

	// �����ܲ���λ��
	if (spcarrot)
	{
		spcarrot->setPosition(customPosition);
	}
}


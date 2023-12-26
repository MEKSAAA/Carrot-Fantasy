#include "CarrotFirstScene.h"
#include "SecondScene.h"
#include "Map1Scene.h"
#include "TowerScene.h"
#include "SimpleAudioEngine.h"
#include "Enemy.h"
using namespace std;

USING_NS_CC;

Scene* Map1Scene::createScene()
{
    return Map1Scene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Map1Scene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    /*-------------------------------------------------------------------------------------------------------------------------*/
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto sprite_0 = Sprite::create("BG1.png");            //��ͼ
    if (sprite_0 == nullptr)
    {
        problemLoading("'BG1.png'");
    }
    else
    {
        sprite_0->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(sprite_0, 0);
    }

    auto sprite = Sprite::create("1.png");            //��ͼ
    if (sprite == nullptr)
    {
        problemLoading("'1.png'");
    }
    else
    {
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(sprite, 1);
    }

    auto sprite_1 = Sprite::create("start01.png");
    sprite_1->setPosition(Vec2(visibleSize.width / 2 + origin.x-310, visibleSize.height / 2 + origin.y+210));
    this->addChild(sprite_1, 2);
    /*-------------------------------------------------------------------------------------------------------------------------*/

    auto map = TMXTiledMap::create("map_1.tmx");    //��ʼ����ͼ
    addChild(map);
    auto Listener = EventListenerTouchOneByOne::create();//��ʼ��������
    Listener->onTouchBegan = CC_CALLBACK_2(Map1Scene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Listener, this);


    /*-------------------------------------------------------------------------------------------------------------------------*/

// ��������
    Enemy* enemy1 = Enemy::createEnemy("F11.png");
    enemy1->setPath({ Vec2(275, 455), Vec2(275, 190), Vec2(670, 190), Vec2(670, 455), Vec2(820, 455) }); // ���õ��˵��ƶ�·��
    enemy1->setSpeed(50.0f);  //  ���õ����ٶ�
    enemy1->setStartPosition(Vec2(150, 455));  // ������ʼλ��
    addChild(enemy1, 3);
    enemy1->move(); // �������˵��ƶ�


    /*-------------------------------------------------------------------------------------------------------------------------*/


    auto closeItem = MenuItemImage::create(                 //��������޸�
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(Map1Scene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 2);
    /*-------------------------------------------------------------------------------------------------------------------------*/
        //��ͼ

    return true;
}

void Map1Scene::createTower(const Vec2& position)
{
    auto tower = TowerScene::create();
    tower->setPosition(position);

    addChild(tower,3);
}

bool Map1Scene::onTouchBegan(Touch* touch, Event* event)
{
    Vec2 touchPos = touch->getLocation();
    createTower(touchPos);
    return true;
}

void Map1Scene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
}

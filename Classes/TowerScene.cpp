#include "TowerScene.h"
#include "CarrotFirstScene.h"
#include "SecondScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

/*Scene* TowerScene::createScene()
{
    return TowerScene::create();
}*/

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool TowerScene::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

   /* auto sprite_0 = Sprite::create("BG1.png");            //µØÍ¼
    if (sprite_0 == nullptr)
    {
        problemLoading("'BG1.png'");
    }
    else
    {
        sprite_0->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(sprite_0, 0);
    }*/
    /*----------------------------------------------------------ÅÚËþ--------------------------------------------------------*/
     level = 1;
    initWithFile("select_01.png");
    auto listener = cocos2d::EventListenerTouchOneByOne::create();       //´¥ÃþÊÂ¼þ
    listener->onTouchBegan = CC_CALLBACK_2(TowerScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    /*----------------------------------------------------------ÅÚËþ--------------------------------------------------------*/

    /*auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(TowerScene::menuCloseCallback, this));

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
    this->addChild(menu, 1);*/

    return true;
}
/*----------------------------------------------------------ÅÚËþ--------------------------------------------------------*/
bool TowerScene::onTouchBegan(Touch* touch, Event* event)
{
    auto tower = TowerScene::create();
    tower->setPosition(touch->getLocation());
    getParent()->addChild(tower,3);
    return true;
}
/*----------------------------------------------------------ÅÚËþ--------------------------------------------------------*/

void TowerScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
}

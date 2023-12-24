/*2251742*/

#include "CarrotFirstScene.h"
#include "SecondScene.h"
#include "Map1Scene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* CarrotFirstScene::createScene()
{
    return CarrotFirstScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in CarrotFirstScene.cpp\n");
}

// on "init" you need to initialize your instance
bool CarrotFirstScene::init()
{
    SimpleAudioEngine::getInstance()->playBackgroundMusic("BGMusic.mp3", true);

    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("CarrotFirstScene_1.png");        //±£ÎÀÂÜ²·±³¾°Í¼
    auto sprite_1 = Sprite::create("Monster_1.png");        //±£ÎÀÂÜ²·±³¾°Í¼²¹³ä
    auto sprite_2 = Sprite::create("Monster_2.png");        //±£ÎÀÂÜ²·±³¾°Í¼²¹³ä
    auto sprite_3 = Sprite::create("Monster_3.png");        //±£ÎÀÂÜ²·±³¾°Í¼²¹³ä
    auto sprite_4 = Sprite::create("Monster_4.png");        //±£ÎÀÂÜ²·±³¾°Í¼²¹³ä
    auto sprite_5 = Sprite::create("Monster_5.png");        //±£ÎÀÂÜ²·±³¾°Í¼²¹³ä
    auto sprite_6 = Sprite::create("Monster_6.png");        //±£ÎÀÂÜ²·±³¾°Í¼²¹³ä
    auto sprite_7 = Sprite::create("Monster_7.png");        //±£ÎÀÂÜ²·±³¾°Í¼²¹³ä
    auto sprite_8 = Sprite::create("Monster_8.png");        //±£ÎÀÂÜ²·±³¾°Í¼²¹³ä
    //auto sprite_9 = Sprite::create("Monster_9.png");        //±£ÎÀÂÜ²·±³¾°Í¼²¹³ä
    sprite_1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(sprite_1, 1);
    sprite_2->setPosition(Vec2(visibleSize.width / 2 + origin.x+200, visibleSize.height / 2 + origin.y-200));    this->addChild(sprite_2, 1);
    sprite_3->setPosition(Vec2(visibleSize.width / 2 + origin.x+50, visibleSize.height / 2 + origin.y-250));    this->addChild(sprite_3, 1);
    sprite_4->setPosition(Vec2(visibleSize.width / 2 + origin.x-190, visibleSize.height / 2 + origin.y-200));    this->addChild(sprite_4, 2);
    sprite_5->setPosition(Vec2(visibleSize.width / 2 + origin.x-50, visibleSize.height / 2 + origin.y-250));    this->addChild(sprite_5, 1);
    sprite_6->setPosition(Vec2(visibleSize.width / 2 + origin.x-350, visibleSize.height / 2 + origin.y+130));    this->addChild(sprite_6, 1);
    sprite_7->setPosition(Vec2(visibleSize.width / 2 + origin.x-250, visibleSize.height / 2 + origin.y-250));    this->addChild(sprite_7, 2);
    sprite_8->setPosition(Vec2(visibleSize.width / 2 + origin.x-300, visibleSize.height / 2 + origin.y-80));    this->addChild(sprite_8, 1);
   // sprite_9->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));    this->addChild(sprite_9, 1);


    if (sprite == nullptr)
    {
        problemLoading("'CarrotFirstScene_1.png'");
    }
    else
    {
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        this->addChild(sprite, 0);
    }

    Button();

    return true;
}

void CarrotFirstScene::Button()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    MenuItemImage* startItem = MenuItemImage::create(
        "Click_1.png",
        "AfterClick_12.png",
        this,
        menu_selector(CarrotFirstScene::menuCloseCallback));            //µã»÷½øÈëÑ¡Ôñ¹Ø¿¨

    if (startItem == nullptr ||
        startItem->getContentSize().width <= 0 ||
        startItem->getContentSize().height <= 0)
    {
        problemLoading("'Click_1.png' and 'AfterClick_12.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - startItem->getContentSize().width / 2;
        float y = origin.y + startItem->getContentSize().height / 2;
        //startItem->setScale(1.0f);         //ÆÚÍû°´Å¥ÓÐ±ä´óµÄÐ§¹û
        startItem->setPosition(Vec2(x - 360, y + 260));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(startItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);



    auto close2Item = MenuItemImage::create(          //ÍË³ö±£ÎÀÂÜ²·
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(CarrotFirstScene::out, this));

    if (close2Item == nullptr ||
        close2Item->getContentSize().width <= 0 ||
        close2Item->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - close2Item->getContentSize().width / 2;
        float y = origin.y + close2Item->getContentSize().height / 2;
        close2Item->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu2 = Menu::create(close2Item, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2, 1);

}

void CarrotFirstScene::menuCloseCallback(Ref* pSender)          //ÕâÀï¸ÄÎª½øÈë¹Ø¿¨Ñ¡Ôñ½çÃæ£¿
{
    Director::getInstance()->pushScene(SecondScene::createScene());
}

void CarrotFirstScene::out(cocos2d::Ref* pSender)
{
    Director::getInstance()->popScene();
}

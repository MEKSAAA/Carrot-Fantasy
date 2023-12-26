#include "Map1Scene.h"
#include "Map2Scene.h"
#include "TowerScene.h"
#include "SecondScene.h"
#include"CarrotFirstScene.h"
#include "SimpleAudioEngine.h"
using namespace std;

USING_NS_CC;

Scene* SecondScene::createScene()
{
    return SecondScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
enum zOrderMap
{
    route = 1,
    routeButtonEffect = 5,  //按钮特效
    levelButton=10    //按钮层级
};
bool SecondScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto bbutton = ui::Button::create("point.png","point.png","");
    /*------------------------------------------------------关卡选择------------------------------------------------------*/
    //背景滚动
    auto scrollView = ui::ScrollView::create();
    scrollView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
    scrollView->setTouchEnabled(true);
    scrollView->setContentSize(Director::getInstance()->getVisibleSize());
    scrollView->setScrollBarEnabled(false);
    this->addChild(scrollView);

    Sprite* imageView = NULL;
    string filePath;
    float nextPosX = 0.f;
    for (int i = 0; i < 14; i++)
    {
        filePath = "map/stage_map_" + to_string(i) + ".png";
        imageView = Sprite::create(filePath);
        imageView->setAnchorPoint(Vec2(0, 0.5));        //更改锚点
        imageView->setPosition(nextPosX, Director::getInstance()->getVisibleSize().height/2);
        nextPosX += imageView->getContentSize().width;
        scrollView->addChild(imageView);
    }
    scrollView->setInnerContainerSize(Size(nextPosX, Director::getInstance()->getVisibleSize().height));
    //背景滚动

    TMXTiledMap* map = TMXTiledMap::create("map/Map.tmx");   //瓦片地图
    auto objectGroup = map->getObjectGroup("point");   //获取瓦片地图中的point对象层
    auto objs = objectGroup->getObjects();       //获取对象层的所有对象
    for (unsigned int i = 0; i < objs.size(); i++)    //放置按钮
    {
        auto button = ui::Button::create();
        scrollView->addChild(button, zOrderMap::levelButton, i);
        vector<ui::Button*>_routeButton;
        _routeButton.push_back(button);
        string texture = "point.png";
        auto valueMap = objs[i].asValueMap();
        if (valueMap["isBoss"].asString() == "YES")  //boss关卡
            texture = "stagepoint_gate.pong";
        if (valueMap["isTime"].asString() == "YES")  //限时关卡
            texture = "stagepoint_time.pong";
        if (valueMap["isChange"].asString() == "YES")  //随机关卡
            texture = "stagepoint_change.pong";
        button->loadTextures(texture, texture, "");
        //按钮的位置坐标
        button->setPosition(Vec2(valueMap["x"].asFloat(), valueMap["y"].asFloat()));
        if (i == 0)
        {
            button->loadTextures(texture, texture, "");
            button->setPosition(Vec2(valueMap["x"].asFloat(), valueMap["y"].asFloat()));
            button->setTouchEnabled(true);
            button->addTouchEventListener(CC_CALLBACK_2(SecondScene::Map_1, this));
        }
        if (i == 1)
        {
            button->loadTextures(texture, texture, "");
            button->setPosition(Vec2(valueMap["x"].asFloat(), valueMap["y"].asFloat()));
            button->setTouchEnabled(true);
            button->addTouchEventListener(CC_CALLBACK_2(SecondScene::Map_2, this));
        }
        //tag索引当前关卡数
        button->setTag(i);
        button->setScale(0.7);
    }

    /*-------------------------------------------------------------------------------------------------------------------------------------*/
    auto sprite_0 = Sprite::create("stagemap_toolbar_rightbg.png");            //返回首页
    if (sprite_0 == nullptr)
    {
        problemLoading("'stagemap_toolbar_rightbg.png'");
    }
    else
    {
        sprite_0->setPosition(Vec2(visibleSize.width / 2 + origin.x+350, visibleSize.height / 2 + origin.y+251));
        this->addChild(sprite_0, 1);
    }
    
    auto closeItem = MenuItemImage::create(                       //返回关卡页面
            "stagemap_toolbar_home.png",
            "stagemap_toolbar_home.png",
            CC_CALLBACK_1(SecondScene::menuCloseCallback, this));

        if (closeItem == nullptr ||
            closeItem->getContentSize().width <= 0 ||
            closeItem->getContentSize().height <= 0)
        {
            problemLoading("'stagemap_toolbar_home.png' and 'stagemap_toolbar_home.png'");
        }
        else
        {
            float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
            float y = origin.y + closeItem->getContentSize().height / 2;
            closeItem->setPosition(Vec2(x, y+548 ));
        }
        auto menu = Menu::create(closeItem, NULL);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 2);
    /*------------------------------------------------------关卡选择------------------------------------------------------*/
    return true;
}
void SecondScene::Map_1(Ref* pSender,ui::Widget::TouchEventType type)
{
    if(type==ui::Widget::TouchEventType::BEGAN)
        Director::getInstance()->pushScene(Map1Scene::createScene());
}
void SecondScene::Map_2(Ref* pSender, ui::Widget::TouchEventType type)
{
    if (type == ui::Widget::TouchEventType::BEGAN)
        Director::getInstance()->pushScene(Map2Scene::createScene());
}
void SecondScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
}
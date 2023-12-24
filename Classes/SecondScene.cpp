#include "Map1Scene.h"
#include "Map2Scene.h"
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
    routeButtonEffect = 5,  //��ť��Ч
    levelButton=10    //��ť�㼶
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
    /*------------------------------------------------------�ؿ�ѡ��------------------------------------------------------*/
    //��������
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
        imageView->setAnchorPoint(Vec2(0, 0.5));        //����ê��
        imageView->setPosition(nextPosX, Director::getInstance()->getVisibleSize().height/2);
        nextPosX += imageView->getContentSize().width;
        scrollView->addChild(imageView);
    }
    scrollView->setInnerContainerSize(Size(nextPosX, Director::getInstance()->getVisibleSize().height));
    //��������

    TMXTiledMap* map = TMXTiledMap::create("map/Map.tmx");   //��Ƭ��ͼ
    auto objectGroup = map->getObjectGroup("point");   //��ȡ��Ƭ��ͼ�е�point�����
    auto objs = objectGroup->getObjects();       //��ȡ���������ж���
    for (unsigned int i = 0; i < objs.size(); i++)    //���ð�ť
    {
        auto button = ui::Button::create();
        scrollView->addChild(button, zOrderMap::levelButton, i);
        vector<ui::Button*>_routeButton;
        _routeButton.push_back(button);
        string texture = "point.png";
        auto valueMap = objs[i].asValueMap();
        if (valueMap["isBoss"].asString() == "YES")  //boss�ؿ�
            texture = "stagepoint_gate.pong";
        if (valueMap["isTime"].asString() == "YES")  //��ʱ�ؿ�
            texture = "stagepoint_time.pong";
        if (valueMap["isChange"].asString() == "YES")  //����ؿ�
            texture = "stagepoint_change.pong";
        button->loadTextures(texture, texture, "");
        //��ť��λ������
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
        //tag������ǰ�ؿ���
        button->setTag(i);
        button->setScale(0.7);
    }

    /*-------------------------------------------------------------------------------------------------------------------------------------*/
    auto sprite_0 = Sprite::create("stagemap_toolbar_rightbg.png");            //������ҳ
    if (sprite_0 == nullptr)
    {
        problemLoading("'stagemap_toolbar_rightbg.png'");
    }
    else
    {
        sprite_0->setPosition(Vec2(visibleSize.width / 2 + origin.x+350, visibleSize.height / 2 + origin.y+251));
        this->addChild(sprite_0, 1);
    }
    
    auto closeItem = MenuItemImage::create(                       //���عؿ�ҳ��
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
    /*------------------------------------------------------�ؿ�ѡ��------------------------------------------------------*/
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
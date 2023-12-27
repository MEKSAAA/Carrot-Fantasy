#include "CarrotFirstScene.h"
#include "SecondScene.h"
#include "Map1Scene.h"
#include "Tower.h"
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

    auto sprite_0 = Sprite::create("BG1.png");            //地图
    if (sprite_0 == nullptr)
    {
        problemLoading("'BG1.png'");
    }
    else
    {
        sprite_0->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(sprite_0, 0);
    }

    auto sprite = Sprite::create("1.png");            //地图
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

    map = TMXTiledMap::create("map_1.tmx");
    addChild(map);//初始化地图
    objectGroup = map->getObjectGroup("bottle");   //获取瓦片地图中的point对象层
    objs = objectGroup->getObjects();

    /*for (const auto& obj : objs)    //放置按钮
    {
        auto valueMap = obj.asValueMap();
        auto button = ui::Button::create("select_01.png", "select_01.png");
        //按钮的位置坐标
        button->setPosition(Vec2(valueMap["x"].asFloat(), valueMap["y"].asFloat()));
        button->setVisible(false);
        button->addTouchEventListener([button](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
            if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
                button->setVisible(true);
            }
            });
        addChild(button);
    }*/
    auto Listener = cocos2d::EventListenerTouchOneByOne::create();//初始化监听器
    Listener->onTouchBegan = CC_CALLBACK_2(Map1Scene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Listener, this);

    


    /*-------------------------------------------------------------------------------------------------------------------------*/

// 创建敌人
    Enemy* enemy1 = Enemy::createEnemy("F11.png");
    enemy1->setPath({ Vec2(275, 455), Vec2(275, 190), Vec2(670, 190), Vec2(670, 455), Vec2(820, 455) }); // 设置敌人的移动路径
    enemy1->setSpeed(50.0f);  //  设置敌人速度
    enemy1->setStartPosition(Vec2(150, 455));  // 设置起始位置
    addChild(enemy1, 3);
    enemy1->move(); // 启动敌人的移动


    /*-------------------------------------------------------------------------------------------------------------------------*/


    auto closeItem = MenuItemImage::create(                 //点击，需修改
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
        //地图

    return true;
}

/*void Map1Scene::createTower(const Vec2& position)
{
    auto tower = TowerScene::create();
    tower->setPosition(position);

    addChild(tower,3);
}

Vec2 Map1Scene::tileCoordForPosition(const Vec2& position)//转换触摸位置到瓦片坐标
{
    int x = position.x / layer->getMapTileSize().width;
    int y = ((layer->getLayerSize().height * layer->getMapTileSize().height) - position.y) / layer->getMapTileSize().height;
    return Vec2(x, y);
}

bool Map1Scene::onTouchBegan(Touch* touch, Event* event)
{
    Vec2 touchPos = touch->getLocation();
    Vec2 tileCoord = tileCoordForPosition(touchPos);

    int tileGID = layer->getTileGIDAt(tileCoord);

    if (tileGID != 0) {
        selectButton->setVisible(true);
        selectButton->setPosition(tileCoord);
    }

    selectButton->setVisible(false);

    return true;
}*/
bool Map1Scene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    if (selecting = true && selection != NULL) {
        removeChild(selection, true);
        selection = NULL;
        selecting = false;
        return true;
    }
    Vec2 touchPos = touch->getLocation();
    Vec2 mapPos = this->convertToNodeSpace(touchPos);

    if (&objs != NULL) {

        for (const auto& obj : objs) {
            auto properties = obj.asValueMap();
            int x = properties["x"].asInt();
            int y = properties["y"].asInt();
            int width = properties["width"].asInt();
            int height = properties["height"].asInt();

            if (mapPos.x >= x && mapPos.x <= x + width && mapPos.y >= y && mapPos.y <= y + height) {
                selection = Sprite::create("select_01.png");
                selection->setPosition(Vec2(x, y));
                addChild(selection,3);
                selecting = true;

                towerButton1 = cocos2d::ui::Button::create("Bottle01.png");
                towerButton1->setPosition(Vec2(x, y + 20));
                selection->addChild(towerButton1);
                towerButton1->addClickEventListener([=](cocos2d::Ref* sender) {buttonClickCallBack(sender, Vec2(x, y)); });
                /*towerButton1->setTouchEnabled(true);
                towerButton1->addTouchEventListener([this,x,y](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
                    if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
                        removeChild(selection, true);
                        selection = NULL;
                        selecting = false;
                        auto bottom = Sprite::create("Bottle_3.png");
                        bottom->setPosition(Vec2(x, y));
                        addChild(bottom, 3);
                    }
                    else{
                        removeChild(selection, true);
                        selection = NULL;
                        selecting = false;
                    }
                    });*/
                //towerButton1.
            }
        }
    }
   
    return true;
}

void Map1Scene::buttonClickCallBack(cocos2d::Ref* sender, const cocos2d::Vec2& pos)
{
    auto ob = find_if(objs.begin(), objs.end(), [=](const Value& cnt) {
        auto cntVM = cnt.asValueMap();
        return pos.x ==cntVM["x"].asInt() && pos.y == cntVM["y"].asInt(); });//游标遍历，在objs中找到当前要放塔的位置
    if (ob != objs.end())
        objs.erase(ob);//从objs中删除放了塔的坐标，这样就不会再放第二次了
    removeChild(selection, true);//删掉选择方框和按钮
    selection = NULL;
    selecting = false;
    BottleTower* newTower = BottleTower::create();
    newTower->PlaceTower(pos, bottle);//放塔
}

void Map1Scene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
}

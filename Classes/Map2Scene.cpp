#include "CarrotFirstScene.h"
#include "SecondScene.h"
#include "Map2Scene.h"
#include "SimpleAudioEngine.h"
#include "Enemy.h"
#include"cocos2d.h"
#include"Carrot.h"
#include"PauseLayer.h"
#include"GameOverScene2.h"
using namespace std;

USING_NS_CC;

Scene* Map2Scene::createScene()
{
    return Map2Scene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Map2Scene::init()
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

    auto sprite = Sprite::create("2.png");            //地图
    if (sprite == nullptr)
    {
        problemLoading("'2.png'");
    }
    else
    {
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(sprite, 1);
    }

    auto sprite_1 = Sprite::create("start01.png");
    sprite_1->setPosition(Vec2(visibleSize.width / 2 + origin.x + 310, visibleSize.height / 2 + origin.y + 210));
    this->addChild(sprite_1, 2);
    /*-------------------------------------------------------------------------------------------------------------------------*/
    //...地图map_2.tmx?




    /*-------------------------------------------------------------------------------------------------------------------------*/
    
    //  初始化暂停层
    pauseLayer = nullptr;

    /*-------------------------------------------------------------------------------------------------------------------------*/
    //  初始化萝卜
    carrot = Carrot::create();
    carrot->setPosition(Vec2(530,185));
    carrotHealth = 100;
    carrot->setHealth(100);
    createCarrot();
    addChild(carrot, 3);


    /*
    // 创建单个敌人（用于调试）
    Enemy* enemy1 = Enemy::createEnemy("F11.png");
    enemy1->setPath({ Vec2(735, 190), Vec2(605, 190), Vec2(605, 320), Vec2(340, 320), Vec2(340, 390) , 
         Vec2(145, 390), Vec2(145, 190), Vec2(210, 190), Vec2(210, 125), Vec2(490, 125) }); // 设置敌人的移动路径
    enemy1->setSpeed(70.0f);  //  设置敌人速度
    enemy1->setStartPosition(Vec2(735,470));  // 设置起始位置
    enemy1->setHealthBarPosition(Vec2(50,90));  //  设置生命值条相对位置
    enemy1->setHealth(80);//用于调试生命值
    addChild(enemy1, 3);
    enemy1->move(); // 启动敌人的移动
    */

    /*-------------------------------------------------------------------------------------------------------------------------*/

    //  创建关闭按钮
    auto closeItem = MenuItemImage::create(                 //点击，需修改
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(Map2Scene::menuCloseCallback, this));

    //  创建暂停按钮
    auto pauseItem = MenuItemImage::create(
        "pause_0.png",
        "pause_0.png",
        CC_CALLBACK_1(Map2Scene::onPauseButtonClicked, this));

    // 创建继续按钮
    auto resumeItem = MenuItemImage::create(
        "pause_1.png",
        "pause_1.png",
        CC_CALLBACK_1(Map2Scene::onResumeButtonClicked, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0 ||
        pauseItem == nullptr ||
        pauseItem->getContentSize().width <= 0 ||
        pauseItem->getContentSize().height <= 0 ||
        resumeItem == nullptr ||
        resumeItem->getContentSize().width <= 0 ||
        resumeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png', 'CloseSelected.png', 'pause_0.png', and 'resume_0.png'");
    }
    else
    {
        //  设置按钮的位置
        float xClose = 930;
        float yClose = 20;
        closeItem->setPosition(Vec2(xClose, yClose));

        float xPause = 880; // 10 是按钮之间的间距
        float yPause = 15;
        pauseItem->setPosition(Vec2(xPause, yPause));

        float xResume = 830;
        float yResume = 15;
        resumeItem->setPosition(Vec2(xResume, yResume));
    }

    // 添加按钮到菜单
    auto menu = Menu::create(closeItem, pauseItem, resumeItem, nullptr);
    menu->setPosition(Vec2(0, 0));
    this->addChild(menu, 9);

    /*-------------------------------------------------------------------------------------------------------------------------*/

     // 使用定时器创建第一个怪物
    scheduleOnce(CC_SCHEDULE_SELECTOR(Map2Scene::spawnMonsters), 1.0f);

    /*-------------------------------------------------------------------------------------------------------------------------*/



    return true;
}

void Map2Scene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
}

void Map2Scene::spawnMonsters(float dt)
{
    // 逐个创建怪物，并添加到场景中
    createMonster(EnemyType::Type1, Vec2(740, 470), 1.0f);
    createMonster(EnemyType::Type1, Vec2(740, 470), 2.0f);
    createMonster(EnemyType::Type1, Vec2(740, 470), 3.0f);
    createMonster(EnemyType::Type1, Vec2(740, 470), 4.0f);
    createMonster(EnemyType::Type1, Vec2(740, 470), 5.0f);

    // 过一段时间，逐个创建第二种怪物
    scheduleOnce(CC_SCHEDULE_SELECTOR(Map2Scene::spawnSecondTypeMonsters), 7.0f);

}

void Map2Scene::spawnSecondTypeMonsters(float dt)
{
    // 逐个创建第二种怪物，并添加到场景中
    createMonster(EnemyType::Type2, Vec2(740, 470), 2.0f);
    createMonster(EnemyType::Type2, Vec2(740, 470), 4.0f);
    createMonster(EnemyType::Type2, Vec2(740, 470), 6.0f);
    createMonster(EnemyType::Type2, Vec2(740, 470), 8.0f);
    createMonster(EnemyType::Type2, Vec2(740, 470), 10.0f);


    // 过一段时间，逐个创建第三种怪物
    scheduleOnce(CC_SCHEDULE_SELECTOR(Map2Scene::spawnThirdTypeMonsters), 12.0f);
}

void Map2Scene::spawnThirdTypeMonsters(float dt)
{
    // 逐个创建第三种怪物，并添加到场景中
    createMonster(EnemyType::Type3, Vec2(740, 470), 2.0f);
    createMonster(EnemyType::Type3, Vec2(740, 470), 4.0f);
    createMonster(EnemyType::Type3, Vec2(740, 470), 6.0f);
    createMonster(EnemyType::Type3, Vec2(740, 470), 8.0f);
    createMonster(EnemyType::Type3, Vec2(740, 470), 10.0f);
}

void Map2Scene::createMonster(EnemyType type, const Vec2& position, float delay)
{
    // 使用延迟创建怪物的动作
    auto delayAction = DelayTime::create(delay);
    auto createMonsterAction = CallFunc::create([this, type, position]() {
        std::string monsterImage;
        switch (type)
        {
            case EnemyType::Type1:
                monsterImage = "F11.png";
                break;
            case EnemyType::Type2:
                monsterImage = "F21.png";
                break;
            case EnemyType::Type3:
                monsterImage = "L11.png";
                break;
            default:
                break;
        }

        auto monster = Enemy::createEnemy(monsterImage, type);

        //  不同种类的怪物起始位置相同
        monster->setStartPosition(position);
        //  不同种类的怪物路径相同
        monster->setPath({ Vec2(740, 190), Vec2(605, 190), Vec2(605, 330), Vec2(340, 330), Vec2(340, 390) ,
         Vec2(145, 390), Vec2(145, 200), Vec2(210, 200), Vec2(210, 125), Vec2(490, 125) }); // 设置怪物的移动路径
        monster->setHealth(100);
        monster->setType(type);
        switch (type)
        {
            case EnemyType::Type1:
                monster->setSpeed(75.0f);// 设置怪物速度
                monster->setHealthBarPosition(Vec2(50, 90));  //  设置生命值条相对于怪物的位置
                break;
            case EnemyType::Type2:
                monster->setSpeed(75.0f);// 设置怪物速度
                monster->setHealthBarPosition(Vec2(40, 95));  //  设置生命值条相对于怪物的位置
                break;
            case EnemyType::Type3:
                monster->setSpeed(75.0f);// 设置怪物速度
                monster->setHealthBarPosition(Vec2(45, 80));  //  设置生命值条相对于怪物的位置
                break;
            default:
                break;
        }

        // 设置其他怪物属性...
        addChild(monster, 3);
        monster->move(); // 启动怪物的移动
        CCLOG("Monster created successfully!");  // 添加日志
        });

    // 创建一个序列动作，包含延迟和创建怪物的动作
    auto sequenceAction = Sequence::create(delayAction, createMonsterAction, nullptr);

    // 执行序列动作
    runAction(sequenceAction);

}

void Map2Scene::createCarrot()
{
    // 创建和初始化生命值条
    carrotHealthBarBackground = Sprite::create("hlb_hb_bg.png");
    carrotHealthBarBackground->setPosition(Vec2(500,215));  // 设置相对位置的坐标
    carrot->addChild(carrotHealthBarBackground, 4);

    carrotHealthBarForeground = ProgressTimer::create(Sprite::create("hlb_hb_fg.png"));
    carrotHealthBarForeground->setType(ProgressTimer::Type::BAR);
    carrotHealthBarForeground->setMidpoint(Vec2(0, 0.5));
    carrotHealthBarForeground->setBarChangeRate(Vec2(1, 0));
    carrotHealthBarForeground->setPercentage(carrotHealth);
    carrotHealthBarForeground->setPosition(Vec2(500, 215));  // 设置相对位置的坐标
    carrot->addChild(carrotHealthBarForeground, 5);
}

void Map2Scene::updateCarrotHealthBar()
{
    // 更新生命值条的百分比
    float percentage = static_cast<float>(carrotHealth) / 100.0f * 100.0f;
    carrotHealthBarForeground->setPercentage(percentage);

    //检查萝卜是否死亡
    if (carrotHealth <= 0) {
        // 移除生命值条元素
        hideCarrotHealthBar();
        //  触发游戏失败事件
        onGameFailed();
    }
}

void Map2Scene::hideCarrotHealthBar()
{
    if (carrotHealthBarBackground) {
        carrotHealthBarBackground->removeFromParent();
        carrotHealthBarBackground = nullptr;
    }

    if (carrotHealthBarForeground) {
        carrotHealthBarForeground->removeFromParent();
        carrotHealthBarForeground = nullptr;
    }
}

Map2Scene::~Map2Scene()
{
    if (carrot) {
        carrot->release();
    }
}

void Map2Scene::onPauseButtonClicked(Ref* sender)
{
    if (!pauseLayer)
    {
        pauseLayer = PauseLayer::create();
        addChild(pauseLayer, 999); // 使用较高的 Z 顺序确保在最上层
        pauseLayer->showPauseMenu();
    }
}

void Map2Scene::onResumeButtonClicked(Ref* sender)
{
    if (pauseLayer)
    {
        pauseLayer->hidePauseMenu();
        pauseLayer = nullptr; // 释放 PauseLayer 对象
    }
}

void Map2Scene::onGameFailed()
{
    // 暂停游戏
    Director::getInstance()->pause();

    // 切换到游戏失败场景
    auto gameOverScene = GameOverScene2::create();
    Director::getInstance()->replaceScene(gameOverScene);
}



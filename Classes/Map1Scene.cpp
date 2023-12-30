//Map1Scene.cpp

#include "CarrotFirstScene.h"
#include "SecondScene.h"
#include "Map1Scene.h"
#include "TowerScene.h"
#include "SimpleAudioEngine.h"
#include "Enemy.h"
#include"cocos2d.h"
#include"Carrot.h"
#include"PauseLayer.h"
#include"GameOverScene.h"
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
    
    //  ��ʼ����ͣ��
    pauseLayer = nullptr;

    /*-------------------------------------------------------------------------------------------------------------------------*/
    //  ��ʼ���ܲ�
    carrot = Carrot::create();
    carrot->setPosition(Vec2(860,520));
    carrotHealth = 100;
    carrot->setHealth(100);
    createCarrot();
    addChild(carrot, 3);


    /*
    // �����������ˣ����ڵ��ԣ�
    Enemy* enemy1 = Enemy::createEnemy("F21.png");
    enemy1->setPath({ Vec2(280, 455), Vec2(280, 195), Vec2(675, 195), Vec2(675, 460), Vec2(820, 460) }); // ���õ��˵��ƶ�·��
    enemy1->setSpeed(70.0f);  //  ���õ����ٶ�
    enemy1->setStartPosition(Vec2(150, 455));  // ������ʼλ��
    enemy1->setHealthBarPosition(Vec2(40, 95));  //  ��������ֵ�����λ��
    enemy1->setHealth(50);//���ڵ�������ֵ
    addChild(enemy1, 3);
    enemy1->move(); // �������˵��ƶ�
    */

    /*-------------------------------------------------------------------------------------------------------------------------*/
    //  �����رհ�ť
    auto closeItem = MenuItemImage::create(                 //��������޸�
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(Map1Scene::menuCloseCallback, this));

    //  ������ͣ��ť
    auto pauseItem = MenuItemImage::create(
        "pause_0.png",
        "pause_0.png",
        CC_CALLBACK_1(Map1Scene::onPauseButtonClicked, this));

    // ����������ť
    auto resumeItem = MenuItemImage::create(
        "pause_1.png",
        "pause_1.png",
        CC_CALLBACK_1(Map1Scene::onResumeButtonClicked, this));

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
        //  ���ð�ť��λ��
        float xClose = 930;
        float yClose = 20;
        closeItem->setPosition(Vec2(xClose, yClose));

        float xPause = 880; // 10 �ǰ�ť֮��ļ��
        float yPause = 15;
        pauseItem->setPosition(Vec2(xPause, yPause));

        float xResume = 830;
        float yResume = 15;
        resumeItem->setPosition(Vec2(xResume, yResume));
    }

    // ��Ӱ�ť���˵�
    auto menu = Menu::create(closeItem, pauseItem, resumeItem, nullptr);
    menu->setPosition(Vec2(0, 0));
    this->addChild(menu, 9);
    /*-------------------------------------------------------------------------------------------------------------------------*/

     // ʹ�ö�ʱ��������һ������
    scheduleOnce(CC_SCHEDULE_SELECTOR(Map1Scene::spawnMonsters), 1.0f);

    /*-------------------------------------------------------------------------------------------------------------------------*/
    


    // ע����ﵽ���յ�ļ�����
    auto eventListener = EventListenerCustom::create("enemy_reached_destination", [&](EventCustom* event) {
        // ������ﵽ���յ���߼�
        Enemy* enemy = static_cast<Enemy*>(event->getUserData());
        // ������ʵ���ܲ���ҧ���߼�
        carrot->biteAnimation();
        int currentHealth = carrot->getHealth();
        currentHealth -= 10;
        carrot->setHealth(currentHealth);
        carrotHealth -= 10;
        updateCarrotHealthBar();
    });

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);

    
    
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

void Map1Scene::spawnMonsters(float dt)
{
    // ��������������ӵ�������
    createMonster(EnemyType::Type1, Vec2(150, 455), 1.0f);
    createMonster(EnemyType::Type1, Vec2(150, 455), 2.0f);
    createMonster(EnemyType::Type1, Vec2(150, 455), 3.0f);
    createMonster(EnemyType::Type1, Vec2(150, 455), 4.0f);
    createMonster(EnemyType::Type1, Vec2(150, 455), 5.0f);

    // ��һ��ʱ�䣬��������ڶ��ֹ���
    scheduleOnce(CC_SCHEDULE_SELECTOR(Map1Scene::spawnSecondTypeMonsters), 7.0f);
}

void Map1Scene::spawnSecondTypeMonsters(float dt)
{
    // ��������ڶ��ֹ������ӵ�������
    createMonster(EnemyType::Type2, Vec2(150, 455), 2.0f);
    createMonster(EnemyType::Type2, Vec2(150, 455), 4.0f);
    createMonster(EnemyType::Type2, Vec2(150, 455), 6.0f);
    createMonster(EnemyType::Type2, Vec2(150, 455), 8.0f);
    createMonster(EnemyType::Type2, Vec2(150, 455), 10.0f);


    // ��һ��ʱ�䣬������������ֹ���
    scheduleOnce(CC_SCHEDULE_SELECTOR(Map1Scene::spawnThirdTypeMonsters), 12.0f);
}

void Map1Scene::spawnThirdTypeMonsters(float dt)
{
    // ������������ֹ������ӵ�������
    createMonster(EnemyType::Type3, Vec2(150, 455), 2.0f);
    createMonster(EnemyType::Type3, Vec2(150, 455), 4.0f);
    createMonster(EnemyType::Type3, Vec2(150, 455), 6.0f);
    createMonster(EnemyType::Type3, Vec2(150, 455), 8.0f);
    createMonster(EnemyType::Type3, Vec2(150, 455), 10.0f);
}

void Map1Scene::createMonster(EnemyType type, const Vec2& position, float delay)
{
    // ʹ���ӳٴ�������Ķ���
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

        //  ��ͬ����Ĺ�����ʼλ����ͬ
        monster->setStartPosition(position);
        //  ��ͬ����Ĺ���·����ͬ
        monster->setPath({ Vec2(280, 455), Vec2(280, 195), Vec2(675, 195), Vec2(675, 460), Vec2(820, 460) }); // ���ù�����ƶ�·��
        monster->setHealth(100);
        monster->setType(type);
        switch (type)
        {
            case EnemyType::Type1:
                monster->setSpeed(75.0f);// ���ù����ٶ�
                monster->setHealthBarPosition(Vec2(50, 90));  //  ��������ֵ������ڹ����λ��
                break;
            case EnemyType::Type2:
                monster->setSpeed(75.0f);// ���ù����ٶ�
                monster->setHealthBarPosition(Vec2(40, 95));  //  ��������ֵ������ڹ����λ��
                break;
            case EnemyType::Type3:
                monster->setSpeed(75.0f);// ���ù����ٶ�
                monster->setHealthBarPosition(Vec2(45, 80));  //  ��������ֵ������ڹ����λ��
                break;
            default:
                break;
        }

        // ����������������...
        addChild(monster,3);  

        monster->move(); // ����������ƶ�
        CCLOG("Monster created successfully!");  // �����һ����־

    });

    // ����һ�����ж����������ӳ٣���������
    auto sequenceAction = Sequence::create(delayAction, createMonsterAction, nullptr);

    // ִ�����ж���
    runAction(sequenceAction);
}

void Map1Scene::createCarrot()
{
    // �����ͳ�ʼ������ֵ��
    carrotHealthBarBackground = Sprite::create("hlb_hb_bg.png");
    carrotHealthBarBackground->setPosition(Vec2(830, 550));  // �������λ�õ�����
    carrot->addChild(carrotHealthBarBackground, 4);

    carrotHealthBarForeground = ProgressTimer::create(Sprite::create("hlb_hb_fg.png"));
    carrotHealthBarForeground->setType(ProgressTimer::Type::BAR);
    carrotHealthBarForeground->setMidpoint(Vec2(0, 0.5));
    carrotHealthBarForeground->setBarChangeRate(Vec2(1, 0));
    carrotHealthBarForeground->setPercentage(carrotHealth);
    carrotHealthBarForeground->setPosition(Vec2(830, 550));  // �������λ�õ�����
    carrot->addChild(carrotHealthBarForeground, 5);
}

void Map1Scene::updateCarrotHealthBar()
{
    // ��������ֵ���İٷֱ�
    float percentage = static_cast<float>(carrotHealth) / 100.0f * 100.0f;
    carrotHealthBarForeground->setPercentage(percentage);

    //����ܲ��Ƿ�����
    if (carrotHealth <= 0) {
        // �Ƴ�����ֵ��Ԫ��
        hideCarrotHealthBar();
        //  ������Ϸʧ���¼�
        onGameFailed();
    }
}

void Map1Scene::hideCarrotHealthBar()
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

Map1Scene::~Map1Scene()
{
    if (carrot) {
        carrot->release();
    }
}

void Map1Scene::onPauseButtonClicked(Ref* sender)
{
    if (!pauseLayer)
    {
        pauseLayer = PauseLayer::create();
        addChild(pauseLayer, 999); // ʹ�ýϸߵ� Z ˳��ȷ�������ϲ�
        pauseLayer->showPauseMenu();
    }
}

void Map1Scene::onResumeButtonClicked(Ref* sender)
{
    if (pauseLayer)
    {
        pauseLayer->hidePauseMenu();
        pauseLayer = nullptr; // �ͷ� PauseLayer ����
    }
}

void Map1Scene::onGameFailed()
{
    // ��ͣ��Ϸ
    Director::getInstance()->pause();

    // �л�����Ϸʧ�ܳ���
    auto gameOverScene = GameOverScene::create();
    Director::getInstance()->replaceScene(gameOverScene);
}

void Map1Scene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
}


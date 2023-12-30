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

    auto sprite = Sprite::create("2.png");            //��ͼ
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
    //...��ͼmap_2.tmx?




    /*-------------------------------------------------------------------------------------------------------------------------*/
    
    //  ��ʼ����ͣ��
    pauseLayer = nullptr;

    /*-------------------------------------------------------------------------------------------------------------------------*/
    //  ��ʼ���ܲ�
    carrot = Carrot::create();
    carrot->setPosition(Vec2(530,185));
    carrotHealth = 100;
    carrot->setHealth(100);
    createCarrot();
    addChild(carrot, 3);


    /*
    // �����������ˣ����ڵ��ԣ�
    Enemy* enemy1 = Enemy::createEnemy("F11.png");
    enemy1->setPath({ Vec2(735, 190), Vec2(605, 190), Vec2(605, 320), Vec2(340, 320), Vec2(340, 390) , 
         Vec2(145, 390), Vec2(145, 190), Vec2(210, 190), Vec2(210, 125), Vec2(490, 125) }); // ���õ��˵��ƶ�·��
    enemy1->setSpeed(70.0f);  //  ���õ����ٶ�
    enemy1->setStartPosition(Vec2(735,470));  // ������ʼλ��
    enemy1->setHealthBarPosition(Vec2(50,90));  //  ��������ֵ�����λ��
    enemy1->setHealth(80);//���ڵ�������ֵ
    addChild(enemy1, 3);
    enemy1->move(); // �������˵��ƶ�
    */

    /*-------------------------------------------------------------------------------------------------------------------------*/

    //  �����رհ�ť
    auto closeItem = MenuItemImage::create(                 //��������޸�
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(Map2Scene::menuCloseCallback, this));

    //  ������ͣ��ť
    auto pauseItem = MenuItemImage::create(
        "pause_0.png",
        "pause_0.png",
        CC_CALLBACK_1(Map2Scene::onPauseButtonClicked, this));

    // ����������ť
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
    // ��������������ӵ�������
    createMonster(EnemyType::Type1, Vec2(740, 470), 1.0f);
    createMonster(EnemyType::Type1, Vec2(740, 470), 2.0f);
    createMonster(EnemyType::Type1, Vec2(740, 470), 3.0f);
    createMonster(EnemyType::Type1, Vec2(740, 470), 4.0f);
    createMonster(EnemyType::Type1, Vec2(740, 470), 5.0f);

    // ��һ��ʱ�䣬��������ڶ��ֹ���
    scheduleOnce(CC_SCHEDULE_SELECTOR(Map2Scene::spawnSecondTypeMonsters), 7.0f);

}

void Map2Scene::spawnSecondTypeMonsters(float dt)
{
    // ��������ڶ��ֹ������ӵ�������
    createMonster(EnemyType::Type2, Vec2(740, 470), 2.0f);
    createMonster(EnemyType::Type2, Vec2(740, 470), 4.0f);
    createMonster(EnemyType::Type2, Vec2(740, 470), 6.0f);
    createMonster(EnemyType::Type2, Vec2(740, 470), 8.0f);
    createMonster(EnemyType::Type2, Vec2(740, 470), 10.0f);


    // ��һ��ʱ�䣬������������ֹ���
    scheduleOnce(CC_SCHEDULE_SELECTOR(Map2Scene::spawnThirdTypeMonsters), 12.0f);
}

void Map2Scene::spawnThirdTypeMonsters(float dt)
{
    // ������������ֹ������ӵ�������
    createMonster(EnemyType::Type3, Vec2(740, 470), 2.0f);
    createMonster(EnemyType::Type3, Vec2(740, 470), 4.0f);
    createMonster(EnemyType::Type3, Vec2(740, 470), 6.0f);
    createMonster(EnemyType::Type3, Vec2(740, 470), 8.0f);
    createMonster(EnemyType::Type3, Vec2(740, 470), 10.0f);
}

void Map2Scene::createMonster(EnemyType type, const Vec2& position, float delay)
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
        monster->setPath({ Vec2(740, 190), Vec2(605, 190), Vec2(605, 330), Vec2(340, 330), Vec2(340, 390) ,
         Vec2(145, 390), Vec2(145, 200), Vec2(210, 200), Vec2(210, 125), Vec2(490, 125) }); // ���ù�����ƶ�·��
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
        addChild(monster, 3);
        monster->move(); // ����������ƶ�
        CCLOG("Monster created successfully!");  // �����־
        });

    // ����һ�����ж����������ӳٺʹ�������Ķ���
    auto sequenceAction = Sequence::create(delayAction, createMonsterAction, nullptr);

    // ִ�����ж���
    runAction(sequenceAction);

}

void Map2Scene::createCarrot()
{
    // �����ͳ�ʼ������ֵ��
    carrotHealthBarBackground = Sprite::create("hlb_hb_bg.png");
    carrotHealthBarBackground->setPosition(Vec2(500,215));  // �������λ�õ�����
    carrot->addChild(carrotHealthBarBackground, 4);

    carrotHealthBarForeground = ProgressTimer::create(Sprite::create("hlb_hb_fg.png"));
    carrotHealthBarForeground->setType(ProgressTimer::Type::BAR);
    carrotHealthBarForeground->setMidpoint(Vec2(0, 0.5));
    carrotHealthBarForeground->setBarChangeRate(Vec2(1, 0));
    carrotHealthBarForeground->setPercentage(carrotHealth);
    carrotHealthBarForeground->setPosition(Vec2(500, 215));  // �������λ�õ�����
    carrot->addChild(carrotHealthBarForeground, 5);
}

void Map2Scene::updateCarrotHealthBar()
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
        addChild(pauseLayer, 999); // ʹ�ýϸߵ� Z ˳��ȷ�������ϲ�
        pauseLayer->showPauseMenu();
    }
}

void Map2Scene::onResumeButtonClicked(Ref* sender)
{
    if (pauseLayer)
    {
        pauseLayer->hidePauseMenu();
        pauseLayer = nullptr; // �ͷ� PauseLayer ����
    }
}

void Map2Scene::onGameFailed()
{
    // ��ͣ��Ϸ
    Director::getInstance()->pause();

    // �л�����Ϸʧ�ܳ���
    auto gameOverScene = GameOverScene2::create();
    Director::getInstance()->replaceScene(gameOverScene);
}



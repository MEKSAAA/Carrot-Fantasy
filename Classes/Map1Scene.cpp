#include "CarrotFirstScene.h"
#include "SecondScene.h"
#include "Map1Scene.h"
#include "Tower.h"
#include "SimpleAudioEngine.h"
#include "Enemy.h"
#include"cocos2d.h"
#include"Carrot.h"
#include"PauseLayer.h"
#include"GameOverScene.h"
#include"PauseLayer.h"
#include"GameOverScene.h"
#include"WinScene1.h"
#include<string>

using namespace std;

USING_NS_CC;
int money_1 = 700;

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

    auto sprite_1 = Sprite::create("start01.png");   //�������
    sprite_1->setPosition(Vec2(visibleSize.width / 2 + origin.x-310, visibleSize.height / 2 + origin.y+210));
    this->addChild(sprite_1, 2);
    /*-------------------------------------------------------------------------------------------------------------------------*/

    map = TMXTiledMap::create("map_1.tmx");
    addChild(map);//��ʼ����ͼ
    objectGroup = map->getObjectGroup("bottle");   //��ȡ��Ƭ��ͼ�е�point�����
    objs = objectGroup->getObjects();

    auto Listener = cocos2d::EventListenerTouchOneByOne::create();//��ʼ��������
    Listener->onTouchBegan = CC_CALLBACK_2(Map1Scene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Listener, this);

    /*-------------------------------------------------------------------------------------------------------------------------*/

    //  ��ʼ����ͣ��
    pauseLayer = nullptr;

    /*-------------------------------------------------------------------------------------------------------------------------*/
    //  ��ʼ���ܲ�
    /*carrot = Carrot::create();
    carrot->setPosition(Vec2(860, 520));
    carrotHealth = 100;
    carrot->setHealth(100);
    createCarrot();
    addChild(carrot, 3);*/


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
    auto sprite_bg = Sprite::create("stagemap_toolbar_rightbg.png");            //������ҳ+���
    if (sprite_bg == nullptr)
    {
        problemLoading("'stagemap_toolbar_rightbg.png'");
    }
    else
    {
        sprite_bg->setPosition(Vec2(visibleSize.width / 2 + origin.x + 350, visibleSize.height / 2 + origin.y + 251));
        this->addChild(sprite_bg, 3);
    }

    auto closeItem = MenuItemImage::create(                       //���عؿ�ҳ��
        "stagemap_toolbar_home.png",
        "stagemap_toolbar_home.png",
        CC_CALLBACK_1(Map1Scene::menuCloseCallback, this));
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
        closeItem->setPosition(Vec2(x, y + 548));
    }
    auto menu2 = Menu::create(closeItem, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2, 4);

    string moneyText = StringUtils::format("%d", money_1);
    auto label = Label::createWithTTF("Money:" + moneyText, "fonts/Marker Felt.ttf", 24);    //Money
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        label->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2 -100, origin.y + closeItem->getContentSize().height / 2 +548));
        this->addChild(label, 4);
    }

    /*------------------------------------------------------------------------------------*/
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

    if (pauseItem == nullptr ||
        pauseItem->getContentSize().width <= 0 ||
        pauseItem->getContentSize().height <= 0 ||
        resumeItem == nullptr ||
        resumeItem->getContentSize().width <= 0 ||
        resumeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseSelected.png', 'pause_0.png', and 'resume_0.png'");
    }
    else
    {
        float xPause = 880; 
        float yPause = 25;
        pauseItem->setPosition(Vec2(xPause, yPause));

        float xResume = 830;
        float yResume = 25;
        resumeItem->setPosition(Vec2(xResume, yResume));
    }

    // ��Ӱ�ť���˵�
    auto menu = Menu::create(pauseItem, resumeItem, nullptr);
    menu->setPosition(Vec2(0, 0));
    this->addChild(menu, 9);
    /*-------------------------------------------------------------------------------------------------------------------------*/

    // ������������ֵ�İ�ť
    addHealthButton = cocos2d::MenuItemImage::create(
        "carrot_upgrade2.png",   // δ����״̬��ͼƬ
        "carrot_upgrade2_selected.png", // ����״̬��ͼƬ
        CC_CALLBACK_1(Map1Scene::onAddHealthButtonClicked, this));

    if (addHealthButton)
    {
        addHealthButton->setPosition(Vec2(770, 33)); // ���ð�ť��λ��
        addHealthButton->setEnabled(true); // ��ť��ʼ����
        auto menu = cocos2d::Menu::create(addHealthButton, nullptr);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 10);
    }

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
//��������
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
                selection->setPosition(Vec2(x+20, y+60));
                addChild(selection,3);
                selecting = true;

                towerButton1 = cocos2d::ui::Button::create("Bottle01.png");
                towerButton1->setPosition(Vec2(35, -35));
                towerButton2 = cocos2d::ui::Button::create("TBlueStar-hd1.png");
                towerButton2->setPosition(Vec2(-35, -35));
                towerButton3 = cocos2d::ui::Button::create("TFireBottle-hd1.png");
                towerButton3->setPosition(Vec2(105, -35));
                selection->addChild(towerButton1);
                selection->addChild(towerButton2);
                selection->addChild(towerButton3);

                /*������������������Ϊ��ť��������������/ɾ����
                  ��������״�������ǵ��ú�������Ϊ�ں������ù����в������ݻᱻ�Զ��ͷŵ��¶�ʧ*/
                towerButton1->addClickEventListener([=](cocos2d::Ref* sender) {
                    /*buttonClickCallBack(sender, Vec2(x, y), bottle);*/
                    removeChild(selection, true);//ɾ��ѡ�񷽿�Ͱ�ť
                    selection = NULL;
                    selecting = false;

                    Tower* newTower;
                    
                    newTower = BottleTower::create();

                    newTower->PlaceTower(Vec2(x,y));//����
                    std::shared_ptr<Tower> sharedTower = std::make_shared<BottleTower>(newTower);
                    mTowerList.push_back(sharedTower);
                    shootBullet(sharedTower);

                    newTower->getBottom()->addClickEventListener([this, sharedTower](cocos2d::Ref* sender) {   
                        if (selecting == true && selection != NULL) {//ɾ��ѡ���Բ��Ͱ�ť
                            removeChild(selection, true);
                            selection = NULL;
                            selecting = false;
                            return;
                        }
                        selection = Sprite::create("UPGorDLT.png");
                        selection->setPosition(Vec2(sharedTower->getPosition().x+20, sharedTower->getPosition().y+50));
                        addChild(selection, 3);
                        selecting = true;

                        dltButton = cocos2d::ui::Button::create("dlt.png");//ɾ����ť
                        upgButton = cocos2d::ui::Button::create("upg.png");//������ť
                        noupgButton = cocos2d::ui::Button::create("MaxLV.png");//������ť
                        dltButton->setPosition(Vec2(165,10));
                        upgButton->setPosition(Vec2(165, 330));
                        noupgButton->setPosition(Vec2(165, 330));
                        selection->addChild(dltButton);
                        if(sharedTower->getLV() != 3)
                            selection->addChild(upgButton);
                        else
                            selection->addChild(noupgButton);
                        dltButton->addClickEventListener([this, sharedTower](cocos2d::Ref* sender) {
                            auto it = mTowerList.begin();
                            int count = 1;
                            for (; it != mTowerList.end(); it++, count++) {
                                if ((*it)->getPosition() == sharedTower->getPosition())
                                    break;
                            }
                            unschedule("shoot_schedule_key" + to_string(count));//�����ѽ��������б��ҵ���������Ӧ��key��Ȼ��unschedule
                            mTowerList.erase(it);//�����������б���"ɾ��"
                            sharedTower->getBottom()->removeFromParent();
                            removeChild(selection, true);
                            selection = NULL;
                            selecting = false;
                            });
                        upgButton->addClickEventListener([this, sharedTower](cocos2d::Ref* sender) {
                            /*buttonClickCallBackUPG(sender);*/
                            sharedTower->lvUP();
                            removeChild(selection, true);
                            selection = NULL;
                            selecting = false;
                            });
                        
                        });
                    });
                towerButton2->addClickEventListener([=](cocos2d::Ref* sender) {
                    /*buttonClickCallBack(sender, Vec2(x, y), bottle);*/
                    removeChild(selection, true);//ɾ��ѡ�񷽿�Ͱ�ť
                    selection = NULL;
                    selecting = false;

                    Tower* newTower;

                    newTower = IceTower::create();

                    newTower->PlaceTower(Vec2(x, y));//����
                    std::shared_ptr<Tower> sharedTower = std::make_shared<IceTower>(newTower);
                    mTowerList.push_back(sharedTower);
                    shootBullet(sharedTower);

                    newTower->getBottom()->addClickEventListener([this, sharedTower](cocos2d::Ref* sender) {
                        if (selecting = true && selection != NULL) {
                            removeChild(selection, true);
                            selection = NULL;
                            selecting = false;
                            return;
                        }
                        selection = Sprite::create("UPGorDLT.png");
                        selection->setPosition(Vec2(sharedTower->getPosition().x + 20, sharedTower->getPosition().y + 50));
                        addChild(selection, 3);
                        selecting = true;

                        dltButton = cocos2d::ui::Button::create("dlt.png");
                        upgButton = cocos2d::ui::Button::create("upg.png");
                        noupgButton = cocos2d::ui::Button::create("MaxLV.png");
                        dltButton->setPosition(Vec2(165, 10));
                        upgButton->setPosition(Vec2(165, 330));
                        noupgButton->setPosition(Vec2(165, 330));
                        selection->addChild(dltButton);
                        if (sharedTower->getLV() != 3)
                            selection->addChild(upgButton);
                        else
                            selection->addChild(noupgButton);
                        dltButton->addClickEventListener([this, sharedTower](cocos2d::Ref* sender) {
                            auto it = mTowerList.begin();
                            int count = 1;
                            for (; it != mTowerList.end(); it++, count++) {
                                if ((*it)->getPosition() == sharedTower->getPosition())
                                    break;
                            }
                            unschedule("shoot_schedule_key" + to_string(count));
                            mTowerList.erase(it);
                            sharedTower->getBottom()->removeFromParent();
                            removeChild(selection, true);
                            selection = NULL;
                            selecting = false;

                            });
                        upgButton->addClickEventListener([this, sharedTower](cocos2d::Ref* sender) {
                            /*buttonClickCallBackUPG(sender);*/
                            sharedTower->lvUP();
                            removeChild(selection, true);
                            selection = NULL;
                            selecting = false;

                            });
                        });
                    });
                towerButton3->addClickEventListener([=](cocos2d::Ref* sender) {
                    removeChild(selection, true);//ɾ��ѡ�񷽿�Ͱ�ť
                    selection = NULL;
                    selecting = false;

                    Tower* newTower;

                    newTower = FireTower::create();

                    newTower->PlaceTower(Vec2(x, y));//����
                    std::shared_ptr<Tower> sharedTower = std::make_shared<FireTower>(newTower);
                    mTowerList.push_back(sharedTower);
                    {
                        shootBullet(sharedTower);
                    }
                    newTower->getBottom()->addClickEventListener([this, sharedTower](cocos2d::Ref* sender) {
                        /*buttonClickCallBack1(sender, pos);*/
                        if (selecting = true && selection != NULL) {
                            removeChild(selection, true);
                            selection = NULL;
                            selecting = false;
                            return;
                        }
                        selection = Sprite::create("UPGorDLT.png");
                        //sharedTower->getBottom()->setTouchEnabled(false);
                        selection->setPosition(Vec2(sharedTower->getPosition().x + 20, sharedTower->getPosition().y + 50));
                        addChild(selection, 3);
                        selecting = true;

                        dltButton = cocos2d::ui::Button::create("dlt.png");
                        upgButton = cocos2d::ui::Button::create("upg.png");
                        noupgButton = cocos2d::ui::Button::create("MaxLV.png");
                        dltButton->setPosition(Vec2(165, 10));
                        upgButton->setPosition(Vec2(165, 330));
                        noupgButton->setPosition(Vec2(165, 330));
                        selection->addChild(dltButton);
                        if (sharedTower->getLV() != 3)
                            selection->addChild(upgButton);
                        else
                            selection->addChild(noupgButton);
                        dltButton->addClickEventListener([this, sharedTower](cocos2d::Ref* sender) {
                            auto it = mTowerList.begin();
                            int count = 1;
                            for (; it != mTowerList.end(); it++, count++) {
                                if ((*it)->getPosition() == sharedTower->getPosition())
                                    break;
                            }
                            unschedule("shoot_schedule_key" + to_string(count));
                            mTowerList.erase(it);
                            sharedTower->getBottom()->removeFromParent();
                            removeChild(selection, true);
                            selection = NULL;
                            selecting = false;

                            });
                        upgButton->addClickEventListener([this, sharedTower](cocos2d::Ref* sender) {
                            /*buttonClickCallBackUPG(sender);*/
                            sharedTower->lvUP();
                            removeChild(selection, true);
                            selection = NULL;
                            selecting = false;

                            });

                        });
                    });
                
            }
        }
    }
    return true;
}

//�������Թ��ﲢ�������
void Map1Scene::shootBullet(std::shared_ptr<Tower> tower) {//���

    string shoot_schedule_key = "shoot_schedule_key" + std::to_string(mTowerList.size());
    Enemy* enemy = Enemy::createEnemy("F11.png", EnemyType::Type1);//����һ�������õĹ���
    enemy->setPosition(Vec2(tower->getPosition().x + 50, tower->getPosition().y + 100));
    enemy->setHealthBarPosition(Vec2(tower->getPosition().x + 200, tower->getPosition().y + 200)); //  ��������ֵ�����λ��
    this->addChild(enemy, 3);

    // ������ֵ����ӵ�������
    //this->addChild(enemy->getHealthBarBackground(), 3);
    //this->addChild(enemy->getHealthBarForeground(), 3);

    schedule([this, tower, enemy](float dt) {
        tower->Rotate(enemy->getPosition());

        auto bullet = Sprite::create(tower->getBltName());
        bullet->setPosition(Vec2(tower->getBottom()->getPosition().x, tower->getBottom()->getPosition().y));
        this->addChild(bullet, 3);

        Point shootVector = enemy->getPosition() - bullet->getPosition();//�������
        Point normalizedVector = ccpNormalize(shootVector);//��׼��

        float moveSpeed = 100;//�ӵ��ɵ��ٶ�
        float moveDuration = sqrt(shootVector.x * shootVector.x + shootVector.y * shootVector.y) / moveSpeed;

        auto move = MoveTo::create(moveDuration, enemy->getPosition());
        auto moveDone = CallFuncN::create(CC_CALLBACK_1(Map1Scene::shootFinish, this));
        auto sequence = Sequence::create(move, moveDone, nullptr);

        auto repeatAction = RepeatForever::create(sequence);

        bullet->runAction(repeatAction);

        // ����˺������߼�
        /*scheduleOnce([this, bullet, enemy, tower](float dt) {
            // �ӵ����й�����ù�������˷���
            enemy->takeAttack(tower->getAtkV());
            // �Ƴ��ӵ�
            removeChild(bullet);
            //bullet->removeFromParentAndCleanup(true);
            }, moveDuration, "bullet_hit_enemy_key");*/

    }, 1.0f, kRepeatForever, 0.0f, shoot_schedule_key);

}

//�������------------------��ɾtest
void Map1Scene::shootFinish(Node* pNode)
{
    Sprite* bullet = dynamic_cast<Sprite*>(pNode);
    if (bullet != NULL)
    {
        bullet->stopAllActions();
        this->removeChild(bullet, true);
    }   
}

//���عؿ�ѡ�����
void Map1Scene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
}

/*--------------------------------------------������ܲ�����Ϸ���̷���---------------------------------------------------------------------*/
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
        addChild(monster, 3);

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

    // �����ͳ�ʼ������ֵ Label
    carrotHealthLabel = Label::createWithTTF("10", "fonts/Marker Felt.ttf", 25);  // ʹ�ú��ʵ�������ֺ�
    carrotHealthLabel->setPosition(Vec2(880, 550));
    carrotHealthLabel->setColor(Color3B::ORANGE);  // ���� Label ����ɫ
    addChild(carrotHealthLabel, 6);  // ���ú��ʵ� Z ˳��
}

void Map1Scene::updateCarrotHealthBar()
{
    // ��������ֵ���İٷֱ�
    float percentage = static_cast<float>(carrotHealth) / 100.0f * 100.0f;
    carrotHealthBarForeground->setPercentage(percentage);

    // ��������ֵ Label ���ı�����
    string healthText = StringUtils::format("%d", carrotHealth / 10);
    carrotHealthLabel->setString(healthText);

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
    //  �Ƴ�����ֵ��
    if (carrotHealthBarBackground) {
        carrotHealthBarBackground->removeFromParent();
        carrotHealthBarBackground = nullptr;
    }

    if (carrotHealthBarForeground) {
        carrotHealthBarForeground->removeFromParent();
        carrotHealthBarForeground = nullptr;
    }

    //  �Ƴ�����ֵlabel
    if (carrotHealthLabel) {
        carrotHealthLabel->removeFromParent();
        carrotHealthLabel = nullptr;
    }
}

//����ˢ�·���
/*void Map1Scene::update(float dt)
{
    //������ĵ��˹���
    for (unsigned int i = 0; i < mEnemyList.size(); ++i)
    {
        //mTowerList[i]->Update(dt);
        //ˢ�·�����
        for (unsigned int k = 0; k < mTowerList.size(); ++k)
        {
            //mTowerList[i]->Update(dt);
            //������ĵ��˹���
            int v = mTowerList[k]->getrngV();
            bool bAtk = mTowerList[k]->Rotate(mEnemyList[i]->getPosition());
            if (bAtk)
            {
                break;
            }
        }
    }
    for (unsigned int k = 0; k < mTowerList.size(); ++k)
    {
        //mTowerList[i]->Update(dt);
        //������ĵ��˹���
        int v = mTowerList[k]->getrngV();
        int a = 1;
    }



    //ˢ���ӵ��߼�

}*/


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
    //auto gameOverScene = WinScene1::create(carrotHealth);//���ڵ���Ӯ�ֵ����
    //Director::getInstance()->replaceScene(gameOverScene);
}

void Map1Scene::onAddHealthButtonClicked(cocos2d::Ref* sender)
{
    if (addHealthButtonCount < 2 && carrot && carrot->getHealth() < 100)
    {
        // ��ť������δ����ʹ�ô����������ܲ�����ֵδ��
        carrot->increaseHealth(10);
        carrotHealth += 10;

        // �������UI�Ͱ�ť״̬
        carrot->updateCarrotAnimation();
        updateCarrotHealthBar();
        updateAddHealthButtonState();

        // ���Ӱ�ťʹ�ô���
        addHealthButtonCount++;

        // ���İ�ťͼƬ
        updateAddHealthButtonImage();
    }
}

void Map1Scene::updateAddHealthButtonState()
{
    if (addHealthButton)
    {
        // �������ֵ�������߰�ťʹ�ô����������ƣ�����ð�ť
        addHealthButton->setEnabled(carrot->getHealth() < 100 && addHealthButtonCount < 2);
    }

    if (addHealthButtonCount >= 2)
    {
        // ���ð�ť
        addHealthButton->setEnabled(false);

        // ���İ�ťͼƬΪ����״̬��ͼƬ
        updateAddHealthButtonImage();
    }
}

void Map1Scene::updateAddHealthButtonImage()
{
    if (addHealthButton)
    {
        // ����ʹ�ô������İ�ť��ͼƬ
        std::string normalImage, selectedImage;
        switch (addHealthButtonCount)
        {
            case 0:
                normalImage = "carrot_upgrade2.png";
                selectedImage = "carrot_upgrade2_selected.png";
                break;
            case 1:
                normalImage = "carrot_upgrade1.png";
                selectedImage = "carrot_upgrade1_selected.png";
                break;
            default:
                normalImage = "carrot_upgrade0.png";
                selectedImage = "carrot_upgrade0_selected.png";
                break;
        }

        // ���ð�ť��ͼƬ
        addHealthButton->setNormalImage(cocos2d::Sprite::create(normalImage));
        addHealthButton->setSelectedImage(cocos2d::Sprite::create(selectedImage));
    }
}

void Map1Scene::onEnter()
{
    Scene::onEnter();

    resetCarrot();
}

void Map1Scene::resetCarrot()
{
    Director::getInstance()->resume();


    // �Ƴ�֮ǰ���ܲ�����
    if (carrot)
    {
        carrot->removeFromParent();
        carrot->release();
        carrot = nullptr;
    }

    // ���´����ͳ�ʼ���ܲ�
    carrot = Carrot::create();
    carrot->setPosition(Vec2(860, 520));
    carrotHealth = 100;
    carrot->setHealth(100);
    createCarrot();
    addChild(carrot, 3);
}


/*--------------------------------------------������ܲ�����Ϸ���̷���---------------------------------------------------------------------*/


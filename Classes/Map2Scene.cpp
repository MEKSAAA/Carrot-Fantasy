#include "CarrotFirstScene.h"
#include "SecondScene.h"
#include "Map2Scene.h"
#include "SimpleAudioEngine.h"
#include "Enemy.h"
#include "Tower.h"
#include"cocos2d.h"
#include"Carrot.h"
#include"PauseLayer.h"
#include"GameOverScene2.h"
using namespace std;

USING_NS_CC;
string money_2 = "900";

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

    auto sprite_1 = Sprite::create("start01.png");             //�������
    sprite_1->setPosition(Vec2(visibleSize.width / 2 + origin.x + 310, visibleSize.height / 2 + origin.y + 210));
    this->addChild(sprite_1, 1);
    /*-------------------------------------------------------------------------------------------------------------------------*/
    //...��ͼmap_2.tmx?
    map = TMXTiledMap::create("map_2.tmx");
    addChild(map);//��ʼ����ͼ
    objectGroup = map->getObjectGroup("bottle");   //��ȡ��Ƭ��ͼ�е�point�����
    objs = objectGroup->getObjects();

    /*for (const auto& obj : objs)    //���ð�ť
    {
        auto valueMap = obj.asValueMap();
        auto button = ui::Button::create("select_01.png", "select_01.png");
        //��ť��λ������
        button->setPosition(Vec2(valueMap["x"].asFloat(), valueMap["y"].asFloat()));
        button->setVisible(false);
        button->addTouchEventListener([button](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
            if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
                button->setVisible(true);
            }
            });
        addChild(button);
    }*/
    auto Listener = cocos2d::EventListenerTouchOneByOne::create();//��ʼ��������
    Listener->onTouchBegan = CC_CALLBACK_2(Map2Scene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Listener, this);

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
    auto sprite_bg = Sprite::create("stagemap_toolbar_rightbg.png");            //������ҳ+���
    if (sprite_bg == nullptr)
    {
        problemLoading("'stagemap_toolbar_rightbg.png'");
    }
    else
    {
        sprite_bg->setPosition(Vec2(visibleSize.width / 2 + origin.x + 350, visibleSize.height / 2 + origin.y + 251));
        this->addChild(sprite_bg, 1);
    }

    auto closeItem = MenuItemImage::create(                       //���عؿ�ҳ��
        "stagemap_toolbar_home.png",
        "stagemap_toolbar_home.png",
        CC_CALLBACK_1(Map2Scene::menuCloseCallback, this));
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
    this->addChild(menu2, 2);

    auto label = Label::createWithTTF("Money:"+money_2, "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        label->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2 - 100, origin.y + closeItem->getContentSize().height / 2 + 548));
        this->addChild(label, 4);
    }

    /*---------------------------------------------------------------------------------------------------------------*/
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

    if (pauseItem == nullptr ||
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
        float xPause = 880; // 10 �ǰ�ť֮��ļ��
        float yPause = 15;
        pauseItem->setPosition(Vec2(xPause, yPause));

        float xResume = 830;
        float yResume = 15;
        resumeItem->setPosition(Vec2(xResume, yResume));
    }

    // ��Ӱ�ť���˵�
    auto menu = Menu::create( pauseItem, resumeItem, nullptr);
    menu->setPosition(Vec2(0, 0));
    this->addChild(menu, 9);

    /*-------------------------------------------------------------------------------------------------------------------------*/

     // ʹ�ö�ʱ��������һ������
    scheduleOnce(CC_SCHEDULE_SELECTOR(Map2Scene::spawnMonsters), 1.0f);

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
bool Map2Scene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
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
                selection->setPosition(Vec2(x + 30, y + 30));
                addChild(selection, 3);
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
                towerButton1->addClickEventListener([=](cocos2d::Ref* sender) {
                    /*buttonClickCallBack(sender, Vec2(x, y), bottle);*/
                    auto ob = find_if(objs.begin(), objs.end(), [=](const Value& cnt) {
                        auto cntVM = cnt.asValueMap();
                        return x == cntVM["x"].asInt() && y == cntVM["y"].asInt(); });//�α��������objs���ҵ���ǰҪ������λ��
                    if (ob != objs.end()) {
                        objs.erase(ob);//��objs��ɾ�������������꣬�����Ͳ����ٷŵڶ�����
                    }
                    removeChild(selection, true);//ɾ��ѡ�񷽿�Ͱ�ť
                    selection = NULL;
                    selecting = false;

                    Tower* newTower;

                    newTower = BottleTower::create();

                    newTower->PlaceTower(Vec2(x, y));//����
                    std::shared_ptr<Tower> sharedTower = std::make_shared<Tower>(newTower);
                    newTower->getBottom()->addClickEventListener([this, sharedTower](cocos2d::Ref* sender) {
                        /*buttonClickCallBack1(sender, pos);*/
                        selection = Sprite::create("UPGorDLT.png");
                        selection->setPosition(Vec2(sharedTower->getPosition().x + 20, sharedTower->getPosition().y + 50));
                        addChild(selection, 3);
                        selecting = true;

                        dltButton = cocos2d::ui::Button::create("dlt.png");
                        upgButton = cocos2d::ui::Button::create("upg.png");
                        dltButton->setPosition(Vec2(165, 10));
                        upgButton->setPosition(Vec2(165, 330));//λ�ò��� ���޸ġ�
                        selection->addChild(dltButton);
                        selection->addChild(upgButton);
                        dltButton->addClickEventListener([this, sharedTower](cocos2d::Ref* sender) {
                            /*buttonClickCallBackDLT(sender);*/
                            sharedTower->getBottom()->removeFromParent();
                            });
                        });

                    //test rotation
                    auto ENEMY = Sprite::create("p11.png");
                    ENEMY->setPosition(Vec2(x + 20, y + 200));
                    this->addChild(ENEMY, 3);
                    newTower->Rotate(ENEMY->getPosition());
                    auto bullet = Sprite::create("pBottle12.png");
                    bullet->setPosition(Vec2(mapPos.x + 20, mapPos.y + 50));
                    this->addChild(bullet, 4);
                    Vec2 tt = bullet->getPosition();
                    //�估��������                          //��������
                    Point shootVector = ENEMY->getPosition() - bullet->getPosition();
                    // ������׼��
                    Point normalizedVector = ccpNormalize(shootVector);
                    // �ƶ���������
                    Point overShootVector = normalizedVector * 1000;
                    // ������Ļ�ĵ�
                    Point offScreenPoint = bullet->getPosition() + overShootVector;
                    // �����ٶ�Ϊ500��pix/s��
                    float moveSpeed = 50;
                    // �ƶ�ʱ��
                    float moveDuration = sqrt(shootVector.x * shootVector.x + shootVector.y * shootVector.y) / moveSpeed;
                    // ִ�����
                    auto move = MoveTo::create(moveDuration, offScreenPoint);
                    CallFunc* moveDone = CallFunc::create(CC_CALLBACK_0(Map2Scene::shootFinish, this, bullet));
                    bullet->runAction(Sequence::create(move, moveDone, NULL));

                    });
                towerButton2->addClickEventListener([=](cocos2d::Ref* sender) {buttonClickCallBack(sender, Vec2(x, y), ice); });
                towerButton3->addClickEventListener([=](cocos2d::Ref* sender) {buttonClickCallBack(sender, Vec2(x, y), fire); });
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
//���------test
void Map2Scene::shootFinish(Node* pNode)
{
    Sprite* bullet = (Sprite*)pNode;
    if (bullet != NULL)
    {
        bullet->stopAllActions();

    }
    this->removeChild(bullet, true);
}
//����
void Map2Scene::buttonClickCallBack(cocos2d::Ref* sender, const cocos2d::Vec2& pos, const int towerType)
{
    auto ob = find_if(objs.begin(), objs.end(), [=](const Value& cnt) {
        auto cntVM = cnt.asValueMap();
        return pos.x == cntVM["x"].asInt() && pos.y == cntVM["y"].asInt(); });//�α��������objs���ҵ���ǰҪ������λ��
    if (ob != objs.end()) {
        objs.erase(ob);//��objs��ɾ�������������꣬�����Ͳ����ٷŵڶ�����
    }
    removeChild(selection, true);//ɾ��ѡ�񷽿�Ͱ�ť
    selection = NULL;
    selecting = false;

    Tower* newTower;
    switch (towerType) {
    case 0:
        newTower = BottleTower::create();
        break;
    case 1:
        newTower = IceTower::create();
        break;
    case 2:
        newTower = FireTower::create();
        break;
    default:
        break;
    }

    newTower->PlaceTower(pos);//����

    newTower->getBottom()->addClickEventListener([=](cocos2d::Ref* sender) {buttonClickCallBack1(sender, pos); });

    //test rotation
    auto ENEMY = Sprite::create("p11.png");
    ENEMY->setPosition(Vec2(pos.x + 20, pos.y + 200));
    this->addChild(ENEMY, 3);
    newTower->Rotate(ENEMY->getPosition());

    //test Attack
    //newTower->Attack(ENEMY);
}
//������ɾ��
void Map2Scene::buttonClickCallBack1(cocos2d::Ref* sender, const cocos2d::Vec2& pos)
{
    /*/auto tw = find_if(tws.begin(), tws.end(), [=](const Value& cnt) {
        auto cntVM = cnt.asValueMap();
        return pos.x == cntVM["x"].asInt() && pos.y == cntVM["y"].asInt(); });//�α��������objs���ҵ���ǰҪ������λ��
    if (choice == 0) {
        if (tw != tws.end()) {
            objs.push_back(*tw);
            tws.erase(tw);//��objs��ɾ�������������꣬�����Ͳ����ٷŵڶ�����
        }
        auto tgtTW = existedTW.begin();
        for (; tgtTW != existedTW.end(); tgtTW++) {
            if ((*tgtTW)->getPosition() == pos)
                break;
        }
        Director::getInstance()->getRunningScene()->removeChild((*tgtTW)->getBottom());
        existedTW.erase(tgtTW);
    }
    removeChild(selection, true);//ɾ��ѡ�񷽿�Ͱ�ť
    selection = NULL;
    selecting = false;*/

    selection = Sprite::create("UPGorDLT.png");
    selection->setPosition(Vec2(pos.x + 20, pos.y + 50));
    addChild(selection, 3);
    selecting = true;

    dltButton = cocos2d::ui::Button::create("dlt.png");
    upgButton = cocos2d::ui::Button::create("upg.png");
    dltButton->setPosition(Vec2(20, -55));
    upgButton->setPosition(Vec2(20, 95));//λ�ò��� ���޸ġ�
    selection->addChild(dltButton);
    selection->addChild(upgButton);
    dltButton->addClickEventListener([=](cocos2d::Ref* sender) {buttonClickCallBackDLT(sender); });

}
//ɾ��
void Map2Scene::buttonClickCallBackDLT(cocos2d::Ref* sender)
{
    selection->removeFromParent();
}
//���عؿ�ѡ�����
void Map2Scene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
}
/*--------------------------------------------������ܲ�����Ϸ���̷���---------------------------------------------------------------------*/
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

/*--------------------------------------------������ܲ�����Ϸ���̷���---------------------------------------------------------------------*/

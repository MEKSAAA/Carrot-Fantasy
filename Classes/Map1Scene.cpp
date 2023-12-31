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

    auto sprite_1 = Sprite::create("start01.png");   //怪物入口
    sprite_1->setPosition(Vec2(visibleSize.width / 2 + origin.x-310, visibleSize.height / 2 + origin.y+210));
    this->addChild(sprite_1, 2);
    /*-------------------------------------------------------------------------------------------------------------------------*/

    map = TMXTiledMap::create("map_1.tmx");
    addChild(map);//初始化地图
    objectGroup = map->getObjectGroup("bottle");   //获取瓦片地图中的point对象层
    objs = objectGroup->getObjects();

    auto Listener = cocos2d::EventListenerTouchOneByOne::create();//初始化监听器
    Listener->onTouchBegan = CC_CALLBACK_2(Map1Scene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Listener, this);

    /*-------------------------------------------------------------------------------------------------------------------------*/

    //  初始化暂停层
    pauseLayer = nullptr;

    /*-------------------------------------------------------------------------------------------------------------------------*/
    //  初始化萝卜
    /*carrot = Carrot::create();
    carrot->setPosition(Vec2(860, 520));
    carrotHealth = 100;
    carrot->setHealth(100);
    createCarrot();
    addChild(carrot, 3);*/


    /*
    // 创建单个敌人（用于调试）
    Enemy* enemy1 = Enemy::createEnemy("F21.png");
    enemy1->setPath({ Vec2(280, 455), Vec2(280, 195), Vec2(675, 195), Vec2(675, 460), Vec2(820, 460) }); // 设置敌人的移动路径
    enemy1->setSpeed(70.0f);  //  设置敌人速度
    enemy1->setStartPosition(Vec2(150, 455));  // 设置起始位置
    enemy1->setHealthBarPosition(Vec2(40, 95));  //  设置生命值条相对位置
    enemy1->setHealth(50);//用于调试生命值
    addChild(enemy1, 3);
    enemy1->move(); // 启动敌人的移动
    */

    /*-------------------------------------------------------------------------------------------------------------------------*/
    //  创建关闭按钮
    auto sprite_bg = Sprite::create("stagemap_toolbar_rightbg.png");            //返回首页+金币
    if (sprite_bg == nullptr)
    {
        problemLoading("'stagemap_toolbar_rightbg.png'");
    }
    else
    {
        sprite_bg->setPosition(Vec2(visibleSize.width / 2 + origin.x + 350, visibleSize.height / 2 + origin.y + 251));
        this->addChild(sprite_bg, 3);
    }

    auto closeItem = MenuItemImage::create(                       //返回关卡页面
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
    //  创建暂停按钮
    auto pauseItem = MenuItemImage::create(
        "pause_0.png",
        "pause_0.png",
        CC_CALLBACK_1(Map1Scene::onPauseButtonClicked, this));

    // 创建继续按钮
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

    // 添加按钮到菜单
    auto menu = Menu::create(pauseItem, resumeItem, nullptr);
    menu->setPosition(Vec2(0, 0));
    this->addChild(menu, 9);
    /*-------------------------------------------------------------------------------------------------------------------------*/

    // 创建增加生命值的按钮
    addHealthButton = cocos2d::MenuItemImage::create(
        "carrot_upgrade2.png",   // 未按下状态的图片
        "carrot_upgrade2_selected.png", // 按下状态的图片
        CC_CALLBACK_1(Map1Scene::onAddHealthButtonClicked, this));

    if (addHealthButton)
    {
        addHealthButton->setPosition(Vec2(770, 33)); // 设置按钮的位置
        addHealthButton->setEnabled(true); // 按钮初始可用
        auto menu = cocos2d::Menu::create(addHealthButton, nullptr);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 10);
    }

    /*-------------------------------------------------------------------------------------------------------------------------*/

     // 使用定时器创建第一个怪物
    scheduleOnce(CC_SCHEDULE_SELECTOR(Map1Scene::spawnMonsters), 1.0f);

    /*-------------------------------------------------------------------------------------------------------------------------*/



    // 注册怪物到达终点的监听器
    auto eventListener = EventListenerCustom::create("enemy_reached_destination", [&](EventCustom* event) {
        // 处理怪物到达终点的逻辑
        Enemy* enemy = static_cast<Enemy*>(event->getUserData());
        // 在这里实现萝卜被咬的逻辑
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
//触摸建塔
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

                /*下面三个都将底座作为按钮，用来处理升级/删除，
                  里面代码套代码而不是调用函数是因为在函数调用过程中部分数据会被自动释放导致丢失*/
                towerButton1->addClickEventListener([=](cocos2d::Ref* sender) {
                    /*buttonClickCallBack(sender, Vec2(x, y), bottle);*/
                    removeChild(selection, true);//删掉选择方框和按钮
                    selection = NULL;
                    selecting = false;

                    Tower* newTower;
                    
                    newTower = BottleTower::create();

                    newTower->PlaceTower(Vec2(x,y));//放塔
                    std::shared_ptr<Tower> sharedTower = std::make_shared<BottleTower>(newTower);
                    mTowerList.push_back(sharedTower);
                    shootBullet(sharedTower);

                    newTower->getBottom()->addClickEventListener([this, sharedTower](cocos2d::Ref* sender) {   
                        if (selecting == true && selection != NULL) {//删掉选择的圆框和按钮
                            removeChild(selection, true);
                            selection = NULL;
                            selecting = false;
                            return;
                        }
                        selection = Sprite::create("UPGorDLT.png");
                        selection->setPosition(Vec2(sharedTower->getPosition().x+20, sharedTower->getPosition().y+50));
                        addChild(selection, 3);
                        selecting = true;

                        dltButton = cocos2d::ui::Button::create("dlt.png");//删除按钮
                        upgButton = cocos2d::ui::Button::create("upg.png");//升级按钮
                        noupgButton = cocos2d::ui::Button::create("MaxLV.png");//满级按钮
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
                            unschedule("shoot_schedule_key" + to_string(count));//遍历已建的塔的列表，找到这座塔对应的key，然后unschedule
                            mTowerList.erase(it);//把这座塔从列表里"删掉"
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
                    removeChild(selection, true);//删掉选择方框和按钮
                    selection = NULL;
                    selecting = false;

                    Tower* newTower;

                    newTower = IceTower::create();

                    newTower->PlaceTower(Vec2(x, y));//放塔
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
                    removeChild(selection, true);//删掉选择方框和按钮
                    selection = NULL;
                    selecting = false;

                    Tower* newTower;

                    newTower = FireTower::create();

                    newTower->PlaceTower(Vec2(x, y));//放塔
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

//创建测试怪物并向它射击
void Map1Scene::shootBullet(std::shared_ptr<Tower> tower) {//射击

    string shoot_schedule_key = "shoot_schedule_key" + std::to_string(mTowerList.size());
    Enemy* enemy = Enemy::createEnemy("F11.png", EnemyType::Type1);//创建一个调试用的怪物
    enemy->setPosition(Vec2(tower->getPosition().x + 50, tower->getPosition().y + 100));
    enemy->setHealthBarPosition(Vec2(tower->getPosition().x + 200, tower->getPosition().y + 200)); //  设置生命值条相对位置
    this->addChild(enemy, 3);

    // 将生命值条添加到场景中
    //this->addChild(enemy->getHealthBarBackground(), 3);
    //this->addChild(enemy->getHealthBarForeground(), 3);

    schedule([this, tower, enemy](float dt) {
        tower->Rotate(enemy->getPosition());

        auto bullet = Sprite::create(tower->getBltName());
        bullet->setPosition(Vec2(tower->getBottom()->getPosition().x, tower->getBottom()->getPosition().y));
        this->addChild(bullet, 3);

        Point shootVector = enemy->getPosition() - bullet->getPosition();//射击向量
        Point normalizedVector = ccpNormalize(shootVector);//标准化

        float moveSpeed = 100;//子弹飞的速度
        float moveDuration = sqrt(shootVector.x * shootVector.x + shootVector.y * shootVector.y) / moveSpeed;

        auto move = MoveTo::create(moveDuration, enemy->getPosition());
        auto moveDone = CallFuncN::create(CC_CALLBACK_1(Map1Scene::shootFinish, this));
        auto sequence = Sequence::create(move, moveDone, nullptr);

        auto repeatAction = RepeatForever::create(sequence);

        bullet->runAction(repeatAction);

        // 添加伤害处理逻辑
        /*scheduleOnce([this, bullet, enemy, tower](float dt) {
            // 子弹击中怪物，调用怪物的受伤方法
            enemy->takeAttack(tower->getAtkV());
            // 移除子弹
            removeChild(bullet);
            //bullet->removeFromParentAndCleanup(true);
            }, moveDuration, "bullet_hit_enemy_key");*/

    }, 1.0f, kRepeatForever, 0.0f, shoot_schedule_key);

}

//射击结束------------------可删test
void Map1Scene::shootFinish(Node* pNode)
{
    Sprite* bullet = dynamic_cast<Sprite*>(pNode);
    if (bullet != NULL)
    {
        bullet->stopAllActions();
        this->removeChild(bullet, true);
    }   
}

//返回关卡选择界面
void Map1Scene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
}

/*--------------------------------------------怪物和萝卜、游戏进程方面---------------------------------------------------------------------*/
void Map1Scene::spawnMonsters(float dt)
{
    // 逐个创建怪物，并添加到场景中
    createMonster(EnemyType::Type1, Vec2(150, 455), 1.0f);
    createMonster(EnemyType::Type1, Vec2(150, 455), 2.0f);
    createMonster(EnemyType::Type1, Vec2(150, 455), 3.0f);
    createMonster(EnemyType::Type1, Vec2(150, 455), 4.0f);
    createMonster(EnemyType::Type1, Vec2(150, 455), 5.0f);

    // 过一段时间，逐个创建第二种怪物
    scheduleOnce(CC_SCHEDULE_SELECTOR(Map1Scene::spawnSecondTypeMonsters), 7.0f);
}

void Map1Scene::spawnSecondTypeMonsters(float dt)
{
    // 逐个创建第二种怪物，并添加到场景中
    createMonster(EnemyType::Type2, Vec2(150, 455), 2.0f);
    createMonster(EnemyType::Type2, Vec2(150, 455), 4.0f);
    createMonster(EnemyType::Type2, Vec2(150, 455), 6.0f);
    createMonster(EnemyType::Type2, Vec2(150, 455), 8.0f);
    createMonster(EnemyType::Type2, Vec2(150, 455), 10.0f);


    // 过一段时间，逐个创建第三种怪物
    scheduleOnce(CC_SCHEDULE_SELECTOR(Map1Scene::spawnThirdTypeMonsters), 12.0f);
}

void Map1Scene::spawnThirdTypeMonsters(float dt)
{
    // 逐个创建第三种怪物，并添加到场景中
    createMonster(EnemyType::Type3, Vec2(150, 455), 2.0f);
    createMonster(EnemyType::Type3, Vec2(150, 455), 4.0f);
    createMonster(EnemyType::Type3, Vec2(150, 455), 6.0f);
    createMonster(EnemyType::Type3, Vec2(150, 455), 8.0f);
    createMonster(EnemyType::Type3, Vec2(150, 455), 10.0f);
}

void Map1Scene::createMonster(EnemyType type, const Vec2& position, float delay)
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
        monster->setPath({ Vec2(280, 455), Vec2(280, 195), Vec2(675, 195), Vec2(675, 460), Vec2(820, 460) }); // 设置怪物的移动路径
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
        CCLOG("Monster created successfully!");  // 添加这一行日志

        });

    // 创建一个序列动作，包含延迟，创建怪物
    auto sequenceAction = Sequence::create(delayAction, createMonsterAction, nullptr);

    // 执行序列动作
    runAction(sequenceAction);
}

void Map1Scene::createCarrot()
{
    // 创建和初始化生命值条
    carrotHealthBarBackground = Sprite::create("hlb_hb_bg.png");
    carrotHealthBarBackground->setPosition(Vec2(830, 550));  // 设置相对位置的坐标
    carrot->addChild(carrotHealthBarBackground, 4);

    carrotHealthBarForeground = ProgressTimer::create(Sprite::create("hlb_hb_fg.png"));
    carrotHealthBarForeground->setType(ProgressTimer::Type::BAR);
    carrotHealthBarForeground->setMidpoint(Vec2(0, 0.5));
    carrotHealthBarForeground->setBarChangeRate(Vec2(1, 0));
    carrotHealthBarForeground->setPercentage(carrotHealth);
    carrotHealthBarForeground->setPosition(Vec2(830, 550));  // 设置相对位置的坐标
    carrot->addChild(carrotHealthBarForeground, 5);

    // 创建和初始化生命值 Label
    carrotHealthLabel = Label::createWithTTF("10", "fonts/Marker Felt.ttf", 25);  // 使用合适的字体和字号
    carrotHealthLabel->setPosition(Vec2(880, 550));
    carrotHealthLabel->setColor(Color3B::ORANGE);  // 设置 Label 的颜色
    addChild(carrotHealthLabel, 6);  // 设置合适的 Z 顺序
}

void Map1Scene::updateCarrotHealthBar()
{
    // 更新生命值条的百分比
    float percentage = static_cast<float>(carrotHealth) / 100.0f * 100.0f;
    carrotHealthBarForeground->setPercentage(percentage);

    // 更新生命值 Label 的文本内容
    string healthText = StringUtils::format("%d", carrotHealth / 10);
    carrotHealthLabel->setString(healthText);

    //检查萝卜是否死亡
    if (carrotHealth <= 0) {
        // 移除生命值条元素
        hideCarrotHealthBar();
        //  触发游戏失败事件
        onGameFailed();
    }
}

void Map1Scene::hideCarrotHealthBar()
{
    //  移除生命值条
    if (carrotHealthBarBackground) {
        carrotHealthBarBackground->removeFromParent();
        carrotHealthBarBackground = nullptr;
    }

    if (carrotHealthBarForeground) {
        carrotHealthBarForeground->removeFromParent();
        carrotHealthBarForeground = nullptr;
    }

    //  移除生命值label
    if (carrotHealthLabel) {
        carrotHealthLabel->removeFromParent();
        carrotHealthLabel = nullptr;
    }
}

//场景刷新方法
/*void Map1Scene::update(float dt)
{
    //找最近的敌人攻击
    for (unsigned int i = 0; i < mEnemyList.size(); ++i)
    {
        //mTowerList[i]->Update(dt);
        //刷新防御塔
        for (unsigned int k = 0; k < mTowerList.size(); ++k)
        {
            //mTowerList[i]->Update(dt);
            //找最近的敌人攻击
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
        //找最近的敌人攻击
        int v = mTowerList[k]->getrngV();
        int a = 1;
    }



    //刷新子弹逻辑

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
        addChild(pauseLayer, 999); // 使用较高的 Z 顺序确保在最上层
        pauseLayer->showPauseMenu();
    }
}

void Map1Scene::onResumeButtonClicked(Ref* sender)
{
    if (pauseLayer)
    {
        pauseLayer->hidePauseMenu();
        pauseLayer = nullptr; // 释放 PauseLayer 对象
    }
}

void Map1Scene::onGameFailed()
{
    // 暂停游戏
    Director::getInstance()->pause();

    // 切换到游戏失败场景
    auto gameOverScene = GameOverScene::create();
    Director::getInstance()->replaceScene(gameOverScene);
    //auto gameOverScene = WinScene1::create(carrotHealth);//用于调试赢局的情况
    //Director::getInstance()->replaceScene(gameOverScene);
}

void Map1Scene::onAddHealthButtonClicked(cocos2d::Ref* sender)
{
    if (addHealthButtonCount < 2 && carrot && carrot->getHealth() < 100)
    {
        // 按钮可用且未超过使用次数限制且萝卜生命值未满
        carrot->increaseHealth(10);
        carrotHealth += 10;

        // 更新相关UI和按钮状态
        carrot->updateCarrotAnimation();
        updateCarrotHealthBar();
        updateAddHealthButtonState();

        // 增加按钮使用次数
        addHealthButtonCount++;

        // 更改按钮图片
        updateAddHealthButtonImage();
    }
}

void Map1Scene::updateAddHealthButtonState()
{
    if (addHealthButton)
    {
        // 如果生命值已满或者按钮使用次数超过限制，则禁用按钮
        addHealthButton->setEnabled(carrot->getHealth() < 100 && addHealthButtonCount < 2);
    }

    if (addHealthButtonCount >= 2)
    {
        // 禁用按钮
        addHealthButton->setEnabled(false);

        // 更改按钮图片为禁用状态的图片
        updateAddHealthButtonImage();
    }
}

void Map1Scene::updateAddHealthButtonImage()
{
    if (addHealthButton)
    {
        // 根据使用次数更改按钮的图片
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

        // 设置按钮的图片
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


    // 移除之前的萝卜对象
    if (carrot)
    {
        carrot->removeFromParent();
        carrot->release();
        carrot = nullptr;
    }

    // 重新创建和初始化萝卜
    carrot = Carrot::create();
    carrot->setPosition(Vec2(860, 520));
    carrotHealth = 100;
    carrot->setHealth(100);
    createCarrot();
    addChild(carrot, 3);
}


/*--------------------------------------------怪物和萝卜、游戏进程方面---------------------------------------------------------------------*/


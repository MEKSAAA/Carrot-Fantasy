#include "Map1Scene.h" 
#include "SecondScene.h"
#include "WinScene1.h"
#include "Map2Scene.h" 


USING_NS_CC;

bool WinScene1::init()
{
    if (!Scene::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 添加新的背景
    auto background = Sprite::create("GameOverBackground.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);

    //  添加“游戏胜利”
    auto label = Label::createWithTTF("YOU WIN!", "fonts/Marker Felt.ttf", 60);
    label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 40));
    this->addChild(label, 1);

    //  添加“下一关”按钮
    auto retryButton = MenuItemImage::create("NextButton.png", "NextButtonSelcted.png", CC_CALLBACK_1(WinScene1::onNextButtonClicked, this));
    retryButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 75));

    //  添加“回到主菜单”按钮
    auto mainMenuButton = MenuItemImage::create("MainMenuButton.png", "MainMenuButtonSelcted.png", CC_CALLBACK_1(WinScene1::onMainMenuButtonClicked, this));
    mainMenuButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 150));

    auto menu = Menu::create(retryButton, mainMenuButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // 初始化星星和位置
    star1 = Sprite::create("star.png");
    star2 = Sprite::create("star.png");
    star3 = Sprite::create("star.png");

    starPosition = Vec2(visibleSize.width / 2 + origin.x - 70, visibleSize.height / 2 + origin.y + 140);

    star1->setPosition(starPosition);
    star2->setPosition(starPosition + Vec2(70, 0));
    star3->setPosition(starPosition + Vec2(140, 0));

    this->addChild(star1, 2);
    this->addChild(star2, 2);
    this->addChild(star3, 2);

    // 加载星星纹理
    loadStarTextures();

    // 根据萝卜生命值设置星星的可见性
    updateStarsTexture();

    return true;
}

void WinScene1::onNextButtonClicked(cocos2d::Ref* sender)
{
    Director::getInstance()->resume(); // 恢复游戏运行
    // 切换回游戏场景
    Director::getInstance()->replaceScene(Map2Scene::createScene());
    // 更新星星的可见性
    updateStarsTexture();
}

void WinScene1::onMainMenuButtonClicked(cocos2d::Ref* sender)
{
    Director::getInstance()->resume(); // 恢复游戏运行
    // 切换到主菜单场景
    Director::getInstance()->replaceScene(SecondScene::createScene());
}

void WinScene1::loadStarTextures()
{
    starTexture1 = Director::getInstance()->getTextureCache()->addImage("starno.png");
    starTexture2 = Director::getInstance()->getTextureCache()->addImage("star.png");
}

void WinScene1::updateStarsTexture()
{
    // 根据生命值设置星星可见性
    star1->setTexture(carrotHealth < 0 ? starTexture1 : starTexture2);
    star2->setTexture(carrotHealth < 50 ? starTexture1 : starTexture2);
    star3->setTexture(carrotHealth <= 100 ? starTexture1 : starTexture2);
}

WinScene1* WinScene1::create(int carrotHealth)
{
    auto scene = WinScene1::create();
    scene->setCarrotHealth(carrotHealth);  // 设置 carrotHealth
    return scene;
}

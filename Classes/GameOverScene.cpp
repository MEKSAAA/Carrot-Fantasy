#include "GameOverScene.h"
#include "Map1Scene.h" 
#include "SecondScene.h"

USING_NS_CC;

bool GameOverScene::init() {
    if (!Scene::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 添加新的背景
    auto background = Sprite::create("GameOverBackground.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);

    //  添加“游戏失败”
    auto label = Label::createWithTTF("YOU LOSE!", "fonts/Marker Felt.ttf", 60);
    label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 40));
    this->addChild(label, 1);

    //  添加“重试”按钮
    auto retryButton = MenuItemImage::create("RetryButton.png", "RetryButtonSelcted.png", CC_CALLBACK_1(GameOverScene::onRetryButtonClicked, this));
    retryButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 75));

    //  添加“回到主菜单”按钮
    auto mainMenuButton = MenuItemImage::create("MainMenuButton.png", "MainMenuButtonSelcted.png", CC_CALLBACK_1(GameOverScene::onMainMenuButtonClicked, this));
    mainMenuButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 150));

    auto menu = Menu::create(retryButton, mainMenuButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}

void GameOverScene::onRetryButtonClicked(Ref* sender) {
    Director::getInstance()->resume(); // 恢复游戏运行
    // 切换回游戏场景
    Director::getInstance()->replaceScene(Map1Scene::createScene());
}

void GameOverScene::onMainMenuButtonClicked(Ref* sender) {
    Director::getInstance()->resume(); // 恢复游戏运行
    // 切换到主菜单场景
    Director::getInstance()->replaceScene(SecondScene::createScene());
}

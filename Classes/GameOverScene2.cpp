#include "GameOverScene2.h"
#include "Map2Scene.h" 
#include "SecondScene.h"

USING_NS_CC;

bool GameOverScene2::init() {
    if (!Scene::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ����µı���
    auto background = Sprite::create("GameOverBackground.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);

    //  ��ӡ���Ϸʧ�ܡ�
    auto label = Label::createWithTTF("YOU LOSE!", "fonts/Marker Felt.ttf", 60);
    label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 40));
    this->addChild(label, 1);

    //  ��ӡ����ԡ���ť
    auto retryButton = MenuItemImage::create("RetryButton.png", "RetryButtonSelcted.png", CC_CALLBACK_1(GameOverScene2::onRetryButtonClicked, this));
    retryButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 75));

    //  ��ӡ��ص����˵�����ť
    auto mainMenuButton = MenuItemImage::create("MainMenuButton.png", "MainMenuButtonSelcted.png", CC_CALLBACK_1(GameOverScene2::onMainMenuButtonClicked, this));
    mainMenuButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 150));

    auto menu = Menu::create(retryButton, mainMenuButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}

void GameOverScene2::onRetryButtonClicked(Ref* sender) {
    Director::getInstance()->resume(); // �ָ���Ϸ����
    // �л�����Ϸ����
    Director::getInstance()->replaceScene(Map2Scene::createScene());
}

void GameOverScene2::onMainMenuButtonClicked(Ref* sender) {
    Director::getInstance()->resume(); // �ָ���Ϸ����
    // �л������˵�����
    Director::getInstance()->replaceScene(SecondScene::createScene());
}
 
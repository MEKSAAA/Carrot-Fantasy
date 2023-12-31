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

    // ����µı���
    auto background = Sprite::create("GameOverBackground.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);

    //  ��ӡ���Ϸʧ�ܡ�
    auto label = Label::createWithTTF("YOU LOSE!", "fonts/Marker Felt.ttf", 60);
    label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 40));
    this->addChild(label, 1);

    //  ��ӡ����ԡ���ť
    auto retryButton = MenuItemImage::create("RetryButton.png", "RetryButtonSelcted.png", CC_CALLBACK_1(GameOverScene::onRetryButtonClicked, this));
    retryButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 75));

    //  ��ӡ��ص����˵�����ť
    auto mainMenuButton = MenuItemImage::create("MainMenuButton.png", "MainMenuButtonSelcted.png", CC_CALLBACK_1(GameOverScene::onMainMenuButtonClicked, this));
    mainMenuButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 150));

    auto menu = Menu::create(retryButton, mainMenuButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // ��ʼ�����Ǻ�λ��
    star1 = Sprite::create("starno.png");
    star2 = Sprite::create("starno.png");
    star3 = Sprite::create("starno.png");

    starPosition = Vec2(visibleSize.width / 2 + origin.x - 70, visibleSize.height / 2 + origin.y + 140);

    star1->setPosition(starPosition);
    star2->setPosition(starPosition + Vec2(70, 0));
    star3->setPosition(starPosition + Vec2(140, 0));

    this->addChild(star1, 2);
    this->addChild(star2, 2);
    this->addChild(star3, 2);

    return true;
}

void GameOverScene::onRetryButtonClicked(Ref* sender) {
    Director::getInstance()->resume(); // �ָ���Ϸ����
    // �л�����Ϸ����
    Director::getInstance()->replaceScene(Map1Scene::createScene());
}

void GameOverScene::onMainMenuButtonClicked(Ref* sender) {
    Director::getInstance()->resume(); // �ָ���Ϸ����
    // �л������˵�����
    Director::getInstance()->replaceScene(SecondScene::createScene());
}

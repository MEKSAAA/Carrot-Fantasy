#include "SecondScene.h"
#include "WinScene2.h"
#include "Map2Scene.h" 
#include "WinScene2.h"

USING_NS_CC;

bool WinScene2::init()
{
    if (!Scene::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ����µı���
    auto background = Sprite::create("GameOverBackground.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);

    //  ��ӡ���Ϸʤ����
    auto label = Label::createWithTTF("YOU WIN!", "fonts/Marker Felt.ttf", 60);
    label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 40));
    this->addChild(label, 1);

    //  ��ӡ��ص����˵�����ť
    auto mainMenuButton = MenuItemImage::create("MainMenuButton.png", "MainMenuButtonSelcted.png", CC_CALLBACK_1(WinScene2::onMainMenuButtonClicked, this));
    mainMenuButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 75));

    auto menu = Menu::create( mainMenuButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // ��ʼ�����Ǻ�λ��
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

    // ������������
    loadStarTextures();

    // �����ܲ�����ֵ�������ǵĿɼ���
    updateStarsTexture();

    return true;
}

void WinScene2::onMainMenuButtonClicked(cocos2d::Ref* sender)
{
    Director::getInstance()->resume(); // �ָ���Ϸ����
    // �л������˵�����
    Director::getInstance()->replaceScene(SecondScene::createScene());
}

WinScene2* WinScene2::create(int carrotHealth)
{
    auto scene = WinScene2::create();
    scene->setCarrotHealth(carrotHealth);  // ���� carrotHealth
    return scene;
}

void WinScene2::loadStarTextures()
{
    starTexture1 = Director::getInstance()->getTextureCache()->addImage("starno.png");
    starTexture2 = Director::getInstance()->getTextureCache()->addImage("star.png");
}

void WinScene2::updateStarsTexture()
{
    // ��������ֵ�������ǿɼ���
    star1->setTexture(carrotHealth < 0 ? starTexture1 : starTexture2);
    star2->setTexture(carrotHealth < 50 ? starTexture1 : starTexture2);
    star3->setTexture(carrotHealth <= 100 ? starTexture1 : starTexture2);
}

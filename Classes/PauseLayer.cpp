#include "PauseLayer.h"

USING_NS_CC;

bool PauseLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // ��ʼ����־
    initFlags();

    return true;
}

void PauseLayer::showPauseMenu()
{
    // ���ñ�־
    isPausing = true;

    // ��ͣ��Ϸ
    Director::getInstance()->pause();
}

void PauseLayer::hidePauseMenu()
{
    // �Ƴ��˵�
    if (pauseMenu)
    {
        pauseMenu->removeFromParent();
        pauseMenu = nullptr;
    }

    // ���ñ�־
    isPausing = false;

    // ������Ϸ
    Director::getInstance()->resume();
}

void PauseLayer::onPauseClicked(Ref* sender)
{
    if (!isPausing)  // �����ظ����
    {
        showPauseMenu();
    }
}

void PauseLayer::onResumeClicked(Ref* sender)
{
    if (isPausing)  // �����ظ����
    {
        hidePauseMenu();
    }
}

void PauseLayer::initFlags()
{
    pauseMenu = nullptr;
    isPausing = false;
}
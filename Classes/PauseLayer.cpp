#include "PauseLayer.h"

USING_NS_CC;

bool PauseLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // 初始化标志
    initFlags();

    return true;
}

void PauseLayer::showPauseMenu()
{
    // 设置标志
    isPausing = true;

    // 暂停游戏
    Director::getInstance()->pause();
}

void PauseLayer::hidePauseMenu()
{
    // 移除菜单
    if (pauseMenu)
    {
        pauseMenu->removeFromParent();
        pauseMenu = nullptr;
    }

    // 设置标志
    isPausing = false;

    // 继续游戏
    Director::getInstance()->resume();
}

void PauseLayer::onPauseClicked(Ref* sender)
{
    if (!isPausing)  // 避免重复点击
    {
        showPauseMenu();
    }
}

void PauseLayer::onResumeClicked(Ref* sender)
{
    if (isPausing)  // 避免重复点击
    {
        hidePauseMenu();
    }
}

void PauseLayer::initFlags()
{
    pauseMenu = nullptr;
    isPausing = false;
}
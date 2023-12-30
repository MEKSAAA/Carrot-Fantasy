#pragma once
#ifndef __PAUSE_LAYER_H__
#define __PAUSE_LAYER_H__

#include "cocos2d.h"

class PauseLayer : public cocos2d::Layer
{
public:
    CREATE_FUNC(PauseLayer);
    virtual bool init();

    // 显示暂停菜单
    void showPauseMenu();

    // 隐藏暂停菜单
    void hidePauseMenu();

    // 暂停按钮回调函数
    void onPauseClicked(cocos2d::Ref* sender);

    // 继续按钮回调函数
    void onResumeClicked(cocos2d::Ref* sender);

private:
    cocos2d::Menu* pauseMenu;

    // 添加标志来避免重复点击
    bool isPausing;

    // 初始化标志
    void initFlags();
};

#endif // __PAUSE_LAYER_H__
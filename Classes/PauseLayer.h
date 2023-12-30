#pragma once
#ifndef __PAUSE_LAYER_H__
#define __PAUSE_LAYER_H__

#include "cocos2d.h"

class PauseLayer : public cocos2d::Layer
{
public:
    CREATE_FUNC(PauseLayer);
    virtual bool init();

    // ��ʾ��ͣ�˵�
    void showPauseMenu();

    // ������ͣ�˵�
    void hidePauseMenu();

    // ��ͣ��ť�ص�����
    void onPauseClicked(cocos2d::Ref* sender);

    // ������ť�ص�����
    void onResumeClicked(cocos2d::Ref* sender);

private:
    cocos2d::Menu* pauseMenu;

    // ��ӱ�־�������ظ����
    bool isPausing;

    // ��ʼ����־
    void initFlags();
};

#endif // __PAUSE_LAYER_H__
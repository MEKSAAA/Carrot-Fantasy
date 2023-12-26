#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"

class Enemy : public cocos2d::Sprite
{
public:
    // ���캯������������
    Enemy();
    virtual ~Enemy();

    // ��̬���������ڴ��� Enemy ʵ��
    static Enemy* createEnemy(const std::string& filename);

    // ���õ����ƶ���·��
    void setPath(const std::vector<cocos2d::Vec2>& path);

    // ���õ��˵��ƶ��ٶ�
    void setSpeed(float speed); 

    // ���õ��˵���ʼλ��
    void setStartPosition(const cocos2d::Vec2& position);  

    // �������˵��ƶ�
    void move();

    // �����ܵ��˺�
    void takeDamage(int damage);

    // �������Ƿ��Ѿ�������
    bool isDead() const;

private:
    // �ƶ���·��
    std::vector<cocos2d::Vec2> path_;

    // �ƶ��ٶ�
    float speed_;

    // ���˵�����ֵ
    int health_;

    //  ��ǵ����Ƿ񻹻���
    bool isAlive_;
};

#endif // __ENEMY_H__

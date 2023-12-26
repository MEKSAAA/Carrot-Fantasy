#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"

class Enemy : public cocos2d::Sprite
{
public:
    // 构造函数和析构函数
    Enemy();
    virtual ~Enemy();

    // 静态方法，用于创建 Enemy 实例
    static Enemy* createEnemy(const std::string& filename);

    // 设置敌人移动的路径
    void setPath(const std::vector<cocos2d::Vec2>& path);

    // 设置敌人的移动速度
    void setSpeed(float speed); 

    // 设置敌人的起始位置
    void setStartPosition(const cocos2d::Vec2& position);  

    // 启动敌人的移动
    void move();

    // 敌人受到伤害
    void takeDamage(int damage);

    // 检查敌人是否已经被击败
    bool isDead() const;

private:
    // 移动的路径
    std::vector<cocos2d::Vec2> path_;

    // 移动速度
    float speed_;

    // 敌人的生命值
    int health_;

    //  标记敌人是否还活着
    bool isAlive_;
};

#endif // __ENEMY_H__

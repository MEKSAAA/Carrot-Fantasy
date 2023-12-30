#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"Carrot.h"
using namespace cocos2d;

enum class EnemyType
{
    Type1,
    Type2,
    Type3,
};  //  怪物种类的枚举


class Enemy : public cocos2d::Sprite
{
public:
    // 构造函数和析构函数
    Enemy();
    virtual ~Enemy();

    // 静态方法，用于创建 Enemy 实例
    static Enemy* createEnemy(const std::string& filename);
    static Enemy* createEnemy(const std::string& filename, EnemyType type);  //  可以接受怪物种类参数

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

    //更新生命值条显示
    void updateHealthBar();

    //设置生命值的相对位置
    void setHealthBarPosition(const cocos2d::Vec2& position);

    //设置生命值
    void setHealth(int health);

    //设置抗击打水平
    void setResistanceLevel(int level);

    //敌人受到攻击
    void takeAttack(int attackDamage);

    //依据怪物种类设置怪物的属性
    void setType(EnemyType type);

    //通知怪物到达终点的事件
    void notifyReachedDestination();

    // 检查怪物是否到达终点
    bool hasReachedDestination() const;

    void setReachedDestination(bool reached);

    // 用于获取怪物移动路径
    const std::vector<cocos2d::Vec2>& getPath() const;

    void checkBiteCarrot();

private:
    // 移动的路径
    std::vector<cocos2d::Vec2> path_;

    // 移动速度
    float speed_;

    // 敌人的生命值
    int health_;

    //  标记敌人是否还活着
    bool isAlive_;

    //用于存储生命值条
    Sprite* healthBarBackground_;
    ProgressTimer* healthBarForeground_;

    // 抗打击水平
    int resistanceLevel_;

    //  怪物种类
    EnemyType type_;

    // 标记怪物是否已经到达终点
    bool reachedDestination_;

};

#endif // __ENEMY_H__

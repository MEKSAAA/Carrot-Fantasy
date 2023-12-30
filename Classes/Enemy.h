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
};  //  ���������ö��


class Enemy : public cocos2d::Sprite
{
public:
    // ���캯������������
    Enemy();
    virtual ~Enemy();

    // ��̬���������ڴ��� Enemy ʵ��
    static Enemy* createEnemy(const std::string& filename);
    static Enemy* createEnemy(const std::string& filename, EnemyType type);  //  ���Խ��ܹ����������

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

    //��������ֵ����ʾ
    void updateHealthBar();

    //��������ֵ�����λ��
    void setHealthBarPosition(const cocos2d::Vec2& position);

    //��������ֵ
    void setHealth(int health);

    //���ÿ�����ˮƽ
    void setResistanceLevel(int level);

    //�����ܵ�����
    void takeAttack(int attackDamage);

    //���ݹ����������ù��������
    void setType(EnemyType type);

    //֪ͨ���ﵽ���յ���¼�
    void notifyReachedDestination();

    // �������Ƿ񵽴��յ�
    bool hasReachedDestination() const;

    void setReachedDestination(bool reached);

    // ���ڻ�ȡ�����ƶ�·��
    const std::vector<cocos2d::Vec2>& getPath() const;

    void checkBiteCarrot();

private:
    // �ƶ���·��
    std::vector<cocos2d::Vec2> path_;

    // �ƶ��ٶ�
    float speed_;

    // ���˵�����ֵ
    int health_;

    //  ��ǵ����Ƿ񻹻���
    bool isAlive_;

    //���ڴ洢����ֵ��
    Sprite* healthBarBackground_;
    ProgressTimer* healthBarForeground_;

    // �����ˮƽ
    int resistanceLevel_;

    //  ��������
    EnemyType type_;

    // ��ǹ����Ƿ��Ѿ������յ�
    bool reachedDestination_;

};

#endif // __ENEMY_H__

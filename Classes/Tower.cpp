#include "Tower.h"
#include "Map1Scene.h"
using namespace std;

#include <Windows.h>
#include <time.h>
#include <cstdlib>
USING_NS_CC;

bool Tower::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    lv = 1;
    return true;
}

void Tower::PlaceTower(const Vec2& pos)
{
    bottom->setPosition(Vec2(pos.x + 20, pos.y + 50));
    loca = pos;
    Director::getInstance()->getRunningScene()->addChild(bottom, 4);

    oriTower->setPosition(30, 35);
    bottom->addChild(oriTower);
}

inline void CorrectDegree(const Point& normalizedVector, const float& radians, float& degree)//��������У���Ƕ�
{
    if (normalizedVector.x == 0)
        degree = (normalizedVector.y > 0 ? 90 : -90);
    else if (normalizedVector.y == 0)
        degree = (normalizedVector.x > 0 ? 0 : 180);
    else if (normalizedVector.x > 0 && normalizedVector.y > 0)
        degree = radians / M_PI * 180;
    else if (normalizedVector.x < 0 && normalizedVector.y > 0)
        degree = radians / M_PI * 180 + 180;
    else if (normalizedVector.x < 0 && normalizedVector.y < 0)
        degree = radians / M_PI * 180 - 180;
    else if(normalizedVector.x > 0 && normalizedVector.y < 0)
        degree = radians / M_PI * 180;
}

void Tower::Rotate(const Vec2& enePos)
{
    Point shootVector = enePos - Vec2(loca.x + 20, loca.y + 50);
    float distance = std::sqrt(shootVector.x * shootVector.x + shootVector.y * shootVector.y);//��з����Լ��ľ���
    if (distance > rng)//�ж��Ƿ��ڹ�����Χ��
        return;
    //������׼��������������Ϊ1
    Point normalizedVector = ccpNormalize(shootVector);
    //�����ת����
    float radians = atan(normalizedVector.y/normalizedVector.x);
    //������ת��Ϊ�Ƕ�
    float degree = 0;//��ʼ������
    CorrectDegree(normalizedVector, radians, degree);//У��
    //����������ת���ٶȣ�����Ϊ2�У�rad/s��
    float rotateSpeed = 2 * M_PI;
    //��ת1��������ʱ��Ϊ
    float rotate_1rad_time = 1 / rotateSpeed;
    //��תʱ��
    float rotateDuration = fabs(radians * rotate_1rad_time);
    //���ִ����ת
    oriTower->runAction(RotateTo::create(rotateDuration, -degree));  //��Ҫ��Ļ��ת�Ͱ�ǰ׺ȥ��
}

void Tower::Attack(Sprite* t)
{
    target = t;
    auto bullet = Sprite::create("PBottle11.png");
    bullet->setPosition(loca.x + 20, loca.y + 50);
    oriTower->addChild(bullet,4);
    //bullets.push_back(bullet);
    Shoot(bullet);
}

void Tower::Shoot(Sprite* bullet)
{
    Vec2 shootVec = target->getPosition() - bullet->getPosition();
    auto moveAction = MoveBy::create(5.0f, shootVec);
    bullet->runAction(moveAction);
}
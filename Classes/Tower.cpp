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
    lv = 1;  //初始等级

    shootInterval = 1.0f;
    damage = 25.0f;

    // 每隔一段时间发射子弹
    schedule([this](float dt) {
        //this->shoot();
        }, shootInterval, "shoot_schedule_key");
    return true;


}
//放置炮塔
void Tower::PlaceTower(const Vec2& pos)
{
    bottom->setPosition(Vec2(pos.x + 20, pos.y + 50));
    loca = pos;
    Director::getInstance()->getRunningScene()->addChild(bottom, 4);

    oriTower->setPosition(30, 35);
    bottom->addChild(oriTower);
}
//计算炮塔旋转角度
inline void CorrectDegree(const Point& normalizedVector, const float& radians, float& degree)//根据象限校正角度
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
//将炮塔旋转到正确位置
void Tower::Rotate(const Vec2& enePos)
{
    Point shootVector = enePos - Vec2(loca.x + 20, loca.y + 50);
    float distance = std::sqrt(shootVector.x * shootVector.x + shootVector.y * shootVector.y);//算敌方到自己的距离
    if (distance > rng)//判断是否在攻击范围内
        return;
    //向量标准化，即向量长度为1
    Point normalizedVector = ccpNormalize(shootVector);
    //算出旋转弧度
    float radians = atan(normalizedVector.y/normalizedVector.x);
    //将弧度转换为角度
    float degree = 0;//初始化定义
    CorrectDegree(normalizedVector, radians, degree);//校正
    //设置匀速旋转的速度，假设为2π（rad/s）
    float rotateSpeed = 2 * M_PI;
    //旋转1弧度所用时间为
    float rotate_1rad_time = 1 / rotateSpeed;
    //旋转时间
    float rotateDuration = fabs(radians * rotate_1rad_time);
    //最后执行旋转
    oriTower->runAction(RotateTo::create(rotateDuration, -degree));  //想要屏幕旋转就把前缀去掉
}

/*----------------------------------------------------待实现----------------------------------------*/
//射击函数-----暂未实现
/*void Tower::Attack(Sprite* t)
{
    target = t;
    auto bullet = Sprite::create("PBottle11.png");
    bullet->setPosition(loca.x + 20, loca.y + 50);
    oriTower->addChild(bullet,4);
    //bullets.push_back(bullet);
    Shoot(bullet);
}
//射击函数-----暂未实现
void Tower::Shoot(Sprite* bullet)
{
    Vec2 shootVec = target->getPosition() - bullet->getPosition();
    auto moveAction = MoveBy::create(5.0f, shootVec);
    bullet->runAction(moveAction);
}
/*----------------------------------------------------待实现----------------------------------------*/
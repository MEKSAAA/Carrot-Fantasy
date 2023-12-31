#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Bullet : public Node {
public:
    CREATE_FUNC(Bullet);

    virtual bool init() override {
        if (!Node::init()) {
            return false;
        }

        // 设置子弹的外观
        auto bulletSprite = Sprite::create("PBottle11.png");
        addChild(bulletSprite);

        // 设置子弹速度
        bulletSpeed = 5.0f;

        return true;
    }

    void shootToTarget(Vec2 targetPosition) {
        // 计算子弹方向和角度
        Vec2 direction = targetPosition - getPosition();
        //float angle = CC_RADIANS_TO_DEGREES(direction.getAngle());

        // 使子弹朝向目标
        //setRotation(-angle);

        // 创建子弹运动动作
        auto moveAction = MoveTo::create(direction.length() / bulletSpeed, targetPosition);
        auto removeAction = CallFunc::create([this]() {
            this->removeFromParentAndCleanup(true);
            });
        auto sequence = Sequence::create(moveAction, removeAction, nullptr);

        // 运行动作
        runAction(sequence);
    }

private:
    float bulletSpeed;
};

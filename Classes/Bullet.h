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

        // �����ӵ������
        auto bulletSprite = Sprite::create("PBottle11.png");
        addChild(bulletSprite);

        // �����ӵ��ٶ�
        bulletSpeed = 5.0f;

        return true;
    }

    void shootToTarget(Vec2 targetPosition) {
        // �����ӵ�����ͽǶ�
        Vec2 direction = targetPosition - getPosition();
        //float angle = CC_RADIANS_TO_DEGREES(direction.getAngle());

        // ʹ�ӵ�����Ŀ��
        //setRotation(-angle);

        // �����ӵ��˶�����
        auto moveAction = MoveTo::create(direction.length() / bulletSpeed, targetPosition);
        auto removeAction = CallFunc::create([this]() {
            this->removeFromParentAndCleanup(true);
            });
        auto sequence = Sequence::create(moveAction, removeAction, nullptr);

        // ���ж���
        runAction(sequence);
    }

private:
    float bulletSpeed;
};

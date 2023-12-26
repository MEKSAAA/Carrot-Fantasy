#include "Enemy.h"

USING_NS_CC;

Enemy::Enemy()
    : speed_(100.0f), health_(100),isAlive_(true)
{
}

Enemy::~Enemy()
{
}

Enemy* Enemy::createEnemy(const std::string& filename)
{
    // ʹ�� create �������� Enemy ʵ��
    auto enemy = new (std::nothrow) Enemy();
    if (enemy && enemy->initWithFile(filename))
    {
        enemy->autorelease();
        return enemy;
    }
    CC_SAFE_DELETE(enemy);
    return nullptr;
}

void Enemy::setPath(const std::vector<Vec2>& path)
{
    // ���õ��˵��ƶ�·��
    path_ = path;
}

void Enemy::setSpeed(float speed)
{
    speed_ = speed;
}

void Enemy::setStartPosition(const cocos2d::Vec2& position)
{
    setPosition(position);
}

void Enemy::move()
{
    if (isAlive_ && !path_.empty())
    {
        // ����������������λ��
        Vec2 relativePosition = path_.front() - getPosition();

        // �������λ�õľ���
        float distance = relativePosition.length();

        // �����ƶ������ʱ�䣨�����ٶ�Ϊ speed_��
        float duration = distance / speed_;

        // �����ƶ�����
        //auto moveTo = MoveTo::create(speed_, path_.front());
        auto moveBy = MoveBy::create(duration, relativePosition);
        
        // �����ص����������ƶ���ɺ���ã������ƶ���һ����
        auto callback = CallFunc::create([this]() {
            path_.erase(path_.begin());
            move();
            });
        // �������ж��������ƶ��ͻص���������ִ��
        auto sequence = Sequence::create(moveBy, callback, nullptr);
        // ִ�����ж���
        runAction(sequence);
    }
    else
    {
        // �ƶ���ɺ���ʧ
        removeFromParent();
    }
}

void Enemy::takeDamage(int damage)
{
    // �����ܵ��˺�����������ֵ
    health_ -= damage;
    // �������ֵС�ڵ��� 0���Ӹ��ڵ����Ƴ�����
    if (health_ <= 0)
    {
        removeFromParent();
    }
}

bool Enemy::isDead() const
{
    // ���ص����Ƿ��Ѿ�������
    return health_ <= 0;
}

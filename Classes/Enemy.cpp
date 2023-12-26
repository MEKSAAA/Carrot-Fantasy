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
    // 使用 create 方法创建 Enemy 实例
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
    // 设置敌人的移动路径
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
        // 计算横向和纵向的相对位置
        Vec2 relativePosition = path_.front() - getPosition();

        // 计算相对位置的距离
        float distance = relativePosition.length();

        // 计算移动所需的时间（假设速度为 speed_）
        float duration = distance / speed_;

        // 创建移动动作
        //auto moveTo = MoveTo::create(speed_, path_.front());
        auto moveBy = MoveBy::create(duration, relativePosition);
        
        // 创建回调动作，在移动完成后调用，继续移动下一个点
        auto callback = CallFunc::create([this]() {
            path_.erase(path_.begin());
            move();
            });
        // 创建序列动作，将移动和回调动作依次执行
        auto sequence = Sequence::create(moveBy, callback, nullptr);
        // 执行序列动作
        runAction(sequence);
    }
    else
    {
        // 移动完成后，消失
        removeFromParent();
    }
}

void Enemy::takeDamage(int damage)
{
    // 敌人受到伤害，减少生命值
    health_ -= damage;
    // 如果生命值小于等于 0，从父节点中移除敌人
    if (health_ <= 0)
    {
        removeFromParent();
    }
}

bool Enemy::isDead() const
{
    // 返回敌人是否已经被击败
    return health_ <= 0;
}

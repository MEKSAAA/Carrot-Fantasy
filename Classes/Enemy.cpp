//Enemy.cpp

#include "Enemy.h"

USING_NS_CC;

Enemy::Enemy()
    : speed_(100.0f), health_(100),isAlive_(true), resistanceLevel_(1),reachedDestination_(false)
{
    // 初始化生命值条的背景和前景
    healthBarBackground_ = Sprite::create("hb_bg.png");
    healthBarBackground_->setPosition(Vec2(getContentSize().width / 2, getContentSize().height/2));
    addChild(healthBarBackground_, 0);

    healthBarForeground_ = ProgressTimer::create(Sprite::create("hb_fg.png"));
    healthBarForeground_->setType(ProgressTimer::Type::BAR);
    healthBarForeground_->setMidpoint(Vec2(0, 0.5));
    healthBarForeground_->setBarChangeRate(Vec2(1, 0));
    healthBarForeground_->setPercentage(100);
    healthBarForeground_->setPosition(Vec2(getContentSize().width / 2, getContentSize().height/2));
    addChild(healthBarForeground_, 1);
}

Enemy::~Enemy()
{
}

Enemy* Enemy::createEnemy(const std::string& filename)
{
    // 使用 create 方法创建 Enemy 实例,仅用于调试
    auto enemy = new (std::nothrow) Enemy();
    if (enemy && enemy->initWithFile(filename))
    {
        enemy->autorelease();
        return enemy;
    }
    CC_SAFE_DELETE(enemy);
    return nullptr;
}

Enemy* Enemy::createEnemy(const std::string& filename, EnemyType type)
{
    auto enemy = new (std::nothrow) Enemy();
    if (enemy && enemy->initWithFile(filename))
    {
        enemy->autorelease();
        enemy->setType(type); // 设置怪物种类及对应属性
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
            updateHealthBar(); // 在移动时更新生命值条位置

            });
        // 创建序列动作，将移动和回调动作依次执行
        auto sequence = Sequence::create(moveBy, callback, nullptr);

        // 执行序列动作
        runAction(sequence);
    }
    else
    {
        if (path_.empty())
        {
            notifyReachedDestination();
        }

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
        health_ = 0;
        isAlive_ = false;

        // 创建一个 Sequence 动作，包含延迟和移除操作
        auto delay = DelayTime::create(0.2f);
        auto removeAction = CallFunc::create([this]() {
            // 从父节点中移除敌人和生命值条
            removeFromParentAndCleanup(true);
            });

        auto sequence = Sequence::create(delay, removeAction, nullptr);
        runAction(sequence);
    }
    updateHealthBar(); // 在生命值减少时更新生命值条
}

bool Enemy::isDead() const
{
    // 返回敌人是否已经被击败
    return health_ <= 0;
}

void Enemy::updateHealthBar()
{
    // 更新生命值条的百分比
    float percentage = static_cast<float>(health_) / 100.0f * 100.0f;
    healthBarForeground_->setPercentage(percentage);
}

void Enemy::setHealthBarPosition(const cocos2d::Vec2& position)
{
    // 设置生命值条的相对位置
    healthBarBackground_->setPosition(position);
    healthBarForeground_->setPosition(position);
}

void Enemy::setHealth(int health)
{
    health_ = health;
    updateHealthBar();
}

void Enemy::setResistanceLevel(int level)
{
    resistanceLevel_ = std::max(level, 1); // 确保抗打击水平不小于 1
}

void Enemy::takeAttack(int attackDamage)
{
    // 调整受到的攻击伤害，使用抗打击水平作为除数
    const int adjustedDamage = attackDamage / resistanceLevel_;
    // 处理敌人受到攻击的逻辑
    takeDamage(attackDamage);
}

void Enemy::setType(EnemyType type)
{
    type_ = type;
    // 根据怪物种类设置不同的属性，例如生命值、抗打击水平等
    std::string filename;//  根据怪物种类设置对应的图片

    switch (type)
    {
        case EnemyType::Type1:
            filename = "F11.png";
            setHealth(100);
            setResistanceLevel(1);
            // 设置其他属性...
            break;

        case EnemyType::Type2:
            filename = "F21.png";
            setHealth(100);
            setResistanceLevel(3);
            // 设置其他属性...
            break;

        case EnemyType::Type3:
            filename = "L11.png";
            setHealth(100);
            setResistanceLevel(2);
            // 设置其他属性...
            break;

        default:
            break;
    }
    // 使用选定的图片创建怪物
    initWithFile(filename);
}

void Enemy::notifyReachedDestination()
{
    // 触发怪物到达终点的事件
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("enemy_reached_destination", this);

}

bool Enemy::hasReachedDestination() const
{
    return reachedDestination_;
}

void Enemy::setReachedDestination(bool reached)
{
    reachedDestination_ = reached;
}

const std::vector<cocos2d::Vec2>& Enemy::getPath() const
{
    return path_;
}

void Enemy::checkBiteCarrot()
{
    // 获取萝卜的位置
    Vec2 carrotPosition = Director::getInstance()->getRunningScene()->getChildByName<Carrot*>("carrot")->getPosition();

    // 判断怪物是否在萝卜附近，这里使用了一个简单的距离判断
    float distanceToCarrot = getPosition().distance(carrotPosition);
    if (distanceToCarrot < 1.0f)  // 你可以根据实际情况调整距离
    {
        // 触发萝卜被咬的逻辑
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("carrot_bitten");
    }

}


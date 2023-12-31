//Enemy.cpp

#include "Enemy.h"
#include"Tower.h"
#include"Map1Scene.h"
#include"Map2Scene.h"
USING_NS_CC;

Enemy::Enemy()
    : speed_(100.0f), health_(100),isAlive_(true), resistanceLevel_(1),reachedDestination_(false)
{
    // ��ʼ������ֵ���ı�����ǰ��
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
    // ʹ�� create �������� Enemy ʵ��,�����ڵ���
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
        enemy->setType(type); // ���ù������༰��Ӧ����
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
            updateHealthBar(); // ���ƶ�ʱ��������ֵ��λ��

            });
        // �������ж��������ƶ��ͻص���������ִ��
        auto sequence = Sequence::create(moveBy, callback, nullptr);

        // ִ�����ж���
        runAction(sequence);
    }
    else
    {
        if (path_.empty())
        {
            notifyReachedDestination();
        }

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
        health_ = 0;
        isAlive_ = false;

        // ����һ�� Sequence �����������ӳٺ��Ƴ�����
        auto delay = DelayTime::create(0.2f);
        auto removeAction = CallFunc::create([this]() {
            // �Ӹ��ڵ����Ƴ����˺�����ֵ��
            removeFromParentAndCleanup(true);
            });

        auto sequence = Sequence::create(delay, removeAction, nullptr);
        runAction(sequence);
    }
    updateHealthBar(); // ������ֵ����ʱ��������ֵ��
}

bool Enemy::isDead() const
{
    // ���ص����Ƿ��Ѿ�������
    return health_ <= 0;
}

void Enemy::updateHealthBar()
{
    // ��������ֵ���İٷֱ�
    float percentage = static_cast<float>(health_) / 100.0f * 100.0f;
    healthBarForeground_->setPercentage(percentage);
}

void Enemy::setHealthBarPosition(const cocos2d::Vec2& position)
{
    // ��������ֵ�������λ��
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
    resistanceLevel_ = std::max(level, 1); // ȷ�������ˮƽ��С�� 1
}

void Enemy::takeAttack(int attackDamage)
{
    // �����ܵ��Ĺ����˺���ʹ�ÿ����ˮƽ��Ϊ����
    const int adjustedDamage = attackDamage / resistanceLevel_;
    // ��������ܵ��������߼�
    takeDamage(attackDamage);
}

void Enemy::setType(EnemyType type)
{
    type_ = type;
    // ���ݹ����������ò�ͬ�����ԣ���������ֵ�������ˮƽ��
    std::string filename;//  ���ݹ����������ö�Ӧ��ͼƬ

    switch (type)
    {
        case EnemyType::Type1:
            filename = "F11.png";
            setHealth(100);
            setResistanceLevel(1);
            // ������������...
            break;

        case EnemyType::Type2:
            filename = "F21.png";
            setHealth(100);
            setResistanceLevel(3);
            // ������������...
            break;

        case EnemyType::Type3:
            filename = "L11.png";
            setHealth(100);
            setResistanceLevel(2);
            // ������������...
            break;

        default:
            break;
    }
    // ʹ��ѡ����ͼƬ��������
    initWithFile(filename);
}

void Enemy::notifyReachedDestination()
{
    // �������ﵽ���յ���¼�
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
    // ��ȡ�ܲ���λ��
    Vec2 carrotPosition = Director::getInstance()->getRunningScene()->getChildByName<Carrot*>("carrot")->getPosition();

    // �жϹ����Ƿ����ܲ�����������ʹ����һ���򵥵ľ����ж�
    float distanceToCarrot = getPosition().distance(carrotPosition);
    if (distanceToCarrot < 1.0f)  // ����Ը���ʵ�������������
    {
        // �����ܲ���ҧ���߼�
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("carrot_bitten");
    }

}


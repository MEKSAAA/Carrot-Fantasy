#include "Tower.h"
#include "Map1Scene.h"
using namespace std;

USING_NS_CC;

bool Tower::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    return true;
}

void Tower::PlaceTower(const Vec2& pos, int type)
{
    Tower* newTower;

    switch (type) {
        case bottle:
            newTower = BottleTower::create();
            break;
        default:
            break;
    }
    
    newTower->bottom->setPosition(pos);
    Director::getInstance()->getRunningScene()->addChild(newTower->bottom, 4);
}
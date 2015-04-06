#pragma once

#include "GameMap.h"
#include "Constants.h"
#include "cocos2d.h"
using namespace cocos2d;

class Food :public CCSprite
{
public:
	Food(void);
	~Food(void);

	void setNewPosition();
	CollisionType collisionCheck(CCPoint point);
};


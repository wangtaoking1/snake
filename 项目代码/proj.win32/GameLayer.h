#pragma once
#include "cocos2d.h"
#include "GameMap.h"
#include "Global.h"
#include "Food.h"
#include "EarthSnake.h"
#include "MarsSnake.h"
using namespace cocos2d;

class GameLayer: public CCLayer
{
private:
	float earthSpeed, marsSpeed;
public:
	GameLayer(void);
	~GameLayer(void);

	virtual bool init();
	void earthStep(float dt);
	void marsStep(float dt);

	CREATE_FUNC(GameLayer);
};


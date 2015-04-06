#pragma once
#include "Constants.h"
#include "GameLayer.h"
#include "ControlLayer.h"
#include "EndLayer.h"
#include "cocos2d.h"
using namespace cocos2d;

class GameScene:public cocos2d::CCScene
{
public:
	GameScene(void);
	~GameScene(void);

	virtual bool init();
	static CCScene *playNewGame();

	CREATE_FUNC(GameScene);
};


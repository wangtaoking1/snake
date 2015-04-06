#include "GameLayer.h"


GameLayer::GameLayer(void)
{
	sGlobal->gamelayer = this;
}


GameLayer::~GameLayer(void)
{
}

bool GameLayer::init()
{
	bool bRet = false;
	do
	{
		//add map
		GameMap *map = GameMap::createNewMap("back.tmx");
		CC_BREAK_IF(! map);
		this->addChild( map, 0);
		
		//add earthsnake
		EarthSnake *earthsnake = EarthSnake::createNewSnake(this);
		CC_BREAK_IF(!earthsnake);
		sGlobal->earthsnake = earthsnake;
		this->addChild( earthsnake, 1, 100);
		
		//add marssnake
		MarsSnake *marssnake = MarsSnake::createNewSnake(this);
		CC_BREAK_IF(!marssnake);
		sGlobal->marssnake = marssnake;
		this->addChild( marssnake, 1, 101);

		//add food
		Food *food = (Food*)Food::create();
		sGlobal->food = food;
		food->setAnchorPoint(cocos2d::CCPointZero);
		this->addChild(food, 0, 50);
		food->setNewPosition();
		
		earthSpeed = 0.2f;
		marsSpeed = 0.2f;
		schedule(schedule_selector(GameLayer::earthStep), earthSpeed);
		schedule(schedule_selector(GameLayer::marsStep), marsSpeed);

		bRet = true;
	}while(0);
	return bRet;
}

void GameLayer::earthStep(float dt)
{
	CCNode *node = this->getChildByTag(100);
	((EarthSnake*)node)->moveOneStep();
}

void GameLayer::marsStep(float dt)
{
	CCNode *node = this->getChildByTag(101);
	((MarsSnake*)node)->moveOneStep();
}

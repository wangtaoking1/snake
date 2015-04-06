#pragma once

#include "Singleton.h"
#include "GameLayer.h"
#include "EndLayer.h"
#include "GameMap.h"
#include "EarthSnake.h"
#include "MarsSnake.h"
#include "Food.h"
#include "cocos2d.h"
using namespace cocos2d;

#define sGlobal Global::instance()

class GameLayer;
class EndLayer;
class GameMap;
class EarthSnake;
class MarsSnake;
class Food;

class Global :public Singleton<Global>
{
public:
	Global(void);
	~Global(void);

	GameLayer *gamelayer;
	EndLayer *endlayer;
	GameMap *gamemap;
	EarthSnake *earthsnake;
	MarsSnake *marssnake;
	Food *food;
};


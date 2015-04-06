#pragma once

#include "Constants.h"
#include "Global.h"
#include "cocos2d.h"
using namespace cocos2d;

class GameMap: public CCTMXTiledMap
{
public:
	bool grass[32][32];

	GameMap(void);
	~GameMap(void);

	static GameMap* createNewMap(const char* tmxFile);

	static CollisionType collisionCheck(CCPoint point);
	
protected:
	void extraInit();
};
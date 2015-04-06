#pragma once

#include "EndScene.h"
#include "Constants.h"
#include "cocos2d.h"
using namespace cocos2d;

class EarthSnake: public CCNode
{
public:
	CCPoint arr[100];
	CCSprite *sprite[100];
	int length;
	CCPoint head, tail, nextPosition;
	sDirection direction;
	CCLayer *parentLayer;
	bool tailFlag;
	bool canTurn;

public:
	EarthSnake(void);
	~EarthSnake(void);

	void loadImages();
	void show();
	void moveOneStep();
	void step();
	void move();
	void grow();
	void die();
	void setDirection(sDirection dir);
	CCPoint getNextPosition(sDirection dir);
	void removeItself();
	
	static EarthSnake* createNewSnake(CCLayer* parentlayer);
	bool enInit(CCLayer* parentlayer);
};


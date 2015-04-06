#pragma once

#include "EndScene.h"
#include "Constants.h"
#include "cocos2d.h"
using namespace cocos2d;

class MarsSnake :public CCNode
{
public:
	CCPoint arr[100];
	CCSprite *sprite[100];
	int length;
	CCPoint head, tail, nextPosition;
	sDirection direction;
	CCLayer *parentLayer;
	bool tailFlag;

public:
	MarsSnake(void);
	~MarsSnake(void);

	void loadImages();
	void show();

	void step();
	void move();
	void grow();
	void die();
	void setDirection(sDirection dir);
	CCPoint getNextPosition(sDirection dir);
	void removeItself();

	static MarsSnake* createNewSnake(CCLayer* parentlayer);
	bool enInit(CCLayer* parentlayer);
	
	void moveOneStep();
	void thinking();
};


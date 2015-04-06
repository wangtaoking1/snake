#include "EarthSnake.h"
#include "Global.h"
#include "GameMap.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

EarthSnake::EarthSnake(void)
{

}

EarthSnake::~EarthSnake(void)
{

}

EarthSnake* EarthSnake::createNewSnake(CCLayer* parentlayer)
{
	EarthSnake* snake = new EarthSnake();
	if( !snake )
		return NULL;
	if( snake->enInit(parentlayer) )
	{
		snake->autorelease();
		return snake;
	}
	CC_SAFE_DELETE(snake);
	return NULL;
}

bool EarthSnake::enInit(CCLayer* parentlayer)
{
	bool bRet = false;
	do
	{
		loadImages();

		parentLayer = parentlayer;
		length = 3;
		arr[0] = ccp(40, 0);
		arr[1] = ccp(20, 0);
		arr[2] = ccp(0, 0);
		head = arr[0];
		tail = arr[2];
		direction = RIGHT;
		tailFlag = false;
		canTurn = true;

		//header
		CCSprite *header = CCSprite::create();
		sprite[0] = header;
		CC_BREAK_IF(! header);
		header->setAnchorPoint(cocos2d::CCPointZero);
		header->setPosition(arr[0]);
		parentLayer->addChild(header);
		
		//body
		for( int i=1; i<length-1; i++ )
		{
			CCSprite *body = CCSprite::create();
			CC_BREAK_IF(! body);
			sprite[i] = body;
			body->setAnchorPoint(cocos2d::CCPointZero);
			body->setPosition(arr[i]);
			parentLayer->addChild(body);
		}

		//tail
		CCSprite *tailer = CCSprite::create();
		sprite[length-1] = tailer;
		CC_BREAK_IF(! tailer);
		tailer->setAnchorPoint(cocos2d::CCPointZero);
		tailer->setPosition(arr[length-1]);
		parentLayer->addChild(tailer);

		show();

		bRet = true;
	}while(0);
	return bRet;
}

void EarthSnake::moveOneStep()
{
	this->step();
}

void EarthSnake::step()
{
	nextPosition = this->getNextPosition(direction);
	CollisionType type = GameMap::collisionCheck( nextPosition);
	switch( type)
	{
	case kNONE:
		move();
		show();
		break;
	case kWALL:
		die();
		break;
	case kFOOD:
		sGlobal->food->setNewPosition();
		//SimpleAudioEngine::sharedEngine()->playEffect("sound61.mp3",false);
		tail = arr[length-1];
		move();
		grow();
		show();
		break;
	case kBODY:
		die();
		break;
	}
}

void EarthSnake::move()
{
	int i;
	for( i=length-1; i>0; i-- )
	{
		arr[i] = arr[i-1];
	}
	arr[0] = nextPosition;
	this->canTurn = true;
}

void EarthSnake::grow()
{
	this->length++;
	arr[length-1] = tail;
	sprite[length-1] = CCSprite::create();
	parentLayer->addChild(sprite[length-1]);
}

void EarthSnake::setDirection(sDirection dir)
{
	if( !this->canTurn )
		return;
	if( ((int)direction+2)%4 == (int)dir )
		return;
	this->canTurn = false;
	this->direction = dir;
}

CCPoint EarthSnake::getNextPosition(sDirection dir)
{
	CCPoint point = arr[0];
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	switch(dir)
	{
	case UP:
		point.y += 20;
		if( point.y == size.height )
			point.y = 0;
		break;
	case RIGHT:
		point.x += 20;
		if( point.x == size.width )
			point.x = 0;
		break;
	case DOWN:
		if( point.y == 0 )
			point.y = size.height;
		point.y -= 20;
		break;
	case LEFT:
		if( point.x == 0 )
			point.x = size.width;
		point.x -=20;
	}
	return point;
}

void EarthSnake::removeItself()
{
	int i=0;
	for( i=0; i<length; i++ )
		parentLayer->removeChild(sprite[i]);
	length =0;
}

void EarthSnake::die()
{
	CCDirector::sharedDirector()->pause();
	sGlobal->endlayer->setZOrder(2);
	EndLayer *Elayer = sGlobal->endlayer;
	((CCSprite*)(Elayer->getChildByTag(1)))->initWithFile("end.png");
	((CCMenu*)(Elayer->getChildByTag(0)))->setEnabled(true);
}

void EarthSnake::loadImages()
{
}

void EarthSnake::show()
{
	sprite[0]->initWithFile(Esnake[(int)direction+1]);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	for( int i=1; i<length-1; i++ )
	{
		if( arr[i-1].x ==arr[i+1].x )
			sprite[i]->initWithFile(Esnake[6]);
		else if( arr[i-1].y == arr[i+1].y )
			sprite[i]->initWithFile(Esnake[5]);
		else
		{
			int dx = arr[i-1].x - arr[i+1].x;
			int dy = arr[i-1].y - arr[i+1].y;
			if( dx == 20 - size.width )
				dx = 20;
			if( dx == size.width - 20 )
				dx = -20;
			if( dy == size.height - 20 )
				dy = -20;
			if( dy == 20 - size.height )
				dy = 20;
			if( dx == 20 && dy == 20 )
			{
				if( arr[i-1].y == arr[i].y )
					sprite[i]->initWithFile(Esnake[17]);   //up-right
				else
					sprite[i]->initWithFile(Esnake[16]);    //right-up
			}
			else if( dx == 20 && dy ==-20 )
			{
				if( arr[i-1].x == arr[i].x )
					sprite[i]->initWithFile(Esnake[15]);      //right-down
				else
					sprite[i]->initWithFile(Esnake[18]);      //down-right
			}
			else if( dx==-20 && dy==20 )
			{
				if( arr[i-1].x == arr[i].x )
					sprite[i]->initWithFile(Esnake[18]);        //left-up
				else
					sprite[i]->initWithFile(Esnake[15]);        //up-left
			}
			else
			{
				if( arr[i-1].y == arr[i].y )
					sprite[i]->initWithFile(Esnake[16]);    //down-left
				else
					sprite[i]->initWithFile(Esnake[17]);    //left-down
			}
		}
	}
	int dx = arr[length-2].x - arr[length-1].x;
	int dy = arr[length-2].y - arr[length-1].y;
	char str[15];
	int tem;
	if( dx==0  && dy == 20)
	{
		//up
		if( tailFlag )
			tem = 7;
		else
			tem = 8;
		strcpy(str, Esnake[tem]);
	}
	else if(dx == 0 && dy == -20)
	{
		//down
		if( tailFlag )
			tem = 11;
		else
			tem = 12;
		strcpy(str, Esnake[tem]);
	}
	else if( dx == 20 && dy == 0)
	{
		//right
		if( tailFlag )
			tem = 9;
		else
			tem = 10;
		strcpy(str, Esnake[tem]);
	}
	else
	{
		//left
		if( tailFlag )
			tem = 13;
		else
			tem = 14;
		strcpy(str, Esnake[tem]);
	}
	tailFlag = !tailFlag;
	sprite[length-1]->initWithFile( str );
	for( int i=0; i<length; i++ )
	{
		sprite[i]->setPosition(arr[i]);
		sprite[i]->setAnchorPoint(cocos2d::CCPointZero);
	}
}

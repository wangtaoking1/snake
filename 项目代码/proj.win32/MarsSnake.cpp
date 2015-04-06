#include "MarsSnake.h"
#include "Global.h"
#include "GameMap.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

MarsSnake::MarsSnake(void)
{
}

MarsSnake::~MarsSnake(void)
{
}

MarsSnake* MarsSnake::createNewSnake(CCLayer* parentlayer)
{
	MarsSnake* snake = new MarsSnake();
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


bool MarsSnake::enInit(CCLayer* parentlayer)
{
	bool bRet = false;
	do
	{
		parentLayer = parentlayer;
		length = 3;
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		arr[0] = ccp(size.width-60, size.height-20);
		arr[1] = ccp(size.width-40, size.height-20);
		arr[2] = ccp(size.width-20, size.height-20);
		head = arr[0];
		tail = arr[2];
		direction = LEFT;
		
		tailFlag = false;

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

void MarsSnake::moveOneStep()
{
	this->thinking();
	this->step();
}


//������˼���㷨����
void MarsSnake::thinking()
{
	CCPoint foodPoint = sGlobal->food->getPosition();
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if( foodPoint.x > arr[0].x )
	{
		if( foodPoint.x - arr[0].x < size.width/2 ) 
			direction = RIGHT;
		else
			direction = LEFT;
	}
	else if( foodPoint.x == arr[0].x )
	{
		if( foodPoint.y > arr[0].y )
		{
			if( foodPoint.y - arr[0].y < size.height/2 )
				direction = UP;
			else
				direction = DOWN;
		}
		else
		{
			if( arr[0].y - foodPoint.y < size.height/2 )
				direction = DOWN;
			else
				direction = UP;
		}
	}
	else
	{
		if( arr[0].x - foodPoint.x < size.width/2 ) 
			direction = LEFT;
		else
			direction = RIGHT;
	}
	for( int i=0; i<4; i++ )
	{
		nextPosition = this->getNextPosition(direction);
		CollisionType type = GameMap::collisionCheck( nextPosition);
		if( type == kNONE || type == kFOOD )
			break;
		if( direction == UP ) direction = RIGHT;
		else if( direction == RIGHT ) direction = DOWN;
		else if( direction == DOWN ) direction = LEFT;
		else direction = UP;
	}
}

void MarsSnake::step()
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

void MarsSnake::move()
{
	int i;
	for( i=length-1; i>0; i-- )
	{
		arr[i] = arr[i-1];
	}
	arr[0] = nextPosition;
}

void MarsSnake::grow()
{
	this->length++;
	arr[length-1] = tail;
	sprite[length-1] = CCSprite::create();
	parentLayer->addChild(sprite[length-1]);
}

void MarsSnake::setDirection(sDirection dir)
{
	if( ((int)direction+2)%4 == (int)dir )
		return;

	this->direction = dir;
}

CCPoint MarsSnake::getNextPosition(sDirection dir)
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

void MarsSnake::removeItself()
{
	int i=0;
	for( i=0; i<length; i++ )
		parentLayer->removeChild(sprite[i]);
	length =0;
}

void MarsSnake::die()
{
	CCDirector::sharedDirector()->pause();
	sGlobal->endlayer->setZOrder(2);
	EndLayer *Elayer = sGlobal->endlayer;
	((CCSprite*)(Elayer->getChildByTag(1)))->initWithFile("win.png");
	((CCMenu*)(Elayer->getChildByTag(0)))->setEnabled(true);
}

void MarsSnake::loadImages()
{
}

void MarsSnake::show()
{
	sprite[0]->initWithFile(Msnake[(int)direction+1]);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	for( int i=1; i<length-1; i++ )
	{
		if( arr[i-1].x ==arr[i+1].x )
			sprite[i]->initWithFile(Msnake[6]);
		else if( arr[i-1].y == arr[i+1].y )
			sprite[i]->initWithFile(Msnake[5]);
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
					sprite[i]->initWithFile(Msnake[17]);   //up-right
				else
					sprite[i]->initWithFile(Msnake[16]);    //right-up
			}
			else if( dx == 20 && dy ==-20 )
			{
				if( arr[i-1].x == arr[i].x )
					sprite[i]->initWithFile(Msnake[15]);      //right-down
				else
					sprite[i]->initWithFile(Msnake[18]);      //down-right
			}
			else if( dx==-20 && dy==20 )
			{
				if( arr[i-1].x == arr[i].x )
					sprite[i]->initWithFile(Msnake[18]);        //left-up
				else
					sprite[i]->initWithFile(Msnake[15]);        //up-left
			}
			else
			{
				if( arr[i-1].y == arr[i].y )
					sprite[i]->initWithFile(Msnake[16]);    //down-left
				else
					sprite[i]->initWithFile(Msnake[17]);    //left-down
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
		strcpy(str, Msnake[tem]);
	}
	else if(dx == 0 && dy == -20)
	{
		//down
		if( tailFlag )
			tem = 11;
		else
			tem = 12;
		strcpy(str, Msnake[tem]);
	}
	else if( dx == 20 && dy == 0)
	{
		//right
		if( tailFlag )
			tem = 9;
		else
			tem = 10;
		strcpy(str, Msnake[tem]);
	}
	else
	{
		//left
		if( tailFlag )
			tem = 13;
		else
			tem = 14;
		strcpy(str, Msnake[tem]);
	}
	tailFlag = !tailFlag;
	sprite[length-1]->initWithFile( str );
	for( int i=0; i<length; i++ )
	{
		sprite[i]->setPosition(arr[i]);
		sprite[i]->setAnchorPoint(cocos2d::CCPointZero);
	}
}

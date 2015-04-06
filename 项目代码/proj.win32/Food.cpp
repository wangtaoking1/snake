#include <stdlib.h>
#include <time.h>
#include "Food.h"

Food::Food(void)
{
}


Food::~Food(void)
{
}


void Food::setNewPosition()
{
	srand((int)time(0));
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	int xsize = size.width / 20;
	int ysize = size.height / 20;
	int x = rand() % xsize;
	int y = rand() % ysize;
	CCPoint point = ccp(x*20, y*20);
	while( collisionCheck(point) != kNONE )
	{
		x = rand() % xsize;
		y = rand() % ysize;
		point = ccp(x*20, y*20);
	}
	this->setPosition(point);
	int t = rand() % 5;
	this->initWithFile(food[t]);
	this->setAnchorPoint(cocos2d::CCPointZero);
}

CollisionType Food::collisionCheck(CCPoint point)
{
	if( sGlobal->gamemap->grass[(int)point.x/20][(int)point.y/20] )
		return kWALL;
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CollisionType type = kNONE;

	CCPoint *pp = sGlobal->earthsnake->arr;
	int i, l = sGlobal->earthsnake->length;
	for( i=0; i < l; i++ )
	{
		if( pp[i].equals(point) )
			break;
	}
	if(i != l)
	{
		type = kBODY;
		return type;
	}
	pp = sGlobal->marssnake->arr;
	l = sGlobal->marssnake->length;
	for( i=0; i<l; i++ )
	{
		if( pp[i].equals(point) )
			break;
	}
	if(i != l)
	{
		type = kBODY;
		return type;
	}
	return type;
}
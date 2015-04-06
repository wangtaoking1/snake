#include "GameMap.h"


GameMap::GameMap(void)
{
	sGlobal->gamemap = this;
}


GameMap::~GameMap(void)
{
}


GameMap* GameMap::createNewMap(const char* tmxFile)
{
	GameMap *pRet = new GameMap();
	if( pRet->initWithTMXFile(tmxFile) )
	{
		pRet->extraInit();
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_RELEASE(pRet);
	return NULL;
}

void GameMap::extraInit()
{
	memset(grass, 0, sizeof(grass));
	for( int i=5; i<9; i++ )
		grass[3][i] = 1;
	for(int i=0; i<5; i++ )
		grass[13][i] = 1;
	for( int i=20; i<25; i++ )
		grass[i][7] = 1;
	for( int i=12; i<=20; i++ )
		grass[19][i] = 1;
	for( int i=5; i<=11; i++ )
		grass[i][14] = 1;
	for( int i=13; i<19; i++ )
		grass[27][i] = 1;
	for( int i=19; i<27; i++ )
		grass[9][i] = 1;
	for( int i=15; i<24; i++ )
		grass[i][27] = 1;
}

CollisionType GameMap::collisionCheck(CCPoint point)
{
	if( sGlobal->gamemap->grass[(int)point.x/20][(int)point.y/20] )
		return kWALL;
	CollisionType type = kNONE;
	CCPoint p = sGlobal->food->getPosition();
	if( p.equals(point) )
	{
		type = kFOOD;
		return type;
	}
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if( point.x<0 || point.x>=size.width || point.y<0 || point.y>=size.height )
	{
		type = kWALL;
		return type;
	}
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
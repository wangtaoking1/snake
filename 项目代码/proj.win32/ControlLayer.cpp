#include "ControlLayer.h"
#include <cmath>

ControlLayer::ControlLayer(void)
{
}

ControlLayer::~ControlLayer(void)
{
}

void ControlLayer::onEnter()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCLayer::onEnter();
}

bool ControlLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{   
	m_tBeginPos = touch->getLocation();  
	return true;
}

void ControlLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
}

void ControlLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCPoint touchPoint = touch->getLocation();
	CCPoint curPos = m_tBeginPos;
	double x = touchPoint.x - curPos.x;
	double y = touchPoint.y - curPos.y;
	//CCLog("%lf %lf", curPos.x, curPos.y);
	if( fabs(y) > fabs(x) )
	{
		if( y > 0 )
		{
			sGlobal->earthsnake->setDirection(UP);
		}
		else
		{
			sGlobal->earthsnake->setDirection(DOWN);
		}
	}
	else
	{
		if( x > 0 )
		{
			sGlobal->earthsnake->setDirection(RIGHT);
		}
		else
		{
			sGlobal->earthsnake->setDirection(LEFT);
		}
	}
}



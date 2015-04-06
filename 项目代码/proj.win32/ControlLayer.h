#pragma once

#include "Constants.h"
#include "cocos2d.h"
#include "Global.h"
using namespace cocos2d;

class ControlLayer :public CCLayer
{
public:
	ControlLayer(void);
	~ControlLayer(void);

	virtual void onEnter();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

	CREATE_FUNC(ControlLayer);
private:
    CCPoint m_tBeginPos;
};


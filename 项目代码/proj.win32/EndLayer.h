#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class EndLayer: public CCLayer
{
public:
	EndLayer(void);
	~EndLayer(void);

	virtual bool init();
	void menuCallBack(CCObject* pSender);
	CREATE_FUNC(EndLayer);
};


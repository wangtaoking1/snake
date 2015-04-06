#pragma once

#include "GameScene.h"
#include "cocos2d.h"
using namespace cocos2d;

class IntroScene :public CCScene
{
public:
	IntroScene(void);
	~IntroScene(void);

	virtual bool init();
	static CCScene* getIntroScene();

	void menuCallBack(CCObject* pSender);

	CREATE_FUNC(IntroScene);
};


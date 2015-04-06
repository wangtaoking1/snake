#pragma once

#include "GameScene.h"
#include "cocos2d.h"
using namespace cocos2d;

class EndScene :public CCScene
{
public:
	EndScene(void);
	~EndScene(void);

	virtual bool init();
	static CCScene* getIntroScene();

	void menuCallBack(CCObject* pSender);
	void setText(char* text);

	CREATE_FUNC(EndScene);
};


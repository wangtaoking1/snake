#include "EndScene.h"


EndScene::EndScene(void)
{
}


EndScene::~EndScene(void)
{
}

CCScene* EndScene::getIntroScene()
{
	CCScene *scene = NULL;
	do
	{
		scene = EndScene::create();
		CC_BREAK_IF(! scene);
	}while(0);
	return scene;
}

bool EndScene::init()
{
	bool bRet = false;
	do
	{
		CCMenuItemFont *start = CCMenuItemFont::create("Try Again", this, menu_selector(EndScene::menuCallBack));
		start->setTag(0);
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		start->setPosition(ccp(size.width/2, 150));
		CCMenuItemFont *exit = CCMenuItemFont::create("Exit", this, menu_selector(EndScene::menuCallBack));
		exit->setTag(1);
		exit->setPosition(ccp(size.width/2, 100));
		CCMenu *menu = CCMenu::create(start, exit, NULL);
		this->addChild(menu);
		menu->setPosition(cocos2d::CCPointZero);


		cocos2d::CCLabelTTF *label = CCLabelTTF::create();
		label->setString("You Win!!");
		label->setFontSize(35);
		this->addChild(label, 1, 1);
		label->setPosition(ccp(size.width/2, 300));
		bRet = true;
	}while(0);
	return bRet;
}


void EndScene::menuCallBack(CCObject* pSender)
{
	CCNode *node = (CCNode*)pSender;
	if( node->getTag() ==0 )
	{
		CCScene *scene = GameScene::playNewGame();
		CCDirector::sharedDirector()->replaceScene(scene);
	}
	else
	{
		CCDirector::sharedDirector()->end();
	}
}

void EndScene::setText(char* text)
{
	CCLabelTTF *label = (CCLabelTTF*)this->getChildByTag(1);
	label->setString(text);
}
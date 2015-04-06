#include "EndLayer.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
EndLayer::EndLayer(void)
{
}


EndLayer::~EndLayer(void)
{
}

bool EndLayer::init()
{
	bool bRet = false;
	do
	{
		sGlobal->endlayer = this;
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		CCMenuItemImage *start = CCMenuItemImage::create("retry.png", "retry.png",this, 
			menu_selector(EndLayer::menuCallBack));
		start->setTag(0);
		start->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + 20 + origin.y));

		CCMenuItemImage *exit = CCMenuItemImage::create("quit.png", "quit.png", this, 
			menu_selector(EndLayer::menuCallBack));
		exit->setTag(1);
		exit->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 - 60 + origin.y));

		CCMenu *menu = CCMenu::create(start,exit, NULL);
		this->addChild(menu, 1, 0);
		menu->setEnabled(false);
		menu->setPosition(cocos2d::CCPointZero);


		CCPoint point = ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);

		CCSprite* pSprite0 = CCSprite::create("end.png");
		CC_BREAK_IF(! pSprite0);
		pSprite0 -> setTag(2);
		pSprite0->setPosition(point);
		this->addChild(pSprite0, 0, 1);

		bRet = true;
	}while(0);
	return bRet;	
}

void EndLayer::menuCallBack(CCObject* pSender)
{
	CCNode *node = (CCNode*)pSender;
	if( node->getTag() ==0 )
	{
		CCScene *scene = GameScene::playNewGame();
		CCDirector::sharedDirector()->replaceScene(scene);
		CCDirector::sharedDirector()->resume();
		EndLayer *Elayer = sGlobal->endlayer;
		((CCMenu*)(Elayer->getChildByTag(0)))->setEnabled(false);
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		CCDirector::sharedDirector()->end();
	}
}

#include "IntroScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#define MUSIC_FILE "sound58.mp3"

IntroScene::IntroScene(void)
{
}


IntroScene::~IntroScene(void)
{
}


CCScene* IntroScene::getIntroScene()
{
	CCScene *scene = NULL;
	do
	{
		scene = IntroScene::create();
		CC_BREAK_IF(! scene);
	}while(0);
	return scene;
}

bool IntroScene::init()
{
	bool bRet = false;
	do
	{
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		//set background image
		CCSprite* pSprite = CCSprite::create("Hello.jpg");
		pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
		this->addChild(pSprite, 0);

		CCMenuItemImage *start = CCMenuItemImage::create("play.png", "play.png", this, 
			menu_selector(IntroScene::menuCallBack));
		start->setTag(0);
		start->setPosition(ccp(120 + origin.x, 180 + origin.y));

		CCMenuItemImage *exit = CCMenuItemImage::create("quit.png", "quit.png", this, 
			menu_selector(IntroScene::menuCallBack));
		exit->setTag(1);
		exit->setPosition(ccp(120 + origin.x, 100 + origin.y));

		CCMenu *menu = CCMenu::create(start, exit, NULL);
		this->addChild(menu, 1);
		menu->setPosition(cocos2d::CCPointZero);

		//SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic( MUSIC_FILE );
		//SimpleAudioEngine::sharedEngine()->preloadEffect( "sound61.mp3" );
		//SimpleAudioEngine::sharedEngine()->playBackgroundMusic( MUSIC_FILE, true);

		bRet = true;
	}while(0);
	return bRet;
}

void IntroScene::menuCallBack(CCObject* pSender)
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
	//SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

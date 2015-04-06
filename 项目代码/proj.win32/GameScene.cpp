#include "GameScene.h"
#include "SimpleAudioEngine.h"

#define MUSIC_FILE1 "sound59.mp3"

GameScene::GameScene(void)
{
}


GameScene::~GameScene(void)
{
}

bool GameScene::init()
{
	bool bRet = false;
	do
	{
		GameLayer *gamelayer = GameLayer::create();
		CC_BREAK_IF(! gamelayer);
		this->addChild(gamelayer, KGameLayer, KGameLayer);

		ControlLayer *controllayer = ControlLayer::create();
		CC_BREAK_IF(! controllayer);
		this->addChild(controllayer, KControlLayer, KControlLayer);

		EndLayer *endLayer = EndLayer::create();
		CC_BREAK_IF(! endLayer);
		this->addChild(endLayer, KEndLayer, KEndLayer);
		
		bRet = true;
	}while(0);
	return bRet;
}

CCScene* GameScene::playNewGame()
{
	GameScene* scene = NULL;
	do
	{
		scene = GameScene::create();
		CC_BREAK_IF(! scene);
	}while(0);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MUSIC_FILE1);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSIC_FILE1, true);
	return scene;
}

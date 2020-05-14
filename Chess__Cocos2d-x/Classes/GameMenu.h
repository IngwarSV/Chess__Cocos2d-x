#pragma once

#include "cocos2d.h"
#include "audio/include/AudioEngine.h"
//#include "audio/include/SimpleAudioEngine.h"

#include "Core.h"
#include "NewGameScene.h"
#include "GameSettingsMenu.h"
#include "CustomGameScene.h"



class GameMenu : public cocos2d::Layer
{
private:
	Core* _core = Core::sharedCore();
	int _layerMusicID = 0;
public:
	static cocos2d::Scene* createScene();

	void update(float deltaTime);

	virtual bool init();

	////New Game Click Handler
	void onNewGamePvPlClick(cocos2d::Ref* sender);

	void onNewGamePvPCClick(cocos2d::Ref* sender);

	void onCustomGameClick(cocos2d::Ref* sender);
	
	void onLoadGameClick(cocos2d::Ref* sender);

	void onGameSettingsClick(cocos2d::Ref* sender);

	void onQuitGameClick(cocos2d::Ref* sender);


	// implement the "static create()" method manually
	CREATE_FUNC(GameMenu);

};

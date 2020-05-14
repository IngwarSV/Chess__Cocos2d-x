#pragma once

#include "cocos2d.h"
#include "audio/include/AudioEngine.h"

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

	//New Game (Player vs Player)
	void onNewGamePvPlClick(cocos2d::Ref* sender);
	//New Game (Player vs PC, NOT IMPLEMENTED)
	void onNewGamePvPCClick(cocos2d::Ref* sender);
	//Custom mode - deploy your troops manually and play
	void onCustomGameClick(cocos2d::Ref* sender);
	//Load Game
	void onLoadGameClick(cocos2d::Ref* sender);
	//Music and sounds volume
	void onGameSettingsClick(cocos2d::Ref* sender);
	// Quit app
	void onQuitGameClick(cocos2d::Ref* sender);

	CREATE_FUNC(GameMenu);
};

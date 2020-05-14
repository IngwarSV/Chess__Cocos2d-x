#pragma once


#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"
#include <filesystem>

#include "Core.h"
#include "LoadGameScene.h"
#include "GameSettingsMenu.h"
#include "QuitGameScene.h"

class CustomGameScene : public cocos2d::Layer {
private:
	Core* _core = Core::sharedCore();
	Color _activeSide = Color::NONE;
	int _layerMusicID = 0;
	cocos2d::Label* _logMessageLabel;


	//// PULL_BOARD 4 x 3
	cocos2d::Vector<Figure*> _pullBoard;

	// Figure to deploy
	Figure* _pullBoardFigure = nullptr;
	Figure* _existingBoardFigure = nullptr;
	// Their majesty The Kings
	Figure* _WKing = nullptr;
	Figure* _BKing = nullptr;

	cocos2d::Sprite* _whiteKingIcon = nullptr;
	cocos2d::Sprite* _blackKingIcon = nullptr;



	
	
	

	void deleteCustomData();

	std::string createFigureDataString(Figure* figureToDeploy, Location boardLocation);

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(CustomGameScene);

	void update(float deltaTime);

	void processEvent(cocos2d::Vec2 location);

	void onMouseDown(cocos2d::Event* event);

	void onPullDeskMouseDown(cocos2d::Event* event);

	void onPlayGameClick(cocos2d::Ref* sender);

	void onClearDataClick(cocos2d::Ref* sender);

	void onGameSettingsClick(cocos2d::Ref* sender);

	void onQuitGameClick(cocos2d::Ref* sender);


};

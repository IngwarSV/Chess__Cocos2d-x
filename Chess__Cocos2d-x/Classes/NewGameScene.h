#pragma once


#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"
#include <filesystem>

#include "Core.h"
#include "SaveGameScene.h"
#include "LoadGameScene.h"
#include "GameSettingsMenu.h"
#include "QuitGameScene.h"

class NewGameScene : public cocos2d::Layer {
private:
// attributes
	Core* _core = Core::sharedCore();
	int _layerMusicID = 0;
	cocos2d::Label* _logMessageLabel;
	cocos2d::Label* _p1Timer;
	cocos2d::Label* _p2Timer;
	cocos2d::Sprite* _whiteKingIcon = nullptr;
	cocos2d::Sprite* _blackKingIcon = nullptr;
	cocos2d::ui::ScrollView* _scrollView = nullptr;
	cocos2d::Vector<cocos2d::ui::Text*> _playersMoves = cocos2d::Vector<cocos2d::ui::Text*>(50);
// methods
	void setActiveIcon();
	void updateTimers();
	void updateMovesLog(std::string lastMove);

public:
// methods
	static cocos2d::Scene* createScene();

	virtual bool init() override;

	CREATE_FUNC(NewGameScene);

	void update(float deltaTime);

	void processEvent(cocos2d::Vec2 location);

	void onMouseDown(cocos2d::Event* event);

	void onSaveGameClick(cocos2d::Ref* sender);

	void onLoadGameClick(cocos2d::Ref* sender);

	void onGameSettingsClick(cocos2d::Ref* sender);

	void onQuitGameClick(cocos2d::Ref* sender);
};

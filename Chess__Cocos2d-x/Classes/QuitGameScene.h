#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"

#include "Core.h"
#include "NewGameScene.h"
#include "Specification.h"


class QuitGameScene : public cocos2d::Layer {
private:
	Core* _core = Core::sharedCore();
	int _layerMusicID = 0;
	
public:
	static cocos2d::Scene* createScene();

	virtual bool init() override;

	CREATE_FUNC(QuitGameScene);
};

#include "CustomGameScene.h"

//#define PERFORM_TESTS 1

using namespace cocos2d;
using namespace cocos2d::experimental;
namespace fs = std::filesystem;
using namespace DEF_SETT;


std::string CustomGameScene::createFigureDataString(Figure* figureToDeploy, Location boardLocation)
{
	std::string col_type_loc = figureToDeploy->getFigureName();

	col_type_loc += static_cast<char>(boardLocation.y) + 'A';
	col_type_loc += std::to_string(boardLocation.x + 1);
	col_type_loc += '1';

	return col_type_loc;
}

cocos2d::Scene* CustomGameScene::createScene() {
	cocos2d::Scene* scene = cocos2d::Scene::create();
	auto layer = CustomGameScene::create();
	scene->addChild(layer);

	return scene;
}

bool CustomGameScene::init() {
	if (!Layer::init())
	{
		return false;
	}

	// Clearing coreData for new customData
	_core->clearData();

	// Getting windows size
	auto winSize = Director::getInstance()->getWinSize();

	// Setting background with desk (desk corner 73,104)
	auto background = cocos2d::Sprite::create("CustomGameLayer.png");
	background->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	this->addChild(background, 0);

	// Setting desk for figures' pull 
	auto pullDesk = cocos2d::Sprite::create("CustomLittleDesk.png");
	pullDesk->setPosition(PULL_DESK_POS);
	pullDesk->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	this->addChild(pullDesk, 1);


	auto whiteQueen = F_Queen::createFigure(Color::WHITE, WQ_INIT_POS);
	auto blackQueen = F_Queen::createFigure(Color::BLACK, BQ_INIT_POS);
	
	_pullBoard.pushBack(F_Pawn::createFigure(Color::WHITE, WP_INIT_POS1));
	_pullBoard.pushBack(whiteQueen);
	_pullBoard.pushBack(F_Pawn::createFigure(Color::BLACK, BP_INIT_POS1));
	_pullBoard.pushBack(F_Knight::createFigure(Color::WHITE, WN_INIT_POS1));
	_pullBoard.pushBack(whiteQueen);
	_pullBoard.pushBack(F_Knight::createFigure(Color::BLACK, BN_INIT_POS1));
	_pullBoard.pushBack(F_Bishop::createFigure(Color::WHITE, WB_INIT_POS1));
	_pullBoard.pushBack(blackQueen);
	_pullBoard.pushBack(F_Bishop::createFigure(Color::BLACK, BB_INIT_POS1));
	_pullBoard.pushBack(F_Rook::createFigure(Color::WHITE, WR_INIT_POS1));
	_pullBoard.pushBack(blackQueen);
	_pullBoard.pushBack(F_Rook::createFigure(Color::BLACK, BR_INIT_POS1));

	int counter = 0;
	for (auto figure : _pullBoard) {
		if (counter == 4 || counter == 10) {
			counter += 1;
			continue;
		}
		figure->setPosition(static_cast<float>(CUS_BOARD_X + counter % CUS_BOARD_COL_SIZE * SQUARE_SIZE),
			static_cast<float>(CUS_BOARD_Y + counter / CUS_BOARD_COL_SIZE * SQUARE_SIZE));
		pullDesk->addChild(figure, CUS_BOARD_ROW_SIZE - counter / CUS_BOARD_COL_SIZE);
		counter += 1;
	}
	
	////Handle Touch Events
	auto pullDeskListener = EventListenerMouse::create();
	pullDeskListener->onMouseDown = CC_CALLBACK_1(CustomGameScene::onPullDeskMouseDown, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(pullDeskListener, pullDesk);
	
	// Deploying kings on the board
	_core->parseFigureDataString(WK_STRING);
	_WKing = _core->getFigureOnBoard(WK_INIT_POS);
	this->addChild(_WKing, BOARD_SIZE - _WKing->getLocation().x);

	_core->parseFigureDataString(BK_STRING);
	_BKing = _core->getFigureOnBoard(BK_INIT_POS);
	this->addChild(_BKing, BOARD_SIZE - _BKing->getLocation().x);
	
	//Creating button sprites for menu
	auto PlayGameButton1 = cocos2d::Sprite::createWithSpriteFrameName("PlayIcon1.png");
	auto PlayGameButton2 = cocos2d::Sprite::createWithSpriteFrameName("PlayIcon2.png");
	auto ClearDataButton1 = cocos2d::Sprite::createWithSpriteFrameName("ClearDataIcon1.png");
	auto ClearDataButton2 = cocos2d::Sprite::createWithSpriteFrameName("ClearDataIcon2.png");
	auto GameSettingsButton1 = cocos2d::Sprite::createWithSpriteFrameName("SettingsIcon.png");
	auto GameSettingsButton2 = cocos2d::Sprite::createWithSpriteFrameName("SettingsIcon2.png");
	auto QuitGameButton1 = cocos2d::Sprite::createWithSpriteFrameName("QuitIcon.png");
	auto QuitGameButton2 = cocos2d::Sprite::createWithSpriteFrameName("QuitIcon2.png");

	//Creating MenuItem for SaveGame button
	MenuItemSprite* PlayGame = MenuItemSprite::create(PlayGameButton1, PlayGameButton2, CC_CALLBACK_1(CustomGameScene::onPlayGameClick, this));
	PlayGame->setScale(0.8f);
	PlayGame->setPosition(SAVE_GAME_BUT);
	//Creating MenuItem for LoadGame button
	MenuItemSprite* LoadGame = MenuItemSprite::create(ClearDataButton1, ClearDataButton2, CC_CALLBACK_1(CustomGameScene::onClearDataClick, this));
	LoadGame->setScale(0.8f);
	LoadGame->setPosition(LOAD_GAME_BUT);
	//Creating MenuItem for GameSettings button
	MenuItemSprite* GameSettings = MenuItemSprite::create(GameSettingsButton1, GameSettingsButton2, CC_CALLBACK_1(CustomGameScene::onGameSettingsClick, this));
	GameSettings->setScale(0.8f);
	GameSettings->setPosition(GAME_SETT_BUT);
	//Creating MenuItem for QuitGame button
	MenuItemSprite* QuitGame = MenuItemSprite::create(QuitGameButton1, QuitGameButton2, CC_CALLBACK_1(CustomGameScene::onQuitGameClick, this));
	QuitGame->setScale(0.8f);
	QuitGame->setPosition(QUIT_BUT);

	auto menu = Menu::create(PlayGame, LoadGame, GameSettings, QuitGame, nullptr);
	this->addChild(menu);

	//Adding logMessages label
	_logMessageLabel = Label::createWithTTF(CustomModeString, FONT, LABEL_DISTANCE);
	_logMessageLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
	_logMessageLabel->setColor(METALLIC_GOLD);
	_logMessageLabel->setPosition(LOG_MESS_POS);
	this->addChild(_logMessageLabel, 100);

	//Adding ActiveSide sprites
	_whiteKingIcon = Sprite::createWithSpriteFrameName(WK_PAS_ICON);
	_whiteKingIcon->setPosition(WHITE_SIDE_POS);
	this->addChild(_whiteKingIcon, 100);

	_blackKingIcon = Sprite::createWithSpriteFrameName(BK_PAS_ICON);
	_blackKingIcon->setPosition(BLACK_SIDE_POS);
	this->addChild(_blackKingIcon, 100);

	auto WKListener = EventListenerMouse::create();
	WKListener->onMouseDown = [&](Event* event) {
		EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
		auto bounds = mouseEvent->getCurrentTarget()->getBoundingBox();

		if (bounds.containsPoint(mouseEvent->getLocationInView())) {
			_blackKingIcon->setSpriteFrame(BK_PAS_ICON);
			_whiteKingIcon->setSpriteFrame(WK_ACT_ICON);
			_activeSide = Color::WHITE;
		}
	};
	_whiteKingIcon->getEventDispatcher()->addEventListenerWithSceneGraphPriority(WKListener, _whiteKingIcon);

	auto BKListener = EventListenerMouse::create();
	BKListener->onMouseDown = [&](Event* event) {
		EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
		auto bounds = mouseEvent->getCurrentTarget()->getBoundingBox();

		if (bounds.containsPoint(mouseEvent->getLocationInView())) {
			_whiteKingIcon->setSpriteFrame(WK_PAS_ICON);
			_blackKingIcon->setSpriteFrame(BK_ACT_ICON);
			_activeSide = Color::BLACK;
		}
	};
	_blackKingIcon->getEventDispatcher()->addEventListenerWithSceneGraphPriority(BKListener, _blackKingIcon);
	

	//Handle Touch Events
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(CustomGameScene::onMouseDown, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// Play BackgroundMusic
	_layerMusicID = AudioEngine::play2d(CUSTOM_MUSIC, true, _core->getMusicVolume());

	// Launching update method every frame
	scheduleUpdate();

	return true;
}

void CustomGameScene::update(float deltaTime) {
	if (AudioEngine::getState(_layerMusicID) != AudioEngine::AudioState::PLAYING) {
		_layerMusicID = AudioEngine::play2d(CUSTOM_MUSIC, true, _core->getMusicVolume());
	}
}

void CustomGameScene::processEvent(cocos2d::Vec2 location)
{
	Location boardLocation;

	float floatX = (location.y - BOARD_Y) / SQUARE_SIZE;
	float floatY = (location.x - BOARD_X) / SQUARE_SIZE;

	if (floatX < 0 || floatX >= BOARD_SIZE || 
		floatY < 0 || floatY >= BOARD_SIZE) {
		if (_pullBoardFigure) {
			_pullBoardFigure->setPassiveState();
			_pullBoardFigure = nullptr;
		}
		
		if (_existingBoardFigure) {
			if (_existingBoardFigure == _WKing || _existingBoardFigure == _BKing) {
				_existingBoardFigure->setPassiveState();
				_existingBoardFigure = nullptr;

				_logMessageLabel->setString(SaveTheKingString);
				return;
			}
			_core->deletingFigure(_existingBoardFigure);
			_existingBoardFigure = nullptr;
		}
		_logMessageLabel->setString(CustomModeString);

		return;
	}

	boardLocation.x = static_cast<int>(floatX);
	boardLocation.y = static_cast<int>(floatY);

	Figure* squareToDeploy = _core->getFigureOnBoard(boardLocation);

	if (_pullBoardFigure) {
		if (_existingBoardFigure) {
			_existingBoardFigure->setPassiveState();
			_existingBoardFigure = nullptr;
		}
		if (squareToDeploy) {
			if (squareToDeploy == _WKing || squareToDeploy == _BKing) {
				_pullBoardFigure->setPassiveState();
				_pullBoardFigure = nullptr;
				_logMessageLabel->setString(SaveTheKingString);
				return;
			}
			_core->deletingFigure(squareToDeploy);
		}
		_core->parseFigureDataString(createFigureDataString(_pullBoardFigure, boardLocation));
		auto figure = _core->getFigureOnBoard(boardLocation);
		this->addChild(figure, BOARD_SIZE - figure->getLocation().x);
		AudioEngine::play2d(CLICK_SOUND_SAMPLE, false, _core->getSoundsVolume());

		return;
	}

	if (_existingBoardFigure) {
		if (_existingBoardFigure->getLocation() == boardLocation) {
			_existingBoardFigure->setPassiveState();
			_existingBoardFigure = nullptr;
			_logMessageLabel->setString(CustomModeString);
			return;
		}
		if (squareToDeploy) {
			if (squareToDeploy == _WKing || squareToDeploy == _BKing) {
				_existingBoardFigure->setPassiveState();
				_existingBoardFigure = nullptr;
				_logMessageLabel->setString(SaveTheKingString);

				return;
			}
			_core->deletingFigure(squareToDeploy);
		}
		_core->makeMove(_existingBoardFigure, _existingBoardFigure->getLocation(), boardLocation);
		_existingBoardFigure = nullptr;

		_logMessageLabel->setString(CustomModeString);

		return;
	}

	if (!_existingBoardFigure && squareToDeploy) {
		_existingBoardFigure = squareToDeploy;
		_existingBoardFigure->setActiveState();

		_logMessageLabel->setString(CustomModeString);

		return;
	}

	_logMessageLabel->setString(CustomModeString);
}

void CustomGameScene::onMouseDown(Event* event)
{
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

	processEvent(mouseEvent->getLocationInView());
}

void CustomGameScene::onPullDeskMouseDown(cocos2d::Event* event)
{
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

	if (mouseEvent->getCurrentTarget()->getBoundingBox().containsPoint(mouseEvent->getLocationInView())) {
		if (_pullBoardFigure) {
			_pullBoardFigure->setPassiveState();
			_pullBoardFigure = nullptr;
		}

		if (_existingBoardFigure) {
			_existingBoardFigure->setPassiveState();
			_existingBoardFigure = nullptr;
		}

		Vec2 location = mouseEvent->getCurrentTarget()->convertToNodeSpace(mouseEvent->getLocationInView());

		Location boardLocation;

		float floatX = (location.y - CUS_BOARD_Y) / SQUARE_SIZE;
		if (floatX < 0 || floatX >= CUS_BOARD_ROW_SIZE) {
			_logMessageLabel->setString(CustomModeString);
			return;
		}

		float floatY = (location.x - CUS_BOARD_X) / SQUARE_SIZE;
		if (floatY < 0 || floatY >= CUS_BOARD_COL_SIZE) {
			_logMessageLabel->setString(CustomModeString);
			return;
		}
		int index = static_cast<int>(floatX) * CUS_BOARD_COL_SIZE + static_cast<int>(floatY);

		_pullBoardFigure = _pullBoard.at(index);
		_pullBoardFigure->setActiveState();

		_logMessageLabel->setString(ChooseSquareString);
		event->stopPropagation();
	}
}

void CustomGameScene::onPlayGameClick(cocos2d::Ref* sender)
{
	AudioEngine::play2d(CLICK_SOUND_SAMPLE, false, _core->getSoundsVolume());
	if (_activeSide == Color::NONE) {
		_logMessageLabel->setString(ChooseSideToMoveString);
		return;
	}

	std::string gameDataString = std::to_string((_activeSide == Color::WHITE) ? 1 : 0) + " 0 0 8 8 8 8";

	std::string wArmyDataString{};
	// saving figures in std::string e.g. "WKA21" - white king, location A2, first move - true;
	for (auto figure : *(_core->getWhiteArmy())) {
		Location location = figure->getLocation();
		int xCoord = location.x + 1;
		char yCoord = static_cast<char>(location.y) + 'A';

		wArmyDataString += figure->getFigureName();
		wArmyDataString += yCoord + std::to_string(xCoord) + std::to_string(figure->_firstMove) + " ";
	}
	wArmyDataString += "\n";

	std::string bArmyDataString{};
	// saving figures in std::string e.g. "WKA21" - white king, location A2, first move - true;
	for (auto figure : *(_core->getBlackArmy())) {
		Location location = figure->getLocation();
		int xCoord = location.x + 1;
		char yCoord = static_cast<char>(location.y) + 'A';

		bArmyDataString += figure->getFigureName();
		bArmyDataString += yCoord + std::to_string(xCoord) + std::to_string(figure->_firstMove) + " ";
	}
	bArmyDataString += "\n";
	
	_core->loadData(gameDataString, wArmyDataString, bArmyDataString, CustomGameLoadedString);
	this->pause();
	AudioEngine::stop(_layerMusicID);
	Director::getInstance()->popToRootScene();
	Director::getInstance()->pushScene(TransitionCrossFade::create(1.0, NewGameScene::createScene()));

}

void CustomGameScene::onClearDataClick(cocos2d::Ref* sender)
{
	// ClearingcustomData
	_pullBoardFigure = nullptr;
	_existingBoardFigure = nullptr;
	_WKing = nullptr;
	_BKing = nullptr;
	_activeSide = Color::NONE;
	_blackKingIcon->setSpriteFrame(BK_PAS_ICON);
	_whiteKingIcon->setSpriteFrame(WK_PAS_ICON);
	
	// Clearing coreData for new customData
	_core->clearData();

	// Deploying kings on the board
	_core->parseFigureDataString(WK_STRING);
	_WKing = _core->getFigureOnBoard(WK_INIT_POS);
	this->addChild(_WKing, BOARD_SIZE - _WKing->getLocation().x);

	_core->parseFigureDataString(BK_STRING);
	_BKing = _core->getFigureOnBoard(BK_INIT_POS);
	this->addChild(_BKing, BOARD_SIZE - _BKing->getLocation().x);

	AudioEngine::play2d(CLICK_SOUND_SAMPLE, false, _core->getSoundsVolume());
}

void CustomGameScene::onGameSettingsClick(cocos2d::Ref* sender)
{
	this->pause();
	AudioEngine::play2d(CLICK_SOUND_SAMPLE, false, _core->getSoundsVolume());
	AudioEngine::stop(_layerMusicID);
	Director::getInstance()->pushScene(GameSettingsMenu::createScene());
}

void CustomGameScene::onQuitGameClick(cocos2d::Ref* sender)
{
	this->pause();
	AudioEngine::play2d(CLICK_SOUND_SAMPLE, false, _core->getSoundsVolume());
	AudioEngine::stop(_layerMusicID);
	Director::getInstance()->pushScene(QuitGameScene::createScene());
}
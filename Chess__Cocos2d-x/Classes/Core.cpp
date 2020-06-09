#include "Core.h"

using namespace cocos2d;
using namespace cocos2d::experimental;


bool Core::init() {
	// creating Board[8][8] with nullptrs
	for (int i = 0; i < BOARD_SIZE; ++i) {
		_board.push_back(std::vector<Figure*>(BOARD_SIZE));
	}
	
	// adding spriteFrames to SpriteFrameCache
	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("Images.plist", "Images.png");

	// initializing figures' pool 
	_figuresPool = FiguresPool::getBarracks();

	// preloading music and sounds
	AudioEngine::preload(CHESS_CLOCK);
	AudioEngine::preload(MAIN_MUSIC_THEME);
	AudioEngine::preload(MENU_MUSIC_THEME);
	AudioEngine::preload(GAME_OVER_MUSIC);
	AudioEngine::preload(CUSTOM_MUSIC);
	AudioEngine::preload(CLICK_SOUND_SAMPLE);
	AudioEngine::preload(MOVE_SOUND_SAMPLE);
	AudioEngine::preload(MUSIC_SAMPLE);
	AudioEngine::preload(MOVE_SOUND1);
	AudioEngine::preload(MOVE_SOUND2);
	AudioEngine::preload(MOVE_SOUND3);
	AudioEngine::preload(MOVE_SOUND4);
	AudioEngine::preload(MOVE_SOUND5);
	AudioEngine::preload(CHECK_SOUND);
	AudioEngine::preload(DRAW_SOUND);

	return true;
}

void Core::initialSetup()
{
	// Creating armies with figures 
	//// White Army
	_WKing = _figuresPool->getFigure(Type::KING, Color::WHITE, WK_INIT_POS);
	_whiteArmy.pushBack(_WKing);
	_whiteArmy.pushBack(_figuresPool->getFigure(Type::QUEEN, Color::WHITE, WQ_INIT_POS));
	_whiteArmy.pushBack(_figuresPool->getFigure(Type::BISHOP, Color::WHITE, WB_INIT_POS1));
	_whiteArmy.pushBack(_figuresPool->getFigure(Type::BISHOP, Color::WHITE, WB_INIT_POS2));
	_whiteArmy.pushBack(_figuresPool->getFigure(Type::KNIGHT, Color::WHITE, WN_INIT_POS1));
	_whiteArmy.pushBack(_figuresPool->getFigure(Type::KNIGHT, Color::WHITE, WN_INIT_POS2));
	_whiteArmy.pushBack(_figuresPool->getFigure(Type::ROOK, Color::WHITE, WR_INIT_POS1));
	_whiteArmy.pushBack(_figuresPool->getFigure(Type::ROOK, Color::WHITE, WR_INIT_POS2));

	//// Black Army
	_BKing = _figuresPool->getFigure(Type::KING, Color::BLACK, BK_INIT_POS);
	_blackArmy.pushBack(_BKing);
	_blackArmy.pushBack(_figuresPool->getFigure(Type::QUEEN, Color::BLACK, BQ_INIT_POS));
	_blackArmy.pushBack(_figuresPool->getFigure(Type::BISHOP, Color::BLACK, BB_INIT_POS1));
	_blackArmy.pushBack(_figuresPool->getFigure(Type::BISHOP, Color::BLACK, BB_INIT_POS2));
	_blackArmy.pushBack(_figuresPool->getFigure(Type::KNIGHT, Color::BLACK, BN_INIT_POS1));
	_blackArmy.pushBack(_figuresPool->getFigure(Type::KNIGHT, Color::BLACK, BN_INIT_POS2));
	_blackArmy.pushBack(_figuresPool->getFigure(Type::ROOK, Color::BLACK, BR_INIT_POS1));
	_blackArmy.pushBack(_figuresPool->getFigure(Type::ROOK, Color::BLACK, BR_INIT_POS2));

	// Pawns
	_pawnQuantity = PAWN_QUANTITY;

	for (int i = 0; i < BOARD_SIZE; ++i) {
		Location tempWhite = WP_INIT_POS1;
		Location tempBlack = BP_INIT_POS1;
		tempWhite.y += i;
		tempBlack.y += i;

		_whiteArmy.pushBack(_figuresPool->getFigure(Type::PAWN, Color::WHITE, tempWhite));
		_blackArmy.pushBack(_figuresPool->getFigure(Type::PAWN, Color::BLACK, tempBlack));
	}

	// updating board's situation considering figures' positions
	for (auto figure : _whiteArmy) {
		Location location = figure->getLocation();
		_board[location.x][location.y] = figure;
	}

	for (Figure* figure : _blackArmy) {
		Location location = figure->getLocation();
		_board[location.x][location.y] = figure;
	}

	// assigning values to the rest of the attributes
	_currentArmy = &_whiteArmy;
	_enemyArmy = &_blackArmy;
	_activeKing = _WKing;
	_figureToMove = nullptr;
	_enPassantFigure = nullptr;
	_figureToPromote = nullptr;
	_tempLocation = Location{ BOARD_SIZE, BOARD_SIZE };
	_halfTurn = 1;
	_CHECK = false;
	_gameOver = false;
	_turnDuration = time(NULL);
	_p1GameDuration = 0.0;
	_p2GameDuration = 0.0;
	_logMessage = NewGameString;
}

Core* Core::sharedCore()
{
	static bool s_firstRun = true;
	static Core s_sharedCore;

	if (s_firstRun) {
		s_sharedCore.init();
		s_firstRun = false;
	}

	return &s_sharedCore;
}

void Core::saveData(std::string filename)
{
	std::string filenamePath = FileUtils::getInstance()->getWritablePath() +
		SAVED_GAMES_DIR + '/' + filename;

	std::ofstream save(filenamePath);
	if (save) {
		// saving _halfTurn
		save << _halfTurn << ' ';

		// saving gameDuration
		save << _p1GameDuration << ' ';
		save << _p2GameDuration << ' ';
		
		// saving "en passant" actions 
		//// location of the pawn, that just made two-square move
		Location enPassantLocation{ BOARD_SIZE, BOARD_SIZE }; // setting point out of the board

		if (_enPassantFigure) {
			enPassantLocation = _enPassantFigure->getLocation();
		}

		//// _tempLocation - square that was skipped by the pawn
		save << enPassantLocation.x << ' ' << enPassantLocation.y << ' '
			<< _tempLocation.x << ' ' << _tempLocation.y << ' ';

		// saving movesLog
		for (auto moveString : _movesVector) {
			save << moveString << ' ';
		}
		save << '\n';

		// saving figures in std::string e.g. "WKA21" - white king, location A2, first move - true;
		for (auto figure : _whiteArmy) {
			const Location location = figure->getLocation();
			const int xCoord = location.x + 1;
			const char yCoord = static_cast<char>(location.y) + 'A';

			save << figure->getFigureName() << yCoord << xCoord << figure->_firstMove << ' ';
		}

		save << '\n';

		for (auto figure : _blackArmy) {
			const Location location = figure->getLocation();
			const int xCoord = location.x + 1;
			const char yCoord = static_cast<char>(location.y) + 'A';

			save << figure->getFigureName() << yCoord << xCoord << figure->_firstMove << ' ';
		}
		save << '\n';

		_logMessage = SuccessSaveGameString + filename;
	}
	else {
		_logMessage = ErrorSaveGameString + filename;
	}

	save.close();
}

void Core::loadData(const std::string& gameDataString,
	const std::string& wArmyDataString, const std::string& bArmyDataString, std::string filename)
{
	//clearing existing core data
	clearData();
	
	std::stringstream load;
	load.str(gameDataString);
	
	// loading _halfTurn
	load >> _halfTurn;
		
	// loading gameDuration
	load >> _p1GameDuration;
	load >> _p2GameDuration;
		
	// loading "en passant" actions 
	//// location of the pawn, that just made two-squares move
	Location enPassantLocation;
	load >> enPassantLocation.x >> enPassantLocation.y;
	//// _tempLocation - square that was skipped by the pawn
	load >> _tempLocation.x >> _tempLocation.y;
		
	// loading savedMovesData
	std::string savedMove;
	for (int savedMoveCounter = 1; savedMoveCounter < _halfTurn;) {
		load >> savedMove;
		_movesVector.push_back(savedMove);
		savedMoveCounter += 1;
	}

	//parsing strings into whiteArmy data
	load.str("");
	load.clear();
	load.str(wArmyDataString);
	std::string col_type_loc;
	while (load) {
		load >> col_type_loc;
		parseFigureDataString(col_type_loc);
	}

	//parsing strings into blackArmy data
	load.str("");
	load.clear();
	load.str(bArmyDataString);
	while (load) {
		load >> col_type_loc;
		parseFigureDataString(col_type_loc);
	}
	
	//// setting pointer to figure, that has just made two-squares move (or to nullprt)
	_enPassantFigure = (enPassantLocation != Location{ BOARD_SIZE, BOARD_SIZE }) ?
	_board[enPassantLocation.x][enPassantLocation.y] : nullptr;

	// updating pointers for quick access
	if (_halfTurn % 2) {
		_currentArmy = &_whiteArmy;
		_enemyArmy = &_blackArmy;
		_activeKing = _WKing;
	}
	else {
		_currentArmy = &_blackArmy;
		_enemyArmy = &_whiteArmy;
		_activeKing = _BKing;
	}

	// checking for CHECK, CHECKMATE and DRAW
	if (isCheck()) {
		_CHECK = true;
		if (isCheckmate()) {
			_gameOver = true;
		}
	}
	else if (isDraw()) {
		_gameOver = true;
	}
	
	if (!_CHECK && !_gameOver) {
		_logMessage = LoadGameSuccessString + filename;
	}
}

void Core::clearData()
{
	// Setting board with nullptrs
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			_board[i][j] = nullptr;
		}
	}

	_movesVector.clear();
	_currentArmy = nullptr;
	_enemyArmy = nullptr;
	_activeKing = nullptr;
	_WKing = nullptr;
	_BKing = nullptr;
	_figureToMove = nullptr;
	_enPassantFigure = nullptr;
	_figureToPromote = nullptr;
	_tempLocation = Location{ BOARD_SIZE, BOARD_SIZE };
	_halfTurn = 1;
	_CHECK = false;
	_gameOver = false;
	_turnDuration = 0;
	_p1GameDuration = 0.0;
	_p2GameDuration = 0.0;
	_logMessage = "";

	// resetting armies' bitsets and pawn quantity
	_bit_whiteArmy.reset();
	_bit_blackArmy.reset();
	_pawnQuantity = 0;

	// deleting current figures
	for (auto figure : _whiteArmy) {
		_figuresPool->putFigure(figure);
		figure->removeFromParent();
	}
	_whiteArmy.clear();

	for (auto figure : _blackArmy) {
		_figuresPool->putFigure(figure);
		figure->removeFromParent();
	}
	_blackArmy.clear();	
}

bool Core::processEvent(Location newLocation)
{
	// ending promotion action
	//Player has made his choice for promotion (Q / B / K / Rook)
	if (_figureToPromote) {
		_figureToMove = _figureToPromote;
		_figureToPromote = nullptr;

		// deleting data for En passant
		_enPassantFigure = nullptr;

		// move and promotion are made, returning to board
		return endTurn(_tempLocation, _figureToMove->getLocation());;
	}

	//checking chosen square
	Figure* chosenSquare = _board[newLocation.x][newLocation.y];

	if (_currentArmy->contains(chosenSquare)) {
		//setting previous figureToMove in passive state
		if (_figureToMove) {
			_figureToMove->setPassiveState();
		}

		_figureToMove = chosenSquare;
		_figureToMove->setActiveState();
		// new figureToMove is chosen, returning to board
		return false;
	}

	if (!_figureToMove) {
		// if there is no figureToMove, returning to board
		return false;
	}

	Location currentLocation = _figureToMove->getLocation();

	//castling checking, execution if true
	if (castling(_figureToMove, currentLocation, newLocation)) {
		// rook movement
		Location rookPosition;
		Location rookNewPosition;
		std::string notation;

		if (newLocation.y > currentLocation.y) {
			rookPosition = Location{ currentLocation.x, BOARD_SIZE - 1 };
			rookNewPosition = Location{ currentLocation.x, newLocation.y - 1 };
			notation = CastlingShort;
		}
		else {
			rookPosition = Location{ currentLocation.x, 0 };
			rookNewPosition = Location{ currentLocation.x, newLocation.y + 1 };
			notation = CastlingLong;
		}
		Figure* rook = _board[rookPosition.x][rookPosition.y];

		_board[rookPosition.x][rookPosition.y] = nullptr;
		_board[rookNewPosition.x][rookNewPosition.y] = rook;
		rook->setLocation(rookNewPosition);
		rook->_firstMove = false;
		rook->runAction(MoveTo::create(0.1f, convertCoord(rookNewPosition)));

		// deleting data for En passant
		_enPassantFigure = nullptr;
		_tempLocation = Location{ BOARD_SIZE, BOARD_SIZE }; // setting point out of the board
		
		//Updating logMessage
		_logMessage = CastlingPerfomed + notation;

		makeMove(_figureToMove, currentLocation, newLocation);

		// castling is made, returning to board
		return endTurn(currentLocation, newLocation);
	}

	// en passant checking, execution if true
	if (enPassant(_figureToMove, currentLocation, newLocation)) {
		Location enPassantLocation = _enPassantFigure->getLocation();

		deletingFigure(_enPassantFigure);
		_board[enPassantLocation.x][enPassantLocation.y] = nullptr;
		
		// deleting data for En passant
		_enPassantFigure = nullptr;
		_tempLocation = Location{ BOARD_SIZE, BOARD_SIZE }; // setting point out of the board
		
		//Updating logMessage
		_logMessage = EnPassantPerformedString + getMoveString(currentLocation, newLocation);;
		
		makeMove(_figureToMove, currentLocation, newLocation);

		// en passant is made, returning to board
		return endTurn(currentLocation, newLocation);
	}

	// checking if figureToMove can execute command
	bool moveIsLegal = false;
	auto v_possibleMoves = _figureToMove->getPossibleMoves(&_board);

	for (auto possiblePosition : *v_possibleMoves) {
		if (newLocation == possiblePosition) {
			moveIsLegal = true;

			break;
		}
	}

	if (!moveIsLegal) {
		_logMessage = ErrorMoveIsIllegal + getMoveString(currentLocation, newLocation);

		//chosen figure can't execute command, returning to board
		return false;
	}
		

	// checking if figure's movement doesn't endanger the king
	if (isKingInDanger(_figureToMove, currentLocation, newLocation)) {
		_logMessage = ErrorKingIsInDanger + getMoveString(currentLocation, newLocation);

		//indeed, returning to board
		return false;
	}

	// deleting data for En passant
	_enPassantFigure = nullptr;
	_tempLocation = Location{ BOARD_SIZE, BOARD_SIZE }; // setting point out of the board

	//checking for new En passant data
	if (_figureToMove->_firstMove) {
		if (_figureToMove->getType() == Type::PAWN) {
			int delta = newLocation.x - currentLocation.x;

			if (delta == 2) {
				_enPassantFigure = _figureToMove;
				_tempLocation = Location{ newLocation.x - 1, newLocation.y };
			}
			else if (delta == -2) {
				_enPassantFigure = _figureToMove;
				_tempLocation = Location{ newLocation.x + 1, newLocation.y };
			}
		}
	}

	// Removing enemy's figure (if needed) and moving figure on new position
	Figure* enemyFigure = _board[newLocation.x][newLocation.y];
	if (enemyFigure) {
		deletingFigure(enemyFigure);
	}

	//Updating logMessage
	_logMessage = PreviousMoveString + getMoveString(currentLocation, newLocation);
	

	// Checking for promotion
	if (_figureToMove->getType() == Type::PAWN && (newLocation.x == 0 || newLocation.x == BOARD_SIZE - 1)) {
		// Starting promotion action
		arrangePromotion(_figureToMove);
		_tempLocation = currentLocation;
		_figureToPromote = _figureToMove;
		
		makeMove(_figureToMove, currentLocation, newLocation);
		
		//chosen figure made its move, player has to make choice for promotion (Q / B / K / Rook)
		return false;
	}

	// Ending move
	makeMove(_figureToMove, currentLocation, newLocation);

	// move is made, returning to board
	return endTurn(currentLocation, newLocation);
}

bool Core::castling(Figure* king, Location currentLocation, Location newLocation)
{
	if ((king->getType() != Type::KING) || _CHECK) {
		// it's not a castling move or king is under attack
		return false;
	}
	
	if (!king->_firstMove) {
		// king can't make a castling move
		return false;
	}
	if (newLocation != Location{ king->getLocation().x, 2 } &&
		newLocation != Location{ king->getLocation().x, 6 }) {
		// it's not a castling move
		return false;
	}

	// cheking if squares king has to move through are empty
	const int delta = (newLocation.y - currentLocation.y) / 2;
	Location square1{ currentLocation.x, currentLocation.y + delta };
	Location square2{ currentLocation.x, currentLocation.y + delta + delta };
	if (!_board[currentLocation.x][square1.y] && !_board[currentLocation.x][square2.y]) {

		// cheking if squares king has to move through are not under attack
		if (!isKingInDanger(king, currentLocation, square1) && !isKingInDanger(king, currentLocation, square2)) {

			// choosing kingside or queenside rook
			Figure* rook = nullptr;
			if (delta > 0) {
				rook = _board[currentLocation.x][BOARD_SIZE - 1];
			}
			else {
				rook = _board[currentLocation.x][0];
				// cheking if square queenside rook has to move through first is empty
				if (_board[currentLocation.x][1]) {
					// castling can't be performed
					return false;
				}
			}

			// cheking rook
			if (rook && rook->getType() == Type::ROOK && rook->_firstMove) {
				// castling can be performed
				return true;
			}
		}
	}
	// castling can't be performed
	return false;
}

bool Core::enPassant(Figure* figureToMove, Location currentLocation, Location newLocation)
{
	bool enPassantIsPossible = false;

	if (figureToMove->getType() != Type::PAWN || !_enPassantFigure) {
		// it's not pawn to move or there is no pawns, that made two-square move
		return false;
	}
	if (newLocation != _tempLocation) {
		// pawn is not intended to make En passant
		return false;
	}

	// location of the pawn, that just made two-squares move
	Location enPassantLocation = _enPassantFigure->getLocation();
	const int delta = currentLocation.y - enPassantLocation.y;

	if (currentLocation.x == enPassantLocation.x && (delta == 1 || delta == -1)) {
		// setting board as if move's been executed
		_enemyArmy->eraseObject(_enPassantFigure);
		_board[currentLocation.x][currentLocation.y] = nullptr;
		_board[enPassantLocation.x][enPassantLocation.y] = nullptr;
		_board[newLocation.x][newLocation.y] = figureToMove;
		figureToMove->setLocation(newLocation);

		// checking for "check"
		enPassantIsPossible = !isCheck();

		// setting board to previous position
		_enemyArmy->pushBack(_enPassantFigure);
		_board[currentLocation.x][currentLocation.y] = figureToMove;
		_board[enPassantLocation.x][enPassantLocation.y] = _enPassantFigure;
		_board[newLocation.x][newLocation.y] = nullptr;
		figureToMove->setLocation(currentLocation);
	}

	return enPassantIsPossible;
}

bool Core::isKingInDanger(Figure* figureToMove, Location currentLocation, Location newLocation)
{
	Figure* enemyFigure = _board[newLocation.x][newLocation.y];
	if (enemyFigure) {
		_enemyArmy->eraseObject(enemyFigure);
	}

	// setting board as if move's been executed
	_board[currentLocation.x][currentLocation.y] = nullptr;
	_board[newLocation.x][newLocation.y] = figureToMove;
	figureToMove->setLocation(newLocation);

	// checking for "check"
	const bool inDanger = isCheck();

	// setting board to previous position
	_board[currentLocation.x][currentLocation.y] = figureToMove;
	_board[newLocation.x][newLocation.y] = enemyFigure;
	figureToMove->setLocation(currentLocation);

	if (enemyFigure) {
		_enemyArmy->pushBack(enemyFigure);
	}

	return inDanger;
}

void Core::makeMove(Figure* figureToMove, Location currentLocation, Location newLocation) {
	// playing "moveSound"
	std::string effect = "Sounds/Move" + std::to_string(rand() % MOVES_SOUND_AMOUNT + 1) + ".mp3";
	AudioEngine::play2d(effect, false, _soundsVolume);

	_board[currentLocation.x][currentLocation.y] = nullptr;
	_board[newLocation.x][newLocation.y] = figureToMove;
	figureToMove->setLocation(newLocation);
	figureToMove->_firstMove = false;
	figureToMove->runAction(MoveTo::create(0.1f, convertCoord(newLocation)));
	figureToMove->setLocalZOrder(BOARD_SIZE - newLocation.x);
	figureToMove->setPassiveState();
}

void Core::deletingFigure(Figure* enemyFigure)
{
	const Type type = enemyFigure->getType();
	const Location location = enemyFigure->getLocation();
	std::bitset<BOARD_SIZE>* bit_enemyArmy;

	bit_enemyArmy = (enemyFigure->getFigureColor() == Color::BLACK) ?
		&_bit_blackArmy : &_bit_whiteArmy;

	// updating bitset considering type of deleted figure
	switch (type) {
		case Type::QUEEN:
			(bit_enemyArmy->test(bit_F_Queen2)) ?
				bit_enemyArmy->reset(bit_F_Queen2) : bit_enemyArmy->reset(bit_F_Queen1);
			break;

		case Type::BISHOP:
			((location.x + location.y) % 2) ?
				bit_enemyArmy->reset(bit_F_Bishop1) : bit_enemyArmy->reset(bit_F_Bishop2);
			break;

		case Type::KNIGHT:
			(bit_enemyArmy->test(bit_F_Knight2)) ?
				bit_enemyArmy->reset(bit_F_Knight2) : bit_enemyArmy->reset(bit_F_Knight1);
			break;

		case Type::ROOK:
			(bit_enemyArmy->test(bit_F_Rook2)) ?
				bit_enemyArmy->reset(bit_F_Rook2) : bit_enemyArmy->reset(bit_F_Rook1);
			break;

		case Type::PAWN:
			_pawnQuantity -= 1;
			break;

		default:
			break;
	}

	_board[location.x][location.y] = nullptr;
	_figuresPool->putFigure(enemyFigure);
	enemyFigure->removeFromParent();
	(enemyFigure->getFigureColor() == Color::BLACK) ?
		_blackArmy.eraseObject(enemyFigure) : _whiteArmy.eraseObject(enemyFigure);
}

void Core::arrangePromotion(Figure* figureToMove)
{
	const auto winSize = Director::getInstance()->getWinSize();
	const Vec2 center{ winSize.width / 2.8f,  winSize.height / 1.9f};
	auto figureParent = figureToMove->getParent();
	
	// pausing all actions, listeners, lowering opacity of total gameLayer
	figureParent->pause();
	for (auto child : figureParent->getChildren()) {
		child->setOpacity(100);
	}

	// Creating QueenSprite to provide option
	auto queen = Sprite::createWithSpriteFrameName(GOLDEN_Q_ICON);
	queen->setScale(0.6f);
	queen->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	queen->setPosition(center.x, center.y + SQUARE_SIZE / 2);
	figureParent->addChild(queen, 100, "Q");
	// Creating RookSprite
	auto rook = Sprite::createWithSpriteFrameName(GOLDEN_R_ICON);
	rook->setScale(0.6f);
	rook->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	rook->setPosition(center.x + SQUARE_SIZE, center.y);
	figureParent->addChild(rook, 100, "R");
	//Creating KnightSprite
	auto knight = Sprite::createWithSpriteFrameName(GOLDEN_H_ICON);
	knight->setScale(0.6f);
	knight->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	knight->setPosition(center.x - SQUARE_SIZE, center.y);
	figureParent->addChild(knight, 100, "N");
	// Creating BishopSprite
	auto bishop = Sprite::createWithSpriteFrameName(GOLDEN_B_ICON);
	bishop->setScale(0.6f);
	bishop->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
	bishop->setPosition(center.x, center.y - SQUARE_SIZE / 2);
	figureParent->addChild(bishop, 100, "B");

	// Creating EventListener for promotion choice
	auto listener = EventListenerMouse::create();

	listener->onMouseDown = [&](Event* event) {
		EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
		auto figureParent = _activeKing->getParent();
		
		auto queen = figureParent->getChildByName("Q");
		auto rook = figureParent->getChildByName("R");
		auto knight = figureParent->getChildByName("N");
		auto bishop = figureParent->getChildByName("B");

		bool promotionIsMade = false;
		//Checking for "Queen" choice
		if (queen && queen->getBoundingBox().containsPoint(mouseEvent->getLocationInView())) {
			executePromotion(_figureToPromote, Type::QUEEN);
			promotionIsMade = true;
		}
		//Checking for "Rook" choice
		else if (rook && rook->getBoundingBox().containsPoint(mouseEvent->getLocationInView())) {
			executePromotion(_figureToPromote, Type::ROOK);
			promotionIsMade = true;
		}
		//Checking for "Knight" choice
		else if (knight && knight->getBoundingBox().containsPoint(mouseEvent->getLocationInView())) {
			executePromotion(_figureToPromote, Type::KNIGHT);
			promotionIsMade = true;
		}
		//Checking for "Bishop" choice
		else if (bishop && bishop->getBoundingBox().containsPoint(mouseEvent->getLocationInView())) {
			executePromotion(_figureToPromote, Type::BISHOP);
			promotionIsMade = true;
		}

		if (promotionIsMade) {
			queen->removeFromParent();
			rook->removeFromParent();
			knight->removeFromParent();
			bishop->removeFromParent();

			figureParent->resume();
			for (auto child : figureParent->getChildren()) {
				child->setOpacity(255);
			}
			
			figureParent->getEventDispatcher()->dispatchEvent(event);
		}
	};

	figureParent->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, figureParent);
}

void Core::executePromotion(Figure* figureToMove, Type figureType)
{
	const Color color = figureToMove->getFigureColor();
	const Location newPosition = figureToMove->getLocation();

	std::bitset<BOARD_SIZE>* bit_currentArmy;
	Figure* promotedFigure = nullptr;
	auto figureParent = figureToMove->getParent();

	bit_currentArmy = (_halfTurn % 2) ? &_bit_whiteArmy : &_bit_blackArmy;
	_logMessage = ChoosePromotionString;
	
	
	if (figureType == Type::QUEEN) {
		promotedFigure = _figuresPool->getFigure(Type::QUEEN, color, newPosition);

		// updating bit_sets (for draw calculatings)
		(bit_currentArmy->test(bit_F_Queen1)) ?
			bit_currentArmy->set(bit_F_Queen2) : bit_currentArmy->set(bit_F_Queen1);
	}
	else if (figureType == Type::BISHOP) {
		promotedFigure = _figuresPool->getFigure(Type::BISHOP, color, newPosition);

		((newPosition.x + newPosition.y) % 2) ?
			bit_currentArmy->set(bit_F_Bishop1) : bit_currentArmy->set(bit_F_Bishop2);
	}
	else if (figureType == Type::KNIGHT) {
		promotedFigure = _figuresPool->getFigure(Type::KNIGHT, color, newPosition);

		(bit_currentArmy->test(bit_F_Knight1)) ?
			bit_currentArmy->set(bit_F_Knight2) : bit_currentArmy->set(bit_F_Knight1);
	}
	else if (figureType == Type::ROOK) {
		promotedFigure = _figuresPool->getFigure(Type::ROOK, color, newPosition);

		(bit_currentArmy->test(bit_F_Rook1)) ?
			bit_currentArmy->set(bit_F_Rook2) : bit_currentArmy->set(bit_F_Rook1);
	}

	// deleting pawn
	deletingFigure(figureToMove);

	// setting new figure
	_board[newPosition.x][newPosition.y] = promotedFigure;
	_currentArmy->pushBack(promotedFigure);
	promotedFigure->setPosition(convertCoord(newPosition));
	figureParent->addChild(promotedFigure, BOARD_SIZE - newPosition.x);
	_figureToPromote = promotedFigure;
	_logMessage = PromotionSuccessString;
}

bool Core::endTurn(Location currentLocation, Location newLocation)
{
	std::string moveString = _figureToMove->getFigureName() + getMoveString(currentLocation, newLocation);

	// updating data
	_figureToMove = nullptr;
	_halfTurn += 1;
	_CHECK = false;
	
	// updating pointers for quick access, recording time
	const auto tempTime = time(NULL);

	if (_halfTurn % 2) {
		_currentArmy = &_whiteArmy;
		_enemyArmy = &_blackArmy;
		_activeKing = _WKing;
		_p2GameDuration += difftime(tempTime, _turnDuration);
	}
	else {
		_currentArmy = &_blackArmy;
		_enemyArmy = &_whiteArmy;
		_activeKing = _BKing;
		_p2GameDuration += difftime(tempTime, _turnDuration);
	}

	// Saving moveString
	const int duration = static_cast<int>(_p1GameDuration + _p2GameDuration);
	if (duration / 60 < 10) {
		moveString += "0";
	}
	moveString += std::to_string(duration / 60) + ':';
	if (duration % 60 < 10) {
		moveString += "0";
	}
	moveString += std::to_string(duration % 60);
	_movesVector.push_back(moveString);

	_turnDuration = tempTime;

	if (isCheck()) {
		_CHECK = true;

		if (isCheckmate()) {
			_gameOver = true;
			AudioEngine::stopAll();
			AudioEngine::play2d(GAME_OVER_MUSIC, false, _musicVolume);
		}
		else {
			AudioEngine::play2d(CHECK_SOUND, false, _soundsVolume);
		}
	}
	else if (isDraw()) {
		_gameOver = true;
		AudioEngine::stopAll();
		AudioEngine::play2d(DRAW_SOUND, false, _soundsVolume);
		AudioEngine::play2d(GAME_OVER_MUSIC, false, _musicVolume);
	}

	// halfTurn is ended
	return true;
}

bool Core::isCheck()
{
	const Location kingPosition = _activeKing->getLocation();

	for (auto enemyFigure : *_enemyArmy) {
		auto v_possibleMoves = enemyFigure->getPossibleMoves(&_board);

		for (auto possiblePosition : *v_possibleMoves) {
			if (kingPosition == possiblePosition) {
				return true;
			}
		}
	}

	return false;
}

bool Core::isCheckmate()
{
	Location kingLocation = _activeKing->getLocation();

	// checking if king can escape attack by himself
	auto v_possibleMoves = _activeKing->getPossibleMoves(&_board);

	for (auto possiblePosition : *v_possibleMoves) {
		if (!isKingInDanger(_activeKing, kingLocation, possiblePosition)) {
			_logMessage += WarningCheckString;

			return false;
		}
	}

	/*checking if army can protect their king 
	(test using king's moves is repeating, but mostly this second check won't be performed)*/

	for (auto figure : *_currentArmy) {
		auto v_possibleMoves = figure->getPossibleMoves(&_board);
		Location figureLocation = figure->getLocation();

		for (auto possiblePosition : *v_possibleMoves) {
			if (!isKingInDanger(figure, figureLocation, possiblePosition)) {
				_logMessage += WarningCheckString;

				return false;
			}
		}

		//// checking if enPassant can be performed to protect the king
		if (figure->getType() == Type::PAWN && _enPassantFigure) {
			if (enPassant(figure, figure->getLocation(), _tempLocation)) {
				_logMessage += WarningCheckString;

				return false;
			}
		}
	}

	// Game Over
	_logMessage += WarningCheckmateString;

	return true;
}

bool Core::isDraw()
{
	// checking stalemate
	bool hasLegalMove = false;

	for (auto figure : *_currentArmy) {
		auto v_possibleMoves = figure->getPossibleMoves(&_board);
		Location figureLocation = figure->getLocation();

		for (auto possiblePosition : *v_possibleMoves) {
			if (!isKingInDanger(figure, figureLocation, possiblePosition)) {
				hasLegalMove = true;

				break;
			}
		}

		// checking for enPassant move
		if (figure->getType() == Type::PAWN && _enPassantFigure && !hasLegalMove) {
			if (enPassant(figure, figure->getLocation(), _tempLocation)) {
				hasLegalMove = true;

				break;
			}
		}
	}

	if (!hasLegalMove) {
		_logMessage = DrawStalemateString;

		return true;
	}

	// checking impossibility of checkmate
	std::bitset<BOARD_SIZE> _bit_temp = _bit_whiteArmy | _bit_blackArmy;

	//// cheking for pawns
	if (_pawnQuantity > 0) {
		return false;
	}

	//// two kings left (there is no bit for kings in the bitsets)
	if (!_bit_temp.to_ulong()) {
		_logMessage = impossibleCheckmate1;

		return true;
	}

	//// king with/without bishop versus king and bishop(bishops) on the same color
	if (_bit_temp.to_ulong() == 4Ul || _bit_temp.to_ulong() == 8Ul) {
		_logMessage = impossibleCheckmate2;

		return true;
	}

	//// king and knight versus king
	if (_bit_temp.to_ulong() == 1Ul && _bit_whiteArmy != _bit_blackArmy) {
		_logMessage = impossibleCheckmate3;

		return true;
	}

	return false;
}

Vec2 Core::convertCoord(Location location)
{
	return Vec2(static_cast<float>(BOARD_X + location.y * SQUARE_SIZE),
		static_cast<float>(BOARD_Y + location.x * SQUARE_SIZE));
}

std::string Core::getMoveString(Location currentLocation, Location newLocation)
{
	std::string moveString;
	moveString = static_cast<char>(currentLocation.y) + 'A';
	moveString += static_cast<char>(currentLocation.x) + '1';
	moveString += '-';
	moveString += static_cast<char>(newLocation.y) + 'A';
	moveString += static_cast<char>(newLocation.x) + '1';

	return moveString;
}

void Core::startTurnDurationCount()
{
	_turnDuration = time(NULL);
}

void Core::parseFigureDataString(std::string col_type_loc)
{
	if (col_type_loc.length() < 4) {
		return;
	}

	Location location;
	Figure* newFigure = nullptr;
	const Color color = static_cast<Color>(col_type_loc[0]);
	std::bitset<BOARD_SIZE>* bit_currentArmy;

	//setting location, e.g "A8" == Location(0,0),"B3" == Location(5,1)
	location.x = static_cast<int>(col_type_loc.at(3) - '1');
	location.y = static_cast<int>(col_type_loc.at(2) - 'A');

	if (location.x < 0 || location.y < 0 || location.x > BOARD_SIZE - 1 || location.y > BOARD_SIZE - 1) {
		// location is out of the board
		return;
	}
	else if (_board[location.x][location.y]) {
		// location is occupied
		return;
	}
	
	//setting color
	if (color == Color::WHITE) {
		_currentArmy = &_whiteArmy;
		bit_currentArmy = &_bit_whiteArmy;
	}
	else if (color == Color::BLACK) {
		_currentArmy = &_blackArmy;
		bit_currentArmy = &_bit_blackArmy;
	}
	else {
		// error color
		return;
	}

	//setting type, creating new figure, adding figure to appropriate army and setting army's bitset
	switch (col_type_loc.at(1)) {
		case static_cast<char>(Type::KING) :
			newFigure = _figuresPool->getFigure(Type::KING, color, location);
			_currentArmy->pushBack(newFigure);
			(color == Color::WHITE) ? _WKing = newFigure : _BKing = newFigure;
			break;

		case static_cast<char>(Type::QUEEN) :
			newFigure = _figuresPool->getFigure(Type::QUEEN, color, location);
			_currentArmy->pushBack(newFigure);
			(bit_currentArmy->test(bit_F_Queen1)) ?
				bit_currentArmy->set(bit_F_Queen2) : bit_currentArmy->set(bit_F_Queen1);
			break;

		case static_cast<char>(Type::BISHOP) :
			newFigure = _figuresPool->getFigure(Type::BISHOP, color, location);
			_currentArmy->pushBack(newFigure);
			((location.x + location.y) % 2) ?
				bit_currentArmy->set(bit_F_Bishop1) : bit_currentArmy->set(bit_F_Bishop2);
			break;

		case static_cast<char>(Type::KNIGHT) :
			newFigure = _figuresPool->getFigure(Type::KNIGHT, color, location);
			_currentArmy->pushBack(newFigure);
			(bit_currentArmy->test(bit_F_Knight1)) ?
				bit_currentArmy->set(bit_F_Knight2) : bit_currentArmy->set(bit_F_Knight1);
			break;

		case static_cast<char>(Type::ROOK) :
			newFigure = _figuresPool->getFigure(Type::ROOK, color, location);
			_currentArmy->pushBack(newFigure);
			(bit_currentArmy->test(bit_F_Rook1)) ?
				bit_currentArmy->set(bit_F_Rook2) : bit_currentArmy->set(bit_F_Rook1);
			break;

		case static_cast<char>(Type::PAWN) :
			newFigure = _figuresPool->getFigure(Type::PAWN, color, location);
			_currentArmy->pushBack(newFigure);
			_pawnQuantity += 1;
			break;

		default:
			return;
	}

	//setting first move state
	if (col_type_loc[4] != L'1') {
		newFigure->_firstMove = false;
	}

	_board[location.x][location.y] = newFigure;

	return;
}

// getters
const cocos2d::Vector<Figure*>* Core::getWhiteArmy() const {
	return &_whiteArmy;
}

const cocos2d::Vector<Figure*>* Core::getBlackArmy() const {
	return &_blackArmy;
}

const cocos2d::Vector<Figure*>* Core::getCurrentArmy() const
{
	return _currentArmy;
}

Figure* Core::getActiveKing() const
{
	return _activeKing;
}

const Figure* Core::getFigureToPromote() const
{
	return _figureToPromote;
}

const std::string& Core::getLogMessage() const 
{
	return _logMessage;
}

const bool Core::getGameOver() const
{
	return _gameOver;
}

const int Core::getHalfTurn() const
{
	return _halfTurn;
}

const std::vector<std::string>* Core::getMovesVector() const
{
	return &_movesVector;
}

const std::string& Core::getLastMove() const
{
	return _movesVector.back();
}

Figure* Core::getFigureOnBoard(Location location) const
{
	return _board[location.x][location.y];
}

const float Core::getSoundsVolume() const
{
	return _soundsVolume;
}

const float Core::getMusicVolume() const
{
	return _musicVolume;
}

const std::pair<double, double> Core::getGameDuration()
{
	const auto tempTime = time(NULL);

	if (_halfTurn % 2) {
		_p1GameDuration += difftime(tempTime, _turnDuration);
	}
	else {
		_p2GameDuration += difftime(tempTime, _turnDuration);
	}

	_turnDuration = tempTime;

	return std::pair<double, double>(_p1GameDuration, _p2GameDuration);
}

// setters
void Core::setLogMessage(std::string logMessage)
{
	_logMessage = logMessage;
}

void Core::setSoundsVolume(float volume)
{
	_soundsVolume = volume;
	if (_soundsVolume > 1.0f) {
		_soundsVolume = 1.0f;
	}
	if (_soundsVolume < 0.0f) {
		_soundsVolume = 0.0f;
	}
}

void Core::setMusicVolume(float volume)
{
	_musicVolume = volume;
	if (_musicVolume > 1.0f) {
		_musicVolume = 1.0f;
	}
	if (_musicVolume < 0.0f) {
		_musicVolume = 0.0f;
	}
}

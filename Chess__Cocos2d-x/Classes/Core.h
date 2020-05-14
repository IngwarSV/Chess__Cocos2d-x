//thanks to Alexandr Zhelanov, https://soundcloud.com/alexandr-zhelanov

#pragma once

#include "cocos2d.h"
#include "audio/include/AudioEngine.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <bitset>

#include "Specification.h"
#include "Figure.h"
#include "Units.h"

using namespace DEF_SETT;

class Core {
private:
// attributes
	// Board[SIZE][SIZE], BOARD_SIZE = 8;
	std::vector < std::vector<Figure*>> _board;
	
	// sets for "White" and "Black" armies and pointers on them
	cocos2d::Vector<Figure*> _whiteArmy = cocos2d::Vector<Figure*>(16);
	cocos2d::Vector<Figure*> _blackArmy = cocos2d::Vector<Figure*>(16);
	cocos2d::Vector<Figure*>* _currentArmy;
	cocos2d::Vector<Figure*>* _enemyArmy;
	
	/* bitsets 0111 1111 for 8 figures (B1, B2, N1, N2, R1, R2, Q1, Q2) 
	in army including 1 place for promoted Queen */
	std::bitset<BOARD_SIZE> _bit_whiteArmy{ 127 };
	std::bitset<BOARD_SIZE> _bit_blackArmy{ 127 };

	//pawns quantity (for draw calculatings)
	int _pawnQuantity; 

	// pointers on kings for quick access
	Figure* _WKing;
	Figure* _BKing;
	Figure* _activeKing;

	// current active figure
	Figure* _figureToMove;

	// temp data for "en passant"/"promotion" actions 
	Figure* _enPassantFigure; // pawn that just made two-squares move
	Figure* _figureToPromote; // pawn that reached board's edge
	/* square that was skipped by "en passant" pawn or
	previous position of promoted pawn*/
	Location _tempLocation; 
	
	int _halfTurn; // game turns: halfTurn * 2
	bool _CHECK;
	bool _gameOver;
	double _p1GameDuration;
	double _p2GameDuration;
	
	// storing halfTurn duration
	time_t _turnDuration;
	
	// storing moves (for scrollView in NewGameScene)
	std::vector<std::string> _movesVector;
	// for game notifications
	std::string _logMessage; 
	
	// Music/Sounds volume
	float _soundsVolume = 1.0f;
	float _musicVolume = 1.0f;
	
// methods
	bool init();

	cocos2d::Vec2 convertCoord(Location location);

	std::string getMoveString(Location currentLocation, Location newLocation);
	
public:
// attributes
	// storing testsResults
	std::vector<std::string> _testsResults;
	
// methods
	void initialSetup();

	static Core* sharedCore();
	
	// saving gameData
	void saveData(std::string filename);

	// loading gameData
	void loadData(const std::string& gameDataString, 
		const std::string& wArmyDataString, const std::string& bArmyDataString, std::string filename);

	// deleting existing game data to load saved game / customize new game
	void clearData(); 

	// main logic block
	bool processEvent(Location newLocation);

	bool castling(Figure* king, Location currentLocation, Location newLocation);

	bool enPassant(Figure* figureToMove, Location currentLocation, Location newLocation);

	bool isKingInDanger(Figure* figureToMove, Location currentLocation, Location newLocation);

	void makeMove(Figure* figureToMove, Location currentLocation, Location newLocation);

	void deletingFigure(Figure* enemyFigure);

	void arrangePromotion(Figure* figureToMove);

	bool endTurn(Location currentLocation, Location newLocation);

	bool isCheck();

	bool isCheckmate();

	bool isDraw();

	void executePromotion(Figure* figureToMove, Type figureType);
	
	//parsing string into figure's data (in case of loading saved game, custom game)
	void parseFigureDataString(std::string col_type_loc); 

	// reseting turnDurationCount
	void startTurnDurationCount();

	// getters
	const cocos2d::Vector<Figure*>* getWhiteArmy() const;
	const cocos2d::Vector<Figure*>* getBlackArmy() const;
	const cocos2d::Vector<Figure*>* getCurrentArmy() const;
	Figure* getActiveKing() const;
	Figure* getFigureOnBoard(Location location) const;
	const Figure* getFigureToPromote() const;
	const std::string& getLogMessage() const;
	const bool getGameOver() const;
	const int getHalfTurn() const;
	const std::vector<std::string>* getMovesVector() const;
	const std::string& getLastMove() const;
	const float getSoundsVolume() const;
	const float getMusicVolume() const;
	//// updating and providing gameDuration
	const std::pair<double, double> getGameDuration();

	//setters
	void setLogMessage(std::string logMessage);
	void setSoundsVolume(float volume);
	void setMusicVolume(float volume);
};

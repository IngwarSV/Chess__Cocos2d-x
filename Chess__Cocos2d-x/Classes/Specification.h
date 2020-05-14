#pragma once

#include "cocos2d.h"
#include <string>


struct Location {
	int x = 0, y = 0;

	bool operator==(const Location& other) const {
		return this->x == other.x && this->y == other.y;
	}

	bool operator!=(const Location& other) const {
		return this->x != other.x || this->y != other.y;
	}
};

enum class Color : char {
	NONE = 0,
	BLACK = 66,
	WHITE = 87
};

enum class Type : char {
	KING = 75,
	QUEEN = 81,
	BISHOP = 66,
	KNIGHT = 78,
	ROOK = 82,
	PAWN = 80
};

namespace DEF_SETT {
	// Board size
	constexpr int BOARD_SIZE = 8;

	// Board  bottom-left corner
	constexpr int BOARD_X = 73;
	constexpr int BOARD_Y = 104;

	// Square size in pixels
	constexpr int SQUARE_SIZE = 73;

	//pawns quantity (for draw calculating)
	constexpr int PAWN_QUANTITY = 16;

	// Main font
	const std::string FONT{ "fonts/BOOK_ANTIQUA.ttf" };
	const std::string FONT2{ "fonts/royal-serif.ttf" };

	// Labels' font size and distance between
	constexpr float LABEL_FONT_SIZE = 18.0f;
	constexpr float LABEL_DISTANCE = LABEL_FONT_SIZE + 2;

	// Labels color
	const cocos2d::Color3B METALLIC_GOLD{ 212, 175, 55 };
	const cocos2d::Color3B CHOKOLATE{ 210,105,30 };

	//GameLabels
	const std::string QUIT_GAME_LABEL{ "Quit Game?" };
	const std::string SAVE_GAME_LABEL{ "Save Game" };
	const std::string PLACEHOLDER_SAVE_GAME{ "Type here" };
	const std::string LOAD_GAME_LABEL{ "Load Game" };

	// UI COMPONENTS' POSITIONS
	const cocos2d::Vec2 LOG_MESS_POS{ 105.0f, 21.0f };
	const cocos2d::Vec2 SAVE_GAME_BUT{ 236.0f, 320.0f };
	const cocos2d::Vec2 LOAD_GAME_BUT{ 314.0f, 320.0f };
	const cocos2d::Vec2 GAME_SETT_BUT{ 392.0f, 320.0f };
	const cocos2d::Vec2 QUIT_BUT{ 470.0f, 320.0f };
	const cocos2d::Vec2 TIMER1_POS{ 754.0f, 443.0f };
	const cocos2d::Vec2 TIMER2_POS{ 914.0f, 443.0f };
	const cocos2d::Vec2 ACT_SIDE_POS1{ 790.0f, 575.0f };
	const cocos2d::Vec2 ACT_SIDE_POS2{ 941.0f, 575.0f };

	// Images for sprites
	////Side to move
	const std::string WK_ACT_ICON{ "WK_ACT_ForTurns.png" };
	const std::string WK_PAS_ICON{ "WK_PAS_ForTurns.png" };
	const std::string BK_ACT_ICON{ "BK_ACT_ForTurns.png" };
	const std::string BK_PAS_ICON{ "BK_PAS_ForTurns.png" };
	//// Promotion variants
	const std::string GOLDEN_Q_ICON{ "GoldenQueen.png" };
	const std::string GOLDEN_R_ICON{ "GoldenRook.png" };
	const std::string GOLDEN_H_ICON{ "GoldenHorse.png" };
	const std::string GOLDEN_B_ICON{ "GoldenBishop.png" };

	// SCROLL_VIEW (for moves's log) stuff
	//// SCROLL_VIEW_POS
	const cocos2d::Vec2 SCROLL_VIEW_POS{ 725.0f, 22.0f };
	//// SCROLL_VIEW_SIZE
	const cocos2d::Size SCROLL_VIEW_SIZE{ 290, 380 };
	//// Move label CoordX
	const float labelCoordX = 25.0f;
	//// Move labels' strings
	const std::string GAME_STARTED_STRING{ "\t\t\t\t Game started!" };
	const std::string WHITE_PL_STRING{ "White player:\t" };
	const std::string BLACK_PL_STRING{ "Black player: \t" };

	// Music
	const std::string MUSIC_SAMPLE{ "Sounds/MUSIC_SAMPLE.mp3" };
	const std::string MAIN_MUSIC_THEME{ "Sounds/MenuTheme1.mp3" };
	const std::string MENU_MUSIC_THEME{ "Sounds/MenuTheme2.mp3" };
	const std::string GAME_OVER_MUSIC{ "Sounds/GameOver.mp3" };
	const std::string CUSTOM_MUSIC{ "Sounds/CustomPipes.mp3" };


	// Sounds
	const int MOVES_SOUND_AMOUNT = 5;
	const std::string MOVE_SOUND_SAMPLE{ "Sounds/Click.mp3" };
	const std::string CLICK_SOUND_SAMPLE{ "Sounds/Click.mp3" };
	const std::string CHESS_CLOCK{ "Sounds/ChessClock.mp3" };
	const std::string CHECK_SOUND{ "Sounds/Sword1.mp3" };
	const std::string DRAW_SOUND{ "Sounds/Draw1.mp3" };
	const std::string MOVE_SOUND1{ "Sounds/Move1.mp3" };
	const std::string MOVE_SOUND2{ "Sounds/Move2.mp3" };
	const std::string MOVE_SOUND3{ "Sounds/Move3.mp3" };
	const std::string MOVE_SOUND4{ "Sounds/Move4.mp3" };
	const std::string MOVE_SOUND5{ "Sounds/Move5.mp3" };

	// Saved games directory
	const std::string SAVED_GAMES_DIR = "SavedGames";

	// CustomGame stuff
	const cocos2d::Vec2 PULL_DESK_POS{ 740.0f, 85.0f };
	//// Pull board  bottom-left corner
	constexpr int CUS_BOARD_COL_SIZE = 3;
	constexpr int CUS_BOARD_ROW_SIZE = 4;
	constexpr int CUS_BOARD_X = 13;
	constexpr int CUS_BOARD_Y = 20;
	//// PullBoard vector size
	constexpr int PULL_BOARD_MAXSIZE = 12;
	//// Side to move first
	const cocos2d::Vec2 WHITE_SIDE_POS{ 790.0f, 550.0f };
	const cocos2d::Vec2 BLACK_SIDE_POS{ 941.0f, 550.0f };
	//// string to create king
	const std::string WK_STRING{ "WKE11" };
	const std::string BK_STRING{ "BKE81" };

	// Figures' starting positions
	//// White Army
	const Location WR_INIT_POS1{ 0,0 };
	const Location WN_INIT_POS1{ 0,1 };
	const Location WB_INIT_POS1{ 0,2 };
	const Location WQ_INIT_POS{ 0,3 };
	const Location WK_INIT_POS{ 0,4 };
	const Location WB_INIT_POS2{ 0,5 };
	const Location WN_INIT_POS2{ 0,6 };
	const Location WR_INIT_POS2{ 0,7 };
	const Location WP_INIT_POS1{ 1,0 };

	//// Black Army
	const Location BR_INIT_POS1{ 7,0 };
	const Location BN_INIT_POS1{ 7,1 };
	const Location BB_INIT_POS1{ 7,2 };
	const Location BQ_INIT_POS{ 7,3 };
	const Location BK_INIT_POS{ 7,4 };
	const Location BB_INIT_POS2{ 7,5 };
	const Location BN_INIT_POS2{ 7,6 };
	const Location BR_INIT_POS2{ 7,7 };
	const Location BP_INIT_POS1{ 6,0 };

	// serial number of bits for 8 figures: N1, N2, B1, B2, R1, R2, Q1, Q2 in bitsets
	const int bit_F_Knight1 = 0;
	const int bit_F_Knight2 = 1;
	const int bit_F_Bishop1 = 2;
	const int bit_F_Bishop2 = 3;
	const int bit_F_Rook1 = 4;
	const int bit_F_Rook2 = 5;
	const int bit_F_Queen1 = 6;
	const int bit_F_Queen2 = 7;

	// Log Messages
	//// Game
	const std::string NewGameString{ "New Game!" };
	const std::string CastlingPerfomed{ "Castling is done: " };
	const std::string CastlingShort{ "O-O  " };
	const std::string CastlingLong{ "O-O-O" };
	const std::string EnPassantPerformedString{ "En passant is made: " };
	const std::string ErrorMoveIsIllegal{ "Figure can't move: " };
	const std::string ErrorKingIsInDanger{ "Your King is in danger if: " };
	const std::string PreviousMoveString{ "Previous move: " };
	const std::string WarningCheckString{ " Warning: CHECK!" };
	const std::string WarningCheckmateString{ " CHECKMATE: GAME OVER!" };
	const std::string DrawStalemateString{ "DRAW: stalemate" };
	const std::string impossibleCheckmate1{ "DRAW: two kings left" };
	const std::string impossibleCheckmate2{ "DRAW: kings with bishop(bishops) on the same color" };
	const std::string impossibleCheckmate3{ "DRAW: king and knight versus king" };
	const std::string ChoosePromotionString{ "Choose promotion: Q, B, N, R" };
	const std::string PromotionSuccessString{ "Promotion successful!" };
	////Save-Load
	const std::string SuccessSaveGameString{ "File was saved as: " };
	const std::string ErrorSaveGameString{ "Error while creating file: " };
	const std::string ErrorSaveGameOverString{ "Can't save, game over" };
	const std::string ErrorLoadGameString{ "No files to load" };
	const std::string NoSuchLoadFileString{ "No such file in directory: " };
	const std::string LoadGameSuccessString{ "File was successfully loaded: " };
	const std::string ErrorActionDuringPromotionString{ "Make your choice" };

	////Custom Game
	const std::string CustomModeString{ "Deploy figures, choose side to move first and play" };
	const std::string SaveTheKingString{ "Stay away from king" };
	const std::string ChooseSquareString{ "Choose square to deploy figure" };
	const std::string ChooseSideToMoveString{ "Choose side to move first" };
	const std::string CustomGameLoadedString{ "Custom Game" };
}

#pragma once

#include "cocos2d.h"

#include "Specification.h"
#include "Figure.h"

// each unit overrides Figure's getPossibleMoves() method

class F_King : public Figure {
public:
	static F_King* createFigure(Color color, Location location, Type type = Type::KING);

	virtual bool init();

	CREATE_FUNC(F_King);

	std::vector<Location>* getPossibleMoves(std::vector < std::vector<Figure*>>* board) override;
};


class F_Queen : public Figure {
public:
	static F_Queen* createFigure(Color color, Location location, Type type = Type::QUEEN);

	virtual bool init();

	CREATE_FUNC(F_Queen);

	std::vector<Location>* getPossibleMoves(std::vector < std::vector<Figure*>>* board) override;
};


class F_Bishop : public Figure {
public:
	static F_Bishop* createFigure(Color color, Location location, Type type = Type::BISHOP);

	virtual bool init();

	CREATE_FUNC(F_Bishop);

	std::vector<Location>* getPossibleMoves(std::vector < std::vector<Figure*>>* board) override;
};


class F_Knight : public Figure {
public:
	static F_Knight* createFigure(Color color, Location location, Type type = Type::KNIGHT);

	virtual bool init();

	CREATE_FUNC(F_Knight);

	std::vector<Location>* getPossibleMoves(std::vector < std::vector<Figure*>>* board) override;
};


class F_Rook : public Figure {
public:
	static F_Rook* createFigure(Color color, Location location, Type type = Type::ROOK);

	virtual bool init();

	CREATE_FUNC(F_Rook);

	std::vector<Location>* getPossibleMoves(std::vector < std::vector<Figure*>>* board) override;

};


class F_Pawn : public Figure {
public:
	static F_Pawn* createFigure(Color color, Location location, Type type = Type::PAWN);

	virtual bool init();

	CREATE_FUNC(F_Pawn);

	std::vector<Location>* getPossibleMoves(std::vector < std::vector<Figure*>>* board) override;
};

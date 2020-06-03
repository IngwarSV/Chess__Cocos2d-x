#pragma once

#include "cocos2d.h"
#include <iostream>
#include <string>
#include <algorithm>

#include "Specification.h"
#include "Figure.h"
#include "Units.h"

using namespace DEF_SETT;

class FiguresPool {
private:
	FiguresPool() {};
	FiguresPool(const FiguresPool& copy) = delete;
	FiguresPool& operator=(const FiguresPool& copy) = delete;

// attributes
	cocos2d::Vector<Figure*> _barracks{ BOARD_SIZE * 5 }; // reserve BOARD_SIZE * 5;
public:
	static FiguresPool* getBarracks();

	bool init();

	Figure* createFigure(Type figureType, Color figureColor,
		Location location = Location{ BOARD_SIZE, BOARD_SIZE });

	Figure* getFigure(Type figureType, Color figureColor, Location location);

	void putFigure(Figure* figure);
};

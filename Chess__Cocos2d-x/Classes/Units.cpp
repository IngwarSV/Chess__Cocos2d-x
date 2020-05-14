#include "Units.h"
using namespace cocos2d;
using namespace DEF_SETT;

F_King* F_King::createFigure(Color color, Location location, Type type)
{
	auto figure = F_King::create();

	figure->_color = color;
	figure->_type = type;
	figure->_name += static_cast<char>(color);
	figure->_name += static_cast<char>(type);
	figure->_location = location;
	figure->_firstMove = true;
	figure->setSpriteFrame(figure->_name + "_Pas.png");
	figure->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	figure->setPosition(static_cast<float>(BOARD_X + location.y * SQUARE_SIZE),
			static_cast<float>(BOARD_Y + location.x * SQUARE_SIZE));
	figure->setVisible(true);

	return figure;
}

bool F_King::init()
{
	if (!Figure::init())
	{
		return false;
	}

	return true;
}

std::vector<Location>* F_King::getPossibleMoves(Figure*** board)
{
	// clearing vector every turn
	_possibleMoves.clear();

	//"vertical" moves
	Location tempLocation = this->getLocation();
	tempLocation.x -= 1;

	if (tempLocation.x >= 0) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);
		}
	}

	tempLocation = this->getLocation();
	tempLocation.x += 1;

	if (tempLocation.x < BOARD_SIZE) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);
		}
	}

	//"horizontal" moves
	tempLocation = this->getLocation();
	tempLocation.y -= 1;

	if (tempLocation.y >= 0) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);
		}
	}

	tempLocation = this->getLocation();
	tempLocation.y += 1;

	if (tempLocation.y < BOARD_SIZE) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);
		}
	}

	//right diagonal moves
	tempLocation = this->getLocation();
	tempLocation.x -= 1;
	tempLocation.y += 1;

	if (tempLocation.x >= 0 && tempLocation.y < BOARD_SIZE) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);
		}
	}

	tempLocation = this->getLocation();
	tempLocation.x += 1;
	tempLocation.y += 1;

	if (tempLocation.x < BOARD_SIZE && tempLocation.y < BOARD_SIZE) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);
		}
	}

	//left diagonal moves
	tempLocation = this->getLocation();
	tempLocation.x -= 1;
	tempLocation.y -= 1;

	if (tempLocation.x >= 0 && tempLocation.y >= 0) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);
		}
	}

	tempLocation = this->getLocation();
	tempLocation.x += 1;
	tempLocation.y -= 1;

	if (tempLocation.x < BOARD_SIZE && tempLocation.y >= 0) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);
		}
	}

	return &_possibleMoves;
}


F_Queen* F_Queen::createFigure(Color color, Location location, Type type)
{
	auto figure = F_Queen::create();

	figure->_color = color;
	figure->_type = type;
	figure->_name += static_cast<char>(color);
	figure->_name += static_cast<char>(type);
	figure->_location = location;
	figure->_firstMove = true;
	figure->setSpriteFrame(figure->_name + "_Pas.png");
	figure->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	figure->setPosition(static_cast<float>(BOARD_X + location.y * SQUARE_SIZE),
		static_cast<float>(BOARD_Y + location.x * SQUARE_SIZE));
	figure->setVisible(true);

	return figure;
}

bool F_Queen::init()
{
	if (!Figure::init())
	{
		return false;
	}

	return true;
}


std::vector<Location>* F_Queen::getPossibleMoves(Figure*** board)
{
	// clearing vector every turn
	_possibleMoves.clear();

	//vertical moves
	Location tempLocation = this->getLocation();

	for (tempLocation.x += 1; tempLocation.x < BOARD_SIZE; ++tempLocation.x) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	tempLocation = this->getLocation();

	for (tempLocation.x -= 1; tempLocation.x >= 0; --tempLocation.x) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	//horizontal moves
	tempLocation = this->getLocation();

	for (tempLocation.y += 1; tempLocation.y < BOARD_SIZE; ++tempLocation.y) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	tempLocation = this->getLocation();

	for (tempLocation.y -= 1; tempLocation.y >= 0; --tempLocation.y) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	//right diagonal moves
	tempLocation = this->getLocation();
	tempLocation.x -= 1;
	tempLocation.y += 1;

	for (; tempLocation.x >= 0 && tempLocation.y < BOARD_SIZE; --tempLocation.x, ++tempLocation.y) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	tempLocation = this->getLocation();
	tempLocation.x += 1;
	tempLocation.y += 1;

	for (; tempLocation.x < BOARD_SIZE && tempLocation.y < BOARD_SIZE; ++tempLocation.x, ++tempLocation.y) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	//left diagonal moves
	tempLocation = this->getLocation();
	tempLocation.x -= 1;
	tempLocation.y -= 1;

	for (; tempLocation.x >= 0 && tempLocation.y >= 0; --tempLocation.x, --tempLocation.y) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	tempLocation = this->getLocation();
	tempLocation.x += 1;
	tempLocation.y -= 1;

	for (; tempLocation.x < BOARD_SIZE && tempLocation.y >= 0; ++tempLocation.x, --tempLocation.y) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	return &_possibleMoves;
}



F_Bishop* F_Bishop::createFigure(Color color, Location location, Type type)
{
	auto figure = F_Bishop::create();

	figure->_color = color;
	figure->_type = type;
	figure->_name += static_cast<char>(color);
	figure->_name += static_cast<char>(type);
	figure->_location = location;
	figure->_firstMove = true;
	figure->setSpriteFrame(figure->_name + "_Pas.png");
	figure->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	figure->setPosition(static_cast<float>(BOARD_X + location.y * SQUARE_SIZE),
		static_cast<float>(BOARD_Y + location.x * SQUARE_SIZE));
	figure->setVisible(true);

	return figure;
}

bool F_Bishop::init()
{
	if (!Figure::init())
	{
		return false;
	}

	return true;
}

std::vector<Location>* F_Bishop::getPossibleMoves(Figure*** board)
{
	// clearing vector every turn
	_possibleMoves.clear();

	//right diagonal moves
	Location tempLocation = this->getLocation();
	tempLocation.x -= 1;
	tempLocation.y += 1;

	for (; tempLocation.x >= 0 && tempLocation.y < BOARD_SIZE; --tempLocation.x, ++tempLocation.y) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	tempLocation = this->getLocation();
	tempLocation.x += 1;
	tempLocation.y += 1;

	for (; tempLocation.x < BOARD_SIZE && tempLocation.y < BOARD_SIZE; ++tempLocation.x, ++tempLocation.y) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	//left diagonal moves
	tempLocation = this->getLocation();
	tempLocation.x -= 1;
	tempLocation.y -= 1;

	for (; tempLocation.x >= 0 && tempLocation.y >= 0; --tempLocation.x, --tempLocation.y) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	tempLocation = this->getLocation();
	tempLocation.x += 1;
	tempLocation.y -= 1;

	for (; tempLocation.x < BOARD_SIZE && tempLocation.y >= 0; ++tempLocation.x, --tempLocation.y) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	return &_possibleMoves;
}



F_Knight* F_Knight::createFigure(Color color, Location location, Type type)
{
	auto figure = F_Knight::create();

	figure->_color = color;
	figure->_type = type;
	figure->_name += static_cast<char>(color);
	figure->_name += static_cast<char>(type);
	figure->_location = location;
	figure->_firstMove = true;
	figure->setSpriteFrame(figure->_name + "_Pas.png");
	figure->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	figure->setPosition(static_cast<float>(BOARD_X + location.y * SQUARE_SIZE),
		static_cast<float>(BOARD_Y + location.x * SQUARE_SIZE));
	figure->setVisible(true);

	return figure;
}

bool F_Knight::init()
{
	if (!Figure::init())
	{
		return false;
	}

	return true;
}

std::vector<Location>* F_Knight::getPossibleMoves(Figure*** board)
{
	// clearing vector every turn
	_possibleMoves.clear();

	//"vertical" up moves
	Location tempLocation = this->getLocation();
	tempLocation.x -= 2;
	tempLocation.y -= 1;

	if (tempLocation.x >= 0 && tempLocation.y >= 0) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);
		}
	}

	tempLocation = this->getLocation();
	tempLocation.x -= 2;
	tempLocation.y += 1;

	if (tempLocation.x >= 0 && tempLocation.y < BOARD_SIZE) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);
		}
	}

	//"vertical" down moves
	tempLocation = this->getLocation();
	tempLocation.x += 2;
	tempLocation.y -= 1;

	if (tempLocation.x < BOARD_SIZE && tempLocation.y >= 0) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);
		}
	}

	tempLocation = this->getLocation();
	tempLocation.x += 2;
	tempLocation.y += 1;

	if (tempLocation.x < BOARD_SIZE && tempLocation.y < BOARD_SIZE) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);
		}
	}

	//"horizontal" left moves
	tempLocation = this->getLocation();
	tempLocation.x -= 1;
	tempLocation.y -= 2;

	if (tempLocation.x >= 0 && tempLocation.y >= 0) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);
		}
	}

	tempLocation = this->getLocation();
	tempLocation.x += 1;
	tempLocation.y -= 2;

	if (tempLocation.x < BOARD_SIZE && tempLocation.y >= 0) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);
		}
	}

	//"horizontal" right moves
	tempLocation = this->getLocation();
	tempLocation.x += 1;
	tempLocation.y += 2;

	if (tempLocation.x < BOARD_SIZE && tempLocation.y < BOARD_SIZE) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);
		}
	}

	tempLocation = this->getLocation();
	tempLocation.x -= 1;
	tempLocation.y += 2;

	if (tempLocation.x >= 0 && tempLocation.y < BOARD_SIZE) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);
		}
	}

	return &_possibleMoves;
}


F_Rook* F_Rook::createFigure(Color color, Location location, Type type)
{
	auto figure = F_Rook::create();

	figure->_color = color;
	figure->_type = type;
	figure->_name += static_cast<char>(color);
	figure->_name += static_cast<char>(type);
	figure->_location = location;
	figure->_firstMove = true;
	figure->setSpriteFrame(figure->_name + "_Pas.png");
	figure->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	figure->setPosition(static_cast<float>(BOARD_X + location.y * SQUARE_SIZE),
		static_cast<float>(BOARD_Y + location.x * SQUARE_SIZE));
	figure->setVisible(true);

	return figure;
}

bool F_Rook::init()
{
	if (!Figure::init())
	{
		return false;
	}

	return true;
}

std::vector<Location>* F_Rook::getPossibleMoves(Figure*** board)
{
	// clearing vector every turn
	_possibleMoves.clear();

	//vertical moves
	Location tempLocation = this->getLocation();

	for (tempLocation.x += 1; tempLocation.x < BOARD_SIZE; ++tempLocation.x) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	tempLocation = this->getLocation();

	for (tempLocation.x -= 1; tempLocation.x >= 0; --tempLocation.x) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	//horizontal moves
	tempLocation = this->getLocation();

	for (tempLocation.y += 1; tempLocation.y < BOARD_SIZE; ++tempLocation.y) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	tempLocation = this->getLocation();

	for (tempLocation.y -= 1; tempLocation.y >= 0; --tempLocation.y) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
		else if (figure->getFigureColor() != this->getFigureColor()) {
			_possibleMoves.push_back(tempLocation);

			break;
		}
		else {
			break;
		}
	}

	return &_possibleMoves;
}


F_Pawn* F_Pawn::createFigure(Color color, Location location, Type type)
{
	auto figure = F_Pawn::create();

	figure->_color = color;
	figure->_type = type;
	figure->_name += static_cast<char>(color);
	figure->_name += static_cast<char>(type);
	figure->_location = location;
	figure->_firstMove = true;
	figure->setSpriteFrame(figure->_name + "_Pas.png");
	figure->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	figure->setPosition(static_cast<float>(BOARD_X + location.y * SQUARE_SIZE),
		static_cast<float>(BOARD_Y + location.x * SQUARE_SIZE));
	figure->setVisible(true);

	return figure;
}

bool F_Pawn::init()
{
	if (!Figure::init())
	{
		return false;
	}

	return true;
}


std::vector<Location>* F_Pawn::getPossibleMoves(Figure*** board)
{
	// clearing vector every turn
	_possibleMoves.clear();

	int delta = (this->getFigureColor() == Color::WHITE) ? 1 : -1;
	
	//Moves
	Location tempLocation = this->getLocation();
	tempLocation.x += delta;

	if (tempLocation.x >= 0 && tempLocation.x < BOARD_SIZE) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (!figure) {
			_possibleMoves.push_back(tempLocation);
		}
	}

	if (this->_firstMove) {
		const Figure* figure1 = board[tempLocation.x][tempLocation.y];

		tempLocation.x += delta;
		if (tempLocation.x >= 0 && tempLocation.x < BOARD_SIZE) {
			const Figure* figure2 = board[tempLocation.x][tempLocation.y];

			if (!figure1 && !figure2) {
				_possibleMoves.push_back(tempLocation);
			}
		}
	}

	//Attacks
	tempLocation = this->getLocation();
	tempLocation.x += delta;
	tempLocation.y += delta;

	if (tempLocation.x >= 0 && tempLocation.x < BOARD_SIZE &&
		tempLocation.y >= 0 && tempLocation.y < BOARD_SIZE) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (figure) {
			if (figure->getFigureColor() != this->getFigureColor()) {
				_possibleMoves.push_back(tempLocation);
			}
		}
	}

	tempLocation = this->getLocation();
	tempLocation.x += delta;
	tempLocation.y -= delta;

	if (tempLocation.x >= 0 && tempLocation.x < BOARD_SIZE &&
		tempLocation.y >= 0 && tempLocation.y < BOARD_SIZE) {
		const Figure* figure = board[tempLocation.x][tempLocation.y];

		if (figure) {
			if (figure->getFigureColor() != this->getFigureColor()) {
				_possibleMoves.push_back(tempLocation);
			}
		}
	}

	return &_possibleMoves;
}

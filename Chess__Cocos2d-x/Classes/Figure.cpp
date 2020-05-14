#include "Figure.h"

using namespace cocos2d;
using namespace DEF_SETT;

Figure::Figure(Color color, Location location, Type type)
{
	this->_color = color;
	this->_type = type;
	this->_name += static_cast<char>(color);
	this->_name += static_cast<char>(type);
	this->_location = location;
	this->_firstMove = true;
	this->_possibleMoves = new std::vector<Location>();
	this->initWithSpriteFrameName(_name + "_Pas.png");
	this->setAnchorPoint(Vec2(0.0, 0.0));
	this->setPosition(static_cast<float>(BOARD_X + location.y * SQUARE_SIZE), 
		static_cast<float>(BOARD_Y + location.x * SQUARE_SIZE));
}

Figure::~Figure()
{
	delete _possibleMoves;
}

const Color Figure::getFigureColor() const
{
	return _color;
}

const Type Figure::getType() const
{
	return _type;
}

const std::string& Figure::getFigureName() const
{
	return _name;
}

const Location Figure::getLocation() const
{
	return _location;
}

void Figure::setLocation(Location location)
{
	_location.x = location.x;
	_location.y = location.y;
}

void Figure::setPassiveState()
{
	this->setSpriteFrame(_name + "_Pas.png");
}

void Figure::setActiveState()
{
	this->setSpriteFrame(_name + "_Act.png");
}


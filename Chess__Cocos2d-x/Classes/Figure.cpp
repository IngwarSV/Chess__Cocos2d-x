#include "Figure.h"

using namespace cocos2d;
using namespace DEF_SETT;


bool Figure::init()
{
	// initializing our figure from SpriteFrameCache
	if (this->initWithSpriteFrameName("WK_Pas.png")) {
		this->setVisible(false);
		
		return true;
	}
	
	return false;
}

std::vector<Location>* Figure::getPossibleMoves(std::vector < std::vector<Figure*>>* board)
{
	return &_possibleMoves;
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


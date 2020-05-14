#pragma once

#include "cocos2d.h"
#include <string>
#include <vector>

#include "Specification.h"


class Figure : public cocos2d::Sprite
{
protected:
// attributes
	Color _color;
	Type _type;
	std::string _name;
	Location _location;
	std::vector<Location>* _possibleMoves = nullptr;

public:
	Figure(Color color, Location location, Type type);
	virtual ~Figure();
// attributes
	bool _firstMove;

// methods
	/*pure virtual method, returns vector of figure's possible moves, 
	considering situation on the board*/
	virtual std::vector<Location>* getPossibleMoves(Figure*** board) = 0;
	
	//getters
	const Color getFigureColor() const;
	const Type getType() const;
	const std::string& getFigureName() const;
	const Location getLocation() const;

	//setters
	void setLocation(Location location);
	void setActiveState();
	void setPassiveState();
};

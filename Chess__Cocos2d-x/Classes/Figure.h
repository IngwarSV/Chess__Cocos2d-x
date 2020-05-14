#pragma once

#include "cocos2d.h"
#include <string>
#include <vector>

#include "Specification.h"


class Figure : public cocos2d::Sprite
{
protected:
// attributes
	Color _color = Color::NONE;
	Type _type = Type::NONE;
	std::string _name;
	Location _location;
	std::vector<Location> _possibleMoves;

public:
	virtual bool init() override;

	CREATE_FUNC(Figure);

// attributes
	bool _firstMove = true;

// methods
	/*virtual method, returns vector of figure's possible moves, 
	considering situation on the board*/
	virtual std::vector<Location>* getPossibleMoves(Figure*** board);
	
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

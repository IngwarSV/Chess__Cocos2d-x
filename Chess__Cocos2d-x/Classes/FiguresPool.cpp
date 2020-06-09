#include "FiguresPool.h"

FiguresPool* FiguresPool::getBarracks()
{
	static bool s_firstRun = true;
	static FiguresPool s_figureBarracks;

	if (s_firstRun) {
		s_figureBarracks.init();
		s_firstRun = false;
	}

	return &s_figureBarracks;
}

bool FiguresPool::init()
{
	// creating full set of figures
	_barracks.pushBack(createFigure(Type::KING, Color::WHITE));
	_barracks.pushBack(createFigure(Type::QUEEN, Color::WHITE));
	_barracks.pushBack(createFigure(Type::QUEEN, Color::WHITE)); // additional queen for promotion
	_barracks.pushBack(createFigure(Type::BISHOP, Color::WHITE));
	_barracks.pushBack(createFigure(Type::BISHOP, Color::WHITE));
	_barracks.pushBack(createFigure(Type::KNIGHT, Color::WHITE));
	_barracks.pushBack(createFigure(Type::KNIGHT, Color::WHITE));
	_barracks.pushBack(createFigure(Type::ROOK, Color::WHITE));
	_barracks.pushBack(createFigure(Type::ROOK, Color::WHITE));
	
	_barracks.pushBack(createFigure(Type::KING, Color::BLACK));
	_barracks.pushBack(createFigure(Type::QUEEN, Color::BLACK));
	_barracks.pushBack(createFigure(Type::QUEEN, Color::BLACK)); // additional queen for promotion
	_barracks.pushBack(createFigure(Type::BISHOP, Color::BLACK));
	_barracks.pushBack(createFigure(Type::BISHOP, Color::BLACK));
	_barracks.pushBack(createFigure(Type::KNIGHT, Color::BLACK));
	_barracks.pushBack(createFigure(Type::KNIGHT, Color::BLACK));
	_barracks.pushBack(createFigure(Type::ROOK, Color::BLACK));
	_barracks.pushBack(createFigure(Type::ROOK, Color::BLACK));

	for (int i = 0; i < BOARD_SIZE; ++i) {
		_barracks.pushBack(createFigure(Type::PAWN, Color::WHITE));
		_barracks.pushBack(createFigure(Type::PAWN, Color::BLACK));
	}

	return true;
}

Figure* FiguresPool::createFigure(Type figureType, Color figureColor, Location location)
{
	switch (figureType) {
	case Type::KING:
		return F_King::createFigure(figureColor, location);;
		break;
	case Type::QUEEN:
		return F_Queen::createFigure(figureColor, location);;
		break;
	case Type::BISHOP:
		return F_Bishop::createFigure(figureColor, location);;
		break;
	case Type::KNIGHT:
		return F_Knight::createFigure(figureColor, location);;
		break;
	case Type::ROOK:
		return F_Rook::createFigure(figureColor, location);;
		break;
	case Type::PAWN:
		return F_Pawn::createFigure(figureColor, location);;
		break;
	default:
		return nullptr;
		break;
	}
}

Figure* FiguresPool::getFigure(Type figureType, Color figureColor, Location location)
{
	std::string name;
	name += static_cast<char>(figureColor);
	name += static_cast<char>(figureType);

	auto  result = std::find_if(_barracks.begin(), _barracks.end(), [&name](const Figure* figure) {
		return figure->getFigureName() == name;
	});

	if (result != _barracks.end()) {
		auto figure = *result;
		
		figure->retain();
		_barracks.eraseObject(figure);

		figure->setLocation(location);
		figure->setPosition(static_cast<float>(BOARD_X + location.y * SQUARE_SIZE),
			static_cast<float>(BOARD_Y + location.x * SQUARE_SIZE));
		
		return figure;
	}

	return createFigure(figureType, figureColor, location);
}

void FiguresPool::putFigure(Figure* figure)
{
	figure->_firstMove = true;
	_barracks.pushBack(figure);
}

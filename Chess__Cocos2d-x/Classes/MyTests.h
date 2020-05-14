#pragma once

#include "cocos2d.h"
#include <iostream>

#include "Specification.h"
#include "Core.h"
#include "Figure.h"
#include "Units.h"


class MyTests {
private:
// attributes
	Core* _core = Core::sharedCore();
// methods
	bool TestIsCheck();
	bool TestIsCheckmate();
	bool TestIsDraw();
	bool TestСastling();
	bool TestEnPassant();
	bool TestIsKingInDanger();
public:
// methods
	void runCoreTests();
};
#include "BoardDirection.h"
#include <sstream>
#include <iostream>
#include <string>

BoardDirection::BoardDirection()
	: mRowChange(0), mColChange(0) {
}

BoardDirection::BoardDirection(int rowChange, int colChange)
	: mRowChange(rowChange), mColChange(colChange) {
}

std::array<BoardDirection, 8> BoardDirection::CARDINAL_DIRECTIONS =
{ BoardDirection {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };


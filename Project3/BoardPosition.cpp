#include "BoardPosition.h"
#include "BoardDirection.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "OthelloMove.h"

BoardPosition::BoardPosition()
	: mRow(0), mCol(0) {
}

BoardPosition::BoardPosition(int row, int col)
	: mRow(row), mCol(col) {
}

BoardPosition::operator std::string() const {
	std::ostringstream os;
	os << "(" << mRow << "," << mCol << ")";
	return os.str();
}

bool BoardPosition::operator==(BoardPosition rhs) {
	return ((mRow == rhs.mRow) && (mCol == rhs.mCol));
}

bool BoardPosition::operator<(BoardPosition rhs) {
	if (mRow == rhs.mRow) {
		return mCol < rhs.mCol;
	}
	else {
		return (mRow < rhs.mRow);
	}
}

bool BoardPosition::InBounds(int boardSize) {
	return (mRow >= 0 && mRow < boardSize) && (mCol >= 0 && mCol < boardSize);
}

bool BoardPosition::InBounds(int rows, int columns) {
	return (mRow >= 0 && mRow < rows) && (mCol >= 0 && mCol < columns);
}

// Returns a vector with all possible rectangular positions on the board
std::vector<BoardPosition> BoardPosition::GetRectangularPositions(int rows, int columns) {
	std::vector<BoardPosition> rectangularPositions;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			BoardPosition b = BoardPosition{ i, j };
			rectangularPositions.push_back(b);
		}
	}

	return rectangularPositions;
}

BoardPosition BoardPosition::operator+(BoardDirection dir) {
	return BoardPosition(mRow + (int)dir.GetRowChange(), mCol + (int)dir.GetColChange());
}

std::istream& operator>>(std::istream &lhs, BoardPosition& rhs) {
	char parenthesis, comma;
	lhs >> parenthesis >> rhs.mRow >> comma >> rhs.mCol >> parenthesis;
	return lhs;
}

std::ostream& operator<<(std::ostream &lhs, BoardPosition rhs) {
	lhs << "(" << rhs.GetRow() << "," << rhs.GetCol() << ")";
	return lhs;
}
#pragma once
#include "BoardDirection.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

class BoardPosition {
private:
	int mRow, mCol;

public:
	BoardPosition();
	BoardPosition(int row, int col);

	inline int GetRow() const {
		return mRow;
	}

	inline int GetCol() const {
		return mCol;
	}

	//Checks if in game board boundaries
	bool InBounds(int boardSize);

	//Checks if in game board boundaries given a row and column
	bool InBounds(int rows, int columns);

	//Gets all possible rectangular positions on a board
	static std::vector<BoardPosition> GetRectangularPositions(int rows, int columns);

	operator std::string() const;

	bool operator==(BoardPosition rhs);

	bool operator<(BoardPosition rhs);

	BoardPosition operator+(BoardDirection dir);

	friend std::istream& operator>>(std::istream &lhs, BoardPosition& rhs);
};

std::ostream& operator<<(std::ostream &lhs, BoardPosition rhs);

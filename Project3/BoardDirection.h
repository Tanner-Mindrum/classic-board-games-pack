#pragma once
#include <array>


class BoardDirection {
private:
	int mRowChange, mColChange;

public:
	BoardDirection();
	BoardDirection(int rowChange, int colChange);

	inline int GetRowChange() const {
		return mRowChange;
	}

	inline int GetColChange() const {
		return mColChange;
	}

	static std::array<BoardDirection, 8> CARDINAL_DIRECTIONS;
};


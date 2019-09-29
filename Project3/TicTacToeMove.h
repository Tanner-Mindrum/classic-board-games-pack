#pragma once
#include <string>
#include <vector>
#include "BoardPosition.h"
#include "BoardDirection.h"
#include "TicTacToeMove.h"
#include "GameMove.h"


class TicTacToeMove : public GameMove {
private:
	BoardPosition mPosition;

	friend class TicTacToeBoard;

public:
	// Default constructor: initializes this move as a PASS.
	TicTacToeMove() : mPosition(0, 0) {

	}
	/*
	1-parameter constructor: initializes this move with the given position.
	*/
	TicTacToeMove(BoardPosition p) : mPosition(p) {

	}

	
	virtual bool operator==(const GameMove &rhs) const override;


	virtual operator std::string() const override;

};



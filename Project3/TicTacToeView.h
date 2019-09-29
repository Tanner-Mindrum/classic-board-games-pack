#pragma once
#include "TicTacToeBoard.h"
#include "GameView.h"
#include <memory>
#include <iostream>


class TicTacToeView : public GameView {
private:
	std::shared_ptr<TicTacToeBoard> mTicTacToeBoard;

	void PrintBoard(std::ostream &s) const override;

public:
	std::string GetPlayerString(int player) const override;


	TicTacToeView(std::shared_ptr<TicTacToeBoard> b)
		: mTicTacToeBoard(b) {
	}

	std::unique_ptr<GameMove> ParseMove(const std::string & move) const override;
};

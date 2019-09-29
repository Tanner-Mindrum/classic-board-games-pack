#include "TicTacToeBoard.h"
#include "TicTacToeMove.h"
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

TicTacToeBoard::TicTacToeBoard() : mBoard({Player::EMPTY}), mCurrentPlayer(Player::X), mValue(0) {
}

void TicTacToeBoard::CheckForWinner() {
	// It would be most efficient if we only checked squares adjacent to the most 
	// recent move. But I'm lazy. We'll check every possible direction of four squares
	// in a row. Only the current player can be the winner, so we'll only look for those squares.
	for (auto pos : BoardPosition::GetRectangularPositions(mBoard.size(), mBoard[0].size())) {
		for (auto dir : BoardDirection::CARDINAL_DIRECTIONS) {
			// Having chosen a square and a direction, walk up to 4 steps in that direction.
			BoardPosition current = pos;
			bool threeInARow = true;

			for (int steps = 0; steps < 3; steps++) {
				if (!InBounds(current) || mCurrentPlayer != GetPlayerAtPosition(current)) {
					// We either walked out of bounds, or found a square that doesn't match current player.
					threeInARow = false;
					break;
				}
				current = current + dir;
			}

			// If we matched four in a row, set the current value to the current player, indicating
			// a winner.
			if (threeInARow) {
				mValue = static_cast<int>(mCurrentPlayer);
				return;
			}
		}
	}
}

std::vector<std::unique_ptr<GameMove>> TicTacToeBoard::GetPossibleMoves() const {
	vector<unique_ptr<GameMove>> moves;
	for (int i = 0; i < mBoard.size(); i++) {
		for (int j = 0; j < mBoard.size(); j++) {
			if (mBoard[i][j] == Player::EMPTY) {
				moves.push_back(std::make_unique<TicTacToeMove>(BoardPosition{ i, j }));
			}
		}
	}
	return moves;
}

void TicTacToeBoard::ApplyMove(std::unique_ptr<GameMove> move) {
	TicTacToeMove *m = dynamic_cast<TicTacToeMove*>(move.get());

	mBoard[m->mPosition.GetRow()][m->mPosition.GetCol()] = mCurrentPlayer;

	CheckForWinner();

	mHistory.push_back(std::move(move));
	mCurrentPlayer = mCurrentPlayer == Player::X ? Player::O : Player::X;

}

void TicTacToeBoard::UndoLastMove() {
	TicTacToeMove *m = dynamic_cast<TicTacToeMove*>(mHistory.back().get());

	cout << m->mPosition.GetRow() << "," << m->mPosition.GetCol() << endl;

	mBoard[m->mPosition.GetRow()][m->mPosition.GetCol()] = Player::EMPTY;

	mHistory.pop_back();

	mCurrentPlayer = mCurrentPlayer == Player::X ? Player::O : Player::X;
}

bool TicTacToeBoard::IsFinished() const {
	return mValue != 0 || mHistory.size() == mBoard.size() * mBoard[0].size();
}

int TicTacToeBoard::GetCurrentPlayer() const {
	return mCurrentPlayer == Player::X ? 1 : 2;
}

const std::vector<std::unique_ptr<GameMove>>& TicTacToeBoard::GetMoveHistory() const {
	return mHistory;
}

int TicTacToeBoard::GetValue() const {
	return mValue;
}


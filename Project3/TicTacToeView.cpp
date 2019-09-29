#include "TicTacToeView.h"

using namespace std;

void TicTacToeView::PrintBoard(std::ostream & s) const {
	s << endl << "- 0 1 2" << " " << endl;
	for (int i = 0; i < mTicTacToeBoard->mBoard.size(); i++) {
		s << i << " ";
		for (int j = 0; j < mTicTacToeBoard->mBoard.size(); j++) {
			if ((int)mTicTacToeBoard->mBoard[i][j] == 0) {
				s << '.' << " ";
			}
			if ((int)mTicTacToeBoard->mBoard[i][j] == 1) {
				s << 'X' << " ";
			}
			if ((int)mTicTacToeBoard->mBoard[i][j] == -1) {
				s << 'O' << " ";
			}
		}
		s << endl;
	}
}

std::string TicTacToeView::GetPlayerString(int player) const {
	return player == 1 ? "X" : "O";
}

std::unique_ptr<GameMove> TicTacToeView::ParseMove(const std::string & move) const {
	istringstream moveFormat{ move };
	char parenthesis, comma;
	int row, col;
	moveFormat >> parenthesis >> row >> comma >> col >> parenthesis;
	BoardPosition position(row, col);
	auto aMove = std::make_unique<TicTacToeMove>(position);
	return std::move(aMove);
}

std::ostream & operator<<(std::ostream & lhs, const TicTacToeMove & rhs) {
	return lhs << static_cast<string> (rhs);
}

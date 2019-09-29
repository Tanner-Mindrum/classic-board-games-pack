#include "OthelloView.h"
#include "OthelloBoard.h"
#include "OthelloMove.h"
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

void OthelloView::PrintBoard(std::ostream & s) const {
	s << endl << "- 0 1 2 3 4 5 6 7" << " " << endl;
	for (int i = 0; i < mOthelloBoard->mBoard.size(); i++) {
		s << i << " ";
		for (int j = 0; j < mOthelloBoard->mBoard.size(); j++) {
			if ((int)mOthelloBoard->mBoard[i][j] == 0) {
				s << '.' << " ";
			}
			if ((int)mOthelloBoard->mBoard[i][j] == 1) {
				s << 'B' << " ";
			}
			if ((int)mOthelloBoard->mBoard[i][j] == -1) {
				s << 'W' << " ";
			}
		}
		s << endl;
	}
}

std::string OthelloView::GetPlayerString(int player) const {
	return player == 1 ? "Black" : "White";
}

std::unique_ptr<GameMove> OthelloView::ParseMove(const std::string & move) const {

	istringstream moveFormat{ move };
	char parenthesis, comma;
	int row, col;

	moveFormat >> parenthesis >> row >> comma >> col >> parenthesis;
	BoardPosition position(row, col);
	auto aMove = std::make_unique<OthelloMove>(position);

	if (aMove->IsPass() || move == "pass") {
		aMove = std::make_unique<OthelloMove>(BoardPosition{-1, -1});
	}

	return std::move(aMove);
}

std::ostream & operator<<(std::ostream & lhs, const OthelloMove & rhs) {
	return lhs << static_cast<string> (rhs);
}

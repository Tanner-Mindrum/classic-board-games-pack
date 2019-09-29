#include "OthelloBoard.h"
#include "BoardDirection.h"
#include "OthelloMove.h"
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

OthelloBoard::OthelloBoard()
	: mValue(0), mCurrentPlayer(Player::WHITE) {

	// Begins game board with BWBW pieces in the center of the board and every other position is empty
	for (int i = 0; i < mBoard.size(); i++) {
		for (int j = 0; j < mBoard.size(); j++) {
			mBoard[i][j] = Player::EMPTY;
		}
	}
	mBoard[3][3] = Player::WHITE, mBoard[3][4] = Player::BLACK, mBoard[4][3] = Player::BLACK, mBoard[4][4] =
		Player::WHITE;
}

/* Gets all possible moves by scanning all eight cardinal directions of the board. A valid position is
   considered to be one where a player will be able to flip an enemy piece and is not currently taken by an enemy.
*/
std::vector<std::unique_ptr<GameMove>> OthelloBoard::GetPossibleMoves() const {

	std::vector<std::unique_ptr<GameMove>> possibleMoves;

	for (int i = 0; i < mBoard.size(); i++) {
		for (int j = 0; j < mBoard.size(); j++) {
			if (mBoard[i][j] == Player::EMPTY) {

				int duplicateCount = 0;

				for (BoardDirection d : BoardDirection::CARDINAL_DIRECTIONS) {

					BoardPosition p = BoardPosition{ i , j };
					p = p + d;

					if ((InBounds(p)) && GetPlayerAtPosition(p) == Player::EMPTY) {
						continue;
					}

					while ((InBounds(p)) && GetPlayerAtPosition(p) != (Player)-((int)mCurrentPlayer)
						&& GetPlayerAtPosition(p) != Player::EMPTY) {
						p = BoardPosition{ p.GetRow() + d.GetRowChange(), p.GetCol() + d.GetColChange() };

						if (InBounds(p) && GetPlayerAtPosition(p) == (Player)-((int)mCurrentPlayer) &&
							mBoard[p.GetRow() - d.GetRowChange()][p.GetCol() - d.GetColChange()] == mCurrentPlayer
							&& duplicateCount == 0) {
							possibleMoves.push_back(std::make_unique<OthelloMove>(BoardPosition{ i, j }));
							duplicateCount++;
						}
					}
				}
			}
		}
	}
	if (possibleMoves.size() == 0) {
		possibleMoves.push_back(make_unique<OthelloMove>(BoardPosition{ -1, -1 }));
	}

	return possibleMoves;
}

/* 
   Applies moves by scanning all eight cardinal directions of the board. At each cardinal direction, walk in
   that position until an enemy is found. Once found, walk in reverse back to the original position of the piece and
   flip all pieces along the way
*/
void OthelloBoard::ApplyMove(std::unique_ptr<GameMove> move) {

	OthelloMove *m = dynamic_cast<OthelloMove*>(move.get());
	mCurrentPlayer = (Player)-((int)mCurrentPlayer);

	if (m->mPosition.GetRow() != -1 && m->mPosition.GetCol() != -1) {
		mBoard[m->mPosition.GetRow()][m->mPosition.GetCol()] = mCurrentPlayer;

		((int)mCurrentPlayer > 0 ? mValue++ : mValue--);

		for (BoardDirection d : BoardDirection::CARDINAL_DIRECTIONS) {
			int enemyCounter = 0;
			BoardPosition p = m->mPosition;

			p = p + d;

			while (InBounds(p) && GetPlayerAtPosition(p) != mCurrentPlayer &&
				GetPlayerAtPosition(p) != Player::EMPTY) {
				enemyCounter++;
				p = p + d;
			}

			if (InBounds(p) && enemyCounter != 0 && GetPlayerAtPosition(p) == mCurrentPlayer) {
				for (int j = 1; j <= enemyCounter + 1; j++) {
					mBoard[m->mPosition.GetRow() + (d.GetRowChange() * j)][m->mPosition.GetCol() +
						(d.GetColChange() * j)] = mCurrentPlayer;
					(j != enemyCounter) ? mValue += (int)mBoard[m->mPosition.GetRow() + (d.GetRowChange() * j)]
						[m->mPosition.GetCol() + (d.GetColChange() * j)] :
						mValue += enemyCounter * (int)mCurrentPlayer;
				}
				m->AddFlipSet({ (char)enemyCounter, d });
			}
		}
	}
	mHistory.push_back(std::move(move));
}


void OthelloBoard::UndoLastMove() {
	int flipCount = 0;
	OthelloMove *m = dynamic_cast<OthelloMove*>(mHistory.back().get());

	for (vector<OthelloMove::FlipSet>::iterator itr = m->mFlips.begin(); itr != m->mFlips.end(); itr++) {
		BoardPosition p = m->mPosition;

		mBoard[p.GetRow()][p.GetCol()] = Player::EMPTY;

		for (int i = 0; i < (int)m->mFlips[itr - m->mFlips.begin()].mFlipCount; i++) {
			flipCount++;
			p = BoardPosition{ p.GetRow() + m->mFlips[itr - m->mFlips.begin()].mDirection.GetRowChange(),
				p.GetCol() + m->mFlips[itr - m->mFlips.begin()].mDirection.GetColChange() };
			mBoard[p.GetRow()][p.GetCol()] = (Player)-((int)mCurrentPlayer);
		}
	}

	mHistory.pop_back();

	((int)mCurrentPlayer > 0 ? mValue -= flipCount * 2 + 1 : mValue += flipCount * 2 + 1);

	mCurrentPlayer = (Player)-((int)mCurrentPlayer);
}

// The game is finished if two players have passed their turn.
bool OthelloBoard::IsFinished() const {

	if (mHistory.size() > 2) {
		OthelloMove *m = dynamic_cast<OthelloMove*>(mHistory.back().get());
		OthelloMove *n = dynamic_cast<OthelloMove*>(mHistory[mHistory.size() - 2].get());

		return m->IsPass()
			&& n->IsPass();
	}
	else {
		return false;
	}
}

int OthelloBoard::GetCurrentPlayer() const {
	return mCurrentPlayer == Player::BLACK ? 1 : 2;
}

const std::vector<std::unique_ptr<GameMove>>& OthelloBoard::GetMoveHistory() const {
	return mHistory;
}

int OthelloBoard::GetValue() const {
	return mValue;
}

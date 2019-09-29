#include "TicTacToeMove.h"
#include <sstream>

bool TicTacToeMove::operator==(const GameMove & rhs) const {
	const TicTacToeMove &m = dynamic_cast<const TicTacToeMove&>(rhs);
	return ((mPosition.GetRow() == m.mPosition.GetRow()) && (mPosition.GetCol() == m.mPosition.GetCol()));
}

TicTacToeMove::operator std::string() const {
	std::ostringstream os;

	os << "(" << mPosition.GetRow() << "," << mPosition.GetCol() << ")";

	return os.str();
}

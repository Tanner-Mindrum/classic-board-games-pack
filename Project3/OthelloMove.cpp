#include "OthelloMove.h"
#include <sstream>

bool OthelloMove::operator==(const GameMove &rhs) const {
	const OthelloMove &m = dynamic_cast<const OthelloMove&>(rhs);
	return ((mPosition.GetRow() == m.mPosition.GetRow()) && (mPosition.GetCol() == m.mPosition.GetCol()));
}

OthelloMove::operator std::string() const {
	std::ostringstream os;
	if (IsPass()) {
		os << "pass";
	}
	else {
		os << "(" << mPosition.GetRow() << "," << mPosition.GetCol() << ")";
	}

	return os.str();
}
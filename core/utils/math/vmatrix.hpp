#pragma once
#include "vector.hpp"

class vmatrix {
private:
	vector m[4][4];

public:
	const matrix3x4& As3x4() const {
		return *((const matrix3x4*)this);
	}
};

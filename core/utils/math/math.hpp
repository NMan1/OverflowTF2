#pragma once
#include "vector.hpp"

typedef float matrix3x4[3][4];

namespace math {
	void vector_transform(const vector& input, const matrix3x4& matrix, vector& output);

	void sin_cos(float radians, float* sine, float* cosine);

	void angle_vectors(const vector& angles, vector* forward);

	vector calc_angle(const vector& source, const vector& destination);

	float calc_fov(const vector& src, const vector& dst);

	float normalize_angle(float ang);

	void clamp_angles(vector& v);
}
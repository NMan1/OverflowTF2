#define NOMINMAX
#include <algorithm>
#include <wtypes.h>
#include "math.hpp"

#define M_RADPI		57.295779513082
#define PI			3.14159265358979323846

namespace math {
	void vector_transform(const vector& input, const matrix3x4& matrix, vector& output) {
		for (auto i = 0; i < 3; i++)
			output[i] = input.dot((vector&)matrix[i]) + matrix[i][3];
	}

	void sin_cos(float radians, float* sine, float* cosine) {
		_asm
		{
			fld		DWORD PTR[radians]
			fsincos

			mov edx, DWORD PTR[cosine]
			mov eax, DWORD PTR[sine]

			fstp DWORD PTR[edx]
			fstp DWORD PTR[eax]
		}
	}

	void angle_vectors(const vector& angles, vector* forward) {
		float sp, sy, cp, cy;

		sin_cos(DEG2RAD(angles.x), &sp, &cp);
		sin_cos(DEG2RAD(angles.y), &sy, &cy);

		if (forward)
		{
			forward->x = cp * cy;
			forward->y = cp * sy;
			forward->z = -sp;
		}
	}

	vector calc_angle(const vector& source, const vector& destination) {
		vector angles = vector(0.0f, 0.0f, 0.0f);
		vector delta = (source - destination);
		float fHyp = FastSqrt((delta.x * delta.x) + (delta.y * delta.y));

		angles.x = (atanf(delta.z / fHyp) * M_RADPI);
		angles.y = (atanf(delta.y / delta.x) * M_RADPI);
		angles.z = 0.0f;

		if (delta.x >= 0.0f)
			angles.y += 180.0f;

		return angles;
	}

	float calc_fov(const vector& src, const vector& dst) {
		vector v_src;
		angle_vectors(src, &v_src);

		vector v_dst = vector();
		angle_vectors(dst, &v_dst);

		float result = RAD2DEG(acos(v_dst.dot(v_src) / v_dst.length_2d_sqr()));

		if (!isfinite(result) || isinf(result) || isnan(result))
			result = 0.0f;

		return result;
	}

	float normalize_angle(float ang)
	{
		if (!std::isfinite(ang))
			return 0.0f;

		return std::remainder(ang, 360.0f);
	}

	void clamp_angles(vector& v) {
		v.x = std::max(-89.0f, std::min(89.0f, normalize_angle(v.x)));
		v.y = normalize_angle(v.y);
		v.z = 0.0f;
	}
}
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

	vector calc_angle(const vector& source, const vector& destination, const vector& view_angles) {
		vector delta = source - destination;
		auto radians_to_degrees = [](float radians) { return radians * 180 / static_cast<float>(M_PI); };
		vector angles;
		angles.x = radians_to_degrees(atanf(delta.z / std::hypotf(delta.x, delta.y))) - view_angles.x;
		angles.y = radians_to_degrees(atanf(delta.y / delta.x)) - view_angles.y;
		angles.z = 0.0f;

		if (delta.x >= 0.0)
			angles.y += 180.0f;

		// normalize
		angles.x = std::isfinite(angles.x) ? std::remainderf(angles.x, 360.0f) : 0.0f;
		angles.y = std::isfinite(angles.y) ? std::remainderf(angles.y, 360.0f) : 0.0f;
		angles.z = 0.0f;

		return angles;
	}
	
	vector calc_angle_projectile(const vector& source, const vector& destination) {
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

	float calc_fov(float distance, const vector& current_view_angles, const vector& angle_to_enemy) {
		vector aiming_at = {};
		math::angle_vectors(current_view_angles, &aiming_at);
		aiming_at *= distance;

		vector aim_to = {};
		math::angle_vectors(angle_to_enemy, &aim_to);
		aim_to *= distance;

		return aiming_at.dist_to(aim_to);
	}

	void normalize_angle(vector& angle)
	{
		while (angle.x > 89.f)
		{
			angle.x -= 180.f;
		}
		while (angle.x < -89.f)
		{
			angle.x += 180.f;
		}
		if (angle.y > 180)
		{
			angle.y -= (round(angle.y / 360) * 360.f);
		}
		else if (angle.y < -180)
		{
			angle.y += (round(angle.y / 360) * -360.f);
		}
		if ((angle.z > 50) || (angle.z < 50))
		{
			angle.z = 0;
		}
	}

	inline float normalize_clamp(float ang) {
		if (!std::isfinite(ang))
			return 0.0f;

		return std::remainder(ang, 360.0f);
	}

	void clamp_angles(vector& v) {
		v.x = std::max(-89.0f, std::min(89.0f, normalize_clamp(v.x)));
		v.y = normalize_clamp(v.y);
		v.z = 0.0f;
	}
}
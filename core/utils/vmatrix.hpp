#pragma once
#include "vector.hpp"

class matrix3x4_t
{
public:
	matrix3x4_t() {}
	matrix3x4_t(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23)
	{
		flMatVal[0][0] = m00;	flMatVal[0][1] = m01; flMatVal[0][2] = m02; flMatVal[0][3] = m03;
		flMatVal[1][0] = m10;	flMatVal[1][1] = m11; flMatVal[1][2] = m12; flMatVal[1][3] = m13;
		flMatVal[2][0] = m20;	flMatVal[2][1] = m21; flMatVal[2][2] = m22; flMatVal[2][3] = m23;
	}
	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	void init(const vector& xAxis, const vector& yAxis, const vector& zAxis, const vector& vecOrigin)
	{
		flMatVal[0][0] = xAxis.x; flMatVal[0][1] = yAxis.x; flMatVal[0][2] = zAxis.x; flMatVal[0][3] = vecOrigin.x;
		flMatVal[1][0] = xAxis.y; flMatVal[1][1] = yAxis.y; flMatVal[1][2] = zAxis.y; flMatVal[1][3] = vecOrigin.y;
		flMatVal[2][0] = xAxis.z; flMatVal[2][1] = yAxis.z; flMatVal[2][2] = zAxis.z; flMatVal[2][3] = vecOrigin.z;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	matrix3x4_t(const vector& xAxis, const vector& yAxis, const vector& zAxis, const vector& vecOrigin)
	{
		init(xAxis, yAxis, zAxis, vecOrigin);
	}

	inline void set_origin(vector const& p)
	{
		flMatVal[0][3] = p.x;
		flMatVal[1][3] = p.y;
		flMatVal[2][3] = p.z;
	}

	inline void invalidate(void)
	{
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++) {
				flMatVal[i][j] = std::numeric_limits<float>::infinity();;
			}
		}
	}

	float* operator[](int i) { return flMatVal[i]; }
	const float* operator[](int i) const { return flMatVal[i]; }
	float* base() { return &flMatVal[0][0]; }
	const float* base() const { return &flMatVal[0][0]; }

	float flMatVal[3][4];
};

class v_matrix
{
public:

	v_matrix();
	v_matrix(
		vec_t m00, vec_t m01, vec_t m02, vec_t m03,
		vec_t m10, vec_t m11, vec_t m12, vec_t m13,
		vec_t m20, vec_t m21, vec_t m22, vec_t m23,
		vec_t m30, vec_t m31, vec_t m32, vec_t m33
	);

	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	v_matrix(const vector& forward, const vector& left, const vector& up);

	// Construct from a 3x4 matrix
	v_matrix(const matrix3x4_t& matrix3x4);

	// Set the values in the matrix.
	void		init(
		vec_t m00, vec_t m01, vec_t m02, vec_t m03,
		vec_t m10, vec_t m11, vec_t m12, vec_t m13,
		vec_t m20, vec_t m21, vec_t m22, vec_t m23,
		vec_t m30, vec_t m31, vec_t m32, vec_t m33
	);


	// Initialize from a 3x4
	void		init(const matrix3x4_t& matrix3x4);

	// array access
	inline float* operator[](int i)
	{
		return m[i];
	}

	inline const float* operator[](int i) const
	{
		return m[i];
	}

	// Get a pointer to m[0][0]
	inline float* base()
	{
		return &m[0][0];
	}

	inline const float* base() const
	{
		return &m[0][0];
	}

	void		set_left(const vector& vLeft);
	void		set_up(const vector& vUp);
	void		set_forward(const vector& vForward);

	void		get_basisvectors(vector& vForward, vector& vLeft, vector& vUp) const;
	void		set_basisvectors(const vector& vForward, const vector& vLeft, const vector& vUp);

	// Get/set the translation.
	vector&		get_translation(vector& vTrans) const;
	void		set_translation(const vector& vTrans);

	void		pre_translate(const vector& vTrans);
	void		post_translate(const vector& vTrans);

	matrix3x4_t& As3x4();
	const matrix3x4_t& As3x4() const;
	void		copy_from3x4(const matrix3x4_t& m3x4);
	void		set3x4(matrix3x4_t& matrix3x4) const;

	bool		operator==(const v_matrix& src) const;
	bool		operator!=(const v_matrix& src) const { return !(*this == src); }

	// Access the basis vectors.
	vector		get_left() const;
	vector		get_up() const;
	vector		get_forward() const;
	vector		get_translation() const;


	// Matrix->vector operations.
public:
	// Multiply by a 3D vector (same as operator*).
	void		V3Mul(const vector& vIn, vector& vOut) const;

	// Multiply by a 4D vector.
	//void		V4Mul( const vector4D &vIn, vector4D &vOut ) const;

	// Applies the rotation (ignores translation in the matrix). (This just calls VMul3x3).
	vector		apply_rotation(const vector& vVec) const;

	// Multiply by a vector (divides by w, assumes input w is 1).
	vector		operator*(const vector& vVec) const;

	// Multiply by the upper 3x3 part of the matrix (ie: only apply rotation).
	vector		VMul3x3(const vector& vVec) const;

	// Apply the inverse (transposed) rotation (only works on pure rotation matrix)
	vector		VMul3x3Transpose(const vector& vVec) const;

	// Multiply by the upper 3 rows.
	vector		VMul4x3(const vector& vVec) const;

	// Apply the inverse (transposed) transformation (only works on pure rotation/translation)
	vector		VMul4x3Transpose(const vector& vVec) const;


	// Matrix->plane operations.
	//public:
	// Transform the plane. The matrix can only contain translation and rotation.
	//void		TransformPlane( const VPlane &inPlane, VPlane &outPlane ) const;

	// Just calls TransformPlane and returns the result.
	//VPlane		operator*(const VPlane &thePlane) const;

	// Matrix->matrix operations.
public:

	v_matrix& operator=(const v_matrix& mOther);

	// Multiply two matrices (out = this * vm).
	void		MatrixMul(const v_matrix& vm, v_matrix& out) const;

	// Add two matrices.
	const v_matrix& operator+=(const v_matrix& other);

	// Just calls MatrixMul and returns the result.	
	v_matrix		operator*(const v_matrix& mOther) const;

	// Add/Subtract two matrices.
	v_matrix		operator+(const v_matrix& other) const;
	v_matrix		operator-(const v_matrix& other) const;

	// Negation.
	v_matrix		operator-() const;

	// Return inverse matrix. Be careful because the results are undefined 
	// if the matrix doesn't have an inverse (ie: InverseGeneral returns false).
	v_matrix		operator~() const;

	// Matrix operations.
public:
	// Set to identity.
	void		identity();

	bool		is_identity() const;

	// Setup a matrix for origin and angles.
	void		setup_matrix_org_angles(const vector& origin, const QAngle& vAngles);

	// General inverse. This may fail so check the return!
	bool		inverse_general(v_matrix& vInverse) const;

	// Does a fast inverse, assuming the matrix only contains translation and rotation.
	void		inverse_tr(v_matrix& mRet) const;

	// Usually used for debug checks. Returns true if the upper 3x3 contains
	// unit vectors and they are all orthogonal.
	bool		is_rotation_matrix() const;

	// This calls the other InverseTR and returns the result.
	v_matrix		inverse_tr() const;

	// Get the scale of the matrix's basis vectors.
	vector		get_scale() const;

	// (Fast) multiply by a scaling matrix setup from vScale.
	v_matrix		scale(const vector& vScale);

	// Normalize the basis vectors.
	v_matrix		normalize_basis_vectors() const;

	// Transpose.
	v_matrix		transpose() const;

	// Transpose upper-left 3x3.
	v_matrix		transpose3x3() const;

public:
	// The matrix.
	vec_t		m[4][4];
};
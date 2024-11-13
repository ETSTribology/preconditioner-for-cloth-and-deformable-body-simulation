#pragma once

#include "SeVector.h"

#include <cmath>

#ifdef WIN32
#include <xmmintrin.h>
#endif


SE_NAMESPACE_BEGIN


#ifdef WIN32

template<typename Type> using SimdVector3 = SeVector<Type, SIMD_VEC3>;

template<> struct SeVector<float, SIMD_VEC3>
{
	static constexpr int Elements = 3;

	using value_type = float;

	union
	{
		struct { __m128 pack; };
		struct { float x, y, z, w; };
		struct { SeVector3<float> xyz; };
		struct { SeVector4<float> xyzw; };
	};

	SeVector() {}
	SeVector(const __m128 & p) : pack(p) {}
	explicit SeVector(float scalar) : pack(_mm_setr_ps(scalar, scalar, scalar, 0.0f)) {}	//pack(_mm_set_ps1(scalar)) {}
	SeVector(float s1, float s2, float s3) : pack(_mm_setr_ps(s1, s2, s3, 0.0f)) {}
	SeVector(float s1, float s2, float s3, float s4) : pack(_mm_setr_ps(s1, s2, s3, s4)) {}
	explicit SeVector(const SeVector<float, VEC3_XYZ> & vec) : pack(_mm_setr_ps(vec.x, vec.y, vec.z, 0.f)) {}

	void operator+=(const SeVector & a) { pack = _mm_add_ps(pack, a.pack); }
	void operator-=(const SeVector & a) { pack = _mm_sub_ps(pack, a.pack); }
	void operator*=(const SeVector & a) { pack = _mm_mul_ps(pack, a.pack); }
	void operator/=(const SeVector & a) { pack = _mm_div_ps(pack, a.pack); }

	void operator+=(const __m128 & a) { pack = _mm_add_ps(pack, a); }
	void operator-=(const __m128 & a) { pack = _mm_sub_ps(pack, a); }
	void operator*=(const __m128 & a) { pack = _mm_mul_ps(pack, a); }
	void operator/=(const __m128 & a) { pack = _mm_div_ps(pack, a); }

	void operator+=(float scalar) { pack = _mm_add_ps(pack, _mm_set_ps1(scalar)); }
	void operator-=(float scalar) { pack = _mm_sub_ps(pack, _mm_set_ps1(scalar)); }
	void operator*=(float scalar) { pack = _mm_mul_ps(pack, _mm_set_ps1(scalar)); }
	void operator/=(float scalar) { pack = _mm_div_ps(pack, _mm_set_ps1(scalar)); }

	SeVector operator+(const SeVector & a) const { return SeVector(_mm_add_ps(pack, a.pack)); }
	SeVector operator-(const SeVector & a) const { return SeVector(_mm_sub_ps(pack, a.pack)); }
	SeVector operator*(const SeVector & a) const { return SeVector(_mm_mul_ps(pack, a.pack)); }
	SeVector operator/(const SeVector & a) const { return SeVector(_mm_div_ps(pack, a.pack)); }

	SeVector operator+(const __m128 & a) const { return SeVector(_mm_add_ps(pack, a)); }
	SeVector operator-(const __m128 & a) const { return SeVector(_mm_sub_ps(pack, a)); }
	SeVector operator*(const __m128 & a) const { return SeVector(_mm_mul_ps(pack, a)); }
	SeVector operator/(const __m128 & a) const { return SeVector(_mm_div_ps(pack, a)); }

	SeVector operator+(float scalar) const { return SeVector(_mm_add_ps(pack, _mm_set_ps1(scalar))); }
	SeVector operator-(float scalar) const { return SeVector(_mm_sub_ps(pack, _mm_set_ps1(scalar))); }
	SeVector operator*(float scalar) const { return SeVector(_mm_mul_ps(pack, _mm_set_ps1(scalar))); }
	SeVector operator/(float scalar) const { return SeVector(_mm_div_ps(pack, _mm_set_ps1(scalar))); }

	friend SeVector operator+(float scalar, const SeVector & a) { return SeVector(_mm_add_ps(_mm_set_ps1(scalar), a.pack)); }
	friend SeVector operator-(float scalar, const SeVector & a) { return SeVector(_mm_sub_ps(_mm_set_ps1(scalar), a.pack)); }
	friend SeVector operator*(float scalar, const SeVector & a) { return SeVector(_mm_mul_ps(_mm_set_ps1(scalar), a.pack)); }
	friend SeVector operator/(float scalar, const SeVector & a) { return SeVector(_mm_div_ps(_mm_set_ps1(scalar), a.pack)); }

	const float & operator[](unsigned int i) const { SE_ASSERT(i < 4); return pack.m128_f32[i]; }
	float & operator[](unsigned int i) { SE_ASSERT(i < 4); return pack.m128_f32[i]; }
};


/*************************************************************************
****************************    Operators    *****************************
*************************************************************************/

template<typename Type> SE_INLINE bool operator==(const SimdVector3<Type> & a, const SimdVector3<Type> & b)
{
	for (int i = 0; i < SimdVector3<Type>::Elements; ++i)		{ if (a[i] != b[i])	return false; }			return true;
}
template<typename Type> SE_INLINE bool operator!=(const SimdVector3<Type> & a, const SimdVector3<Type> & b)
{
	for (int i = 0; i < SimdVector3<Type>::Elements; ++i)		{ if (a[i] != b[i])	return true; }			return false;
}
template<typename Type> SE_INLINE SimdVector3<Type> operator-(const SimdVector3<Type> & a)
{
	for (int i = 0; i < SimdVector3<Type>::Elements; ++i)		a[i] = -a[i];			return a;
}
template<typename Type> SE_INLINE SimdVector3<Type> operator!(const SimdVector3<Type> & a)
{
	for (int i = 0; i < SimdVector3<Type>::Elements; ++i)		a[i] = !a[i];			return a;
}
template<typename Type> SE_INLINE SimdVector3<Type> operator~(const SimdVector3<Type> & a)
{
	for (int i = 0; i < SimdVector3<Type>::Elements; ++i)		a[i] = ~a[i];			return a;
}

template<> SE_INLINE SimdVector3<float> operator - (const SimdVector3<float> & a)
{
	return _mm_xor_ps(a.pack, _mm_set1_ps(-0.f));
}

/*
template<> SE_INLINE SeVector<float, SIMD_VEC3> operator - (SeVector<float, SIMD_VEC3> a)
{
	return _mm_xor_ps(a.pack, _mm_set1_ps(-0.f));
}*/

#endif


/*************************************************************************
***************************    Type defines    ***************************
*************************************************************************/


using Simd3f = SimdVector3<float>;
template<typename Type> using SimdVector3 = SeVector<Type, SIMD_VEC3>;

using SeVec3fSimd = Simd3f;


SE_NAMESPACE_END

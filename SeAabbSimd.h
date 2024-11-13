#pragma once

#include "SeMathSimd.h"

#include "SeAabb.h"

#include <limits>

SE_NAMESPACE_BEGIN

/*************************************************************************
******************************    SeAabb    ******************************
*************************************************************************/

/**
 *	@brief		Axis-align Bounding Box.
 */

template<> struct SeAabb<Simd3f>
{

public:

	//!	@brief	Default constructor.
	SeAabb() : Lower(FLT_MAX), Upper(-FLT_MAX) {}

	//!	@brief	Constructed by a given point.
	SeAabb(const Simd3f & Point) : Lower(Point), Upper(Point) {}

	//!	@brief	Constructed by a paired points explicitly.
	explicit SeAabb(const Simd3f & P1, const Simd3f & P2) : Lower(Math::Min(P1, P2)), Upper(Math::Max(P1, P2)) {}

public:

	SeAabb operator+(const SeAabb & Other) const
	{
		return SeAabb(Math::Min(Lower, Other.Lower), Math::Max(Upper, Other.Upper));
	}

	SeAabb operator+(const Simd3f & Point) const
	{
		return SeAabb(Math::Min(Lower, Point), Math::Max(Upper, Point));
	}

	void operator += (const SeAabb & Other)
	{
		Lower = Math::Min(Lower, Other.Lower);		Upper = Math::Max(Upper, Other.Upper);
	}

	void operator += (const Simd3f & Point)
	{
		Lower = Math::Min(Lower, Point);		Upper = Math::Max(Upper, Point);
	}

	void Enlarge(float Amount)
	{
		Lower -= Amount;		Upper += Amount;
	}

	Simd3f Center() const
	{
		return Math::Average(Lower, Upper);
	}

	Simd3f Extent() const
	{
		return Upper - Lower;
	}

public:

	Simd3f Lower, Upper;
};



template<>
static SE_INLINE bool IsContain(const SeAabb<Simd3f>& aabb, const Simd3f& P) 
{ 
	return !((aabb.Upper.x < P.x) || (aabb.Upper.y < P.y) || (aabb.Upper.z < P.z) ||
			 (aabb.Lower.x > P.x) || (aabb.Lower.y > P.y) || (aabb.Lower.z > P.z));
}

template<> 
static SE_INLINE bool IsContain(const SeAabb<Simd3f>& aabb, const Simd3f& P, float radium)
{ 
	return !((aabb.Upper.x < P.x - radium) || (aabb.Upper.y < P.y - radium) || (aabb.Upper.z < P.z - radium) ||
		(aabb.Lower.x > P.x + radium) || (aabb.Lower.y > P.y + radium) || (aabb.Lower.z > P.z + radium));
}

template<>
static SE_INLINE bool IsOverlap(const SeAabb<Simd3f>& aabb, const SeAabb<Simd3f>& P)
{
	return !((aabb.Upper.x < P.Lower.x) || (aabb.Upper.y < P.Lower.y) || (aabb.Upper.z < P.Lower.z) ||
		(aabb.Lower.x > P.Upper.x) || (aabb.Lower.y > P.Upper.y) || (aabb.Lower.z > P.Upper.z));
}


template<>
static SE_INLINE bool IsIntersect(const SeAabb<Simd3f>& aabb, const Simd3f& Pa, const Simd3f& Pb) 
{
	Simd3f Dir = Simd3f(Pb - Pa);

	if (Dir.x == 0.0f)		Dir.x = 1e-6f;
	if (Dir.y == 0.0f)		Dir.y = 1e-6f;
	if (Dir.z == 0.0f)		Dir.z = 1e-6f;

	Simd3f invDir = 1.0f / Dir;
	Simd3f Left = Simd3f(aabb.Lower - Pa) * invDir;
	Simd3f Right = Simd3f(aabb.Upper - Pa) * invDir;

	Float2 T1 = Float2(Math::Min(Left.x, Right.x), Math::Max(Left.x, Right.x));
	Float2 T2 = Float2(Math::Min(Left.y, Right.y), Math::Max(Left.y, Right.y));
	Float2 T3 = Float2(Math::Min(Left.z, Right.z), Math::Max(Left.z, Right.z));

	float range0 = Math::Max(T1.x, T2.x, T3.x, 0.0f);
	float range1 = Math::Min(T1.y, T2.y, T3.y, 1.0f);

	return range0 < range1;
}

SE_NAMESPACE_END

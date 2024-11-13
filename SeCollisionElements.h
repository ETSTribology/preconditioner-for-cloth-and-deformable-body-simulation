#pragma once

#include "SeVectorSimd.h"

SE_NAMESPACE_BEGIN

struct EfSet
{
	int		m_eId;
	int		m_fId;
	float	stiff;
	Float3	m_bary;			// (x, 1-x) / (y, z, 1-y-z): barycentric weight of the intersection point
	SeVec3fSimd m_normal;	// repulsion direction
};

struct VfSet
{
	int		m_vId;
	int		m_fId;
	float	stiff;
	Float2	m_bary;			// (x, y, 1-x-y): barycentric weight of the vertex
	SeVec3fSimd m_normal;	// repulsion direction
};

struct EeSet
{
	int		m_eId0;
	int		m_eId1;
	float	stiff;
	Float2	m_bary;			// (x, 1-x) / (y, 1-y): barycentric weight of the two closest points
	SeVec3fSimd m_normal;	// repulsion direction
};

struct Stencil
{
	int verextNumPerStencil;
	int vertexNumOfFirstPrimitive;

	int		index[5];
	float	weight[5];
	float	stiff;
	SeVec3fSimd direction;
};

SE_NAMESPACE_END
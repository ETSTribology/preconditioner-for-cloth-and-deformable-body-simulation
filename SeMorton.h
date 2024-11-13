#pragma once

#include "SeMath.h"

SE_NAMESPACE_BEGIN

/*************************************************************************
****************************    SeMorton64    ****************************
*************************************************************************/

/**
 *	@brief	64-bit Morton-Code object.
 */
class SE_ALIGN(8) SeMorton64
{

public:

	using value_type = unsigned long long;

	//!	@brief	Default constructor.
	 SeMorton64() {}

	//!	@brief	Convert to vulue_type.
	 operator value_type() const { return m_Value; }

	//!	@brief	Constructed by a given value.
	 SeMorton64(value_type _Value) : m_Value(_Value) {}

	//!	@brief	Encoded by the given 3d point located within the unit cube (controlable precision).
	template<unsigned int precision>  void Encode(float x, float y, float z, value_type lastBits)
	{
		static_assert(precision <= 21, "The highest precision for 64-bit Morton code is 21.");

		x = Math::Clamp(x * (1ll << precision), 0.0f, (1ll << precision) - 1.0f);
		y = Math::Clamp(y * (1ll << precision), 0.0f, (1ll << precision) - 1.0f);
		z = Math::Clamp(z * (1ll << precision), 0.0f, (1ll << precision) - 1.0f);

		value_type xx = SeMorton64::ExpandBits(static_cast<value_type>(x)) << (66 - 3 * precision);
		value_type yy = SeMorton64::ExpandBits(static_cast<value_type>(y)) << (65 - 3 * precision);
		value_type zz = SeMorton64::ExpandBits(static_cast<value_type>(z)) << (64 - 3 * precision);

		constexpr value_type bitMask = ~value_type(0) >> (3 * precision);

		m_Value = xx + yy + zz + (lastBits & bitMask);
	}

	//!	@brief	Encoded by the given 3d point located within the unit cube (full precision).
	 void Encode(float x, float y, float z)
	{
		x = Math::Clamp(x * (1ll << 21), 0.0f, (1ll << 21) - 1.0f);
		y = Math::Clamp(y * (1ll << 21), 0.0f, (1ll << 21) - 1.0f);
		z = Math::Clamp(z * (1ll << 21), 0.0f, (1ll << 21) - 1.0f);

		value_type xx = SeMorton64::ExpandBits(static_cast<value_type>(x));
		value_type yy = SeMorton64::ExpandBits(static_cast<value_type>(y));
		value_type zz = SeMorton64::ExpandBits(static_cast<value_type>(z));

		m_Value = (xx << 2) + (yy << 1) + zz;
	}

private:

	/**
	 *	@brief	Expand bits by inserting two zeros after each bit.
	 *	@e.g.	0000 0000 1111  ->  0010 0100 1001
	 */
	static  value_type ExpandBits(value_type bits)
	{
		bits = (bits | (bits << 32)) & 0xFFFF00000000FFFFu;
		bits = (bits | (bits << 16)) & 0x00FF0000FF0000FFu;
		bits = (bits | (bits <<  8)) & 0xF00F00F00F00F00Fu;
		bits = (bits | (bits <<  4)) & 0x30C30C30C30C30C3u;
		return (bits | (bits <<  2)) & 0x9249249249249249u;
	}

private:

	value_type		m_Value;
};

SE_NAMESPACE_END
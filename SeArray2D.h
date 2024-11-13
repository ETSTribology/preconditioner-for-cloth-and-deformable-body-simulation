#pragma once

#include "SePreDefine.h"

SE_NAMESPACE_BEGIN

/*************************************************************************
****************************    SeArray2D    *****************************
*************************************************************************/

//!	@brief	��ά��������
template<typename Type> class SeArray2D
{

public:

	//!	@brief	Default constructor.
	SeArray2D() : m_Rows(0), m_Columns(0) {}

	//!	@brief	Construct and resize.
	explicit SeArray2D(size_t _Rows, size_t _Columns) : m_Rows(_Rows), m_Columns(_Columns), m_Values(_Rows * _Columns) {}

	//!	@brief	Construct, resize and memory set.
	explicit SeArray2D(size_t _Rows, size_t _Columns, Type _Value) : m_Rows(_Rows), m_Columns(_Columns), m_Values(_Rows * _Columns, _Value) {}

public:

	//! @brief  Data will be reserved in Column Major format
	void Resize(size_t _Rows, size_t _Columns)
	{
		m_Values.resize(_Rows * _Columns);

		m_Columns = _Columns;

		m_Rows = _Rows;
	}

	//! @brief  release spare memory
	void ShrinkToFit()
	{
		m_Values.shrink_to_fit();
	}

	//!	@brief	Fill data.
	void Memset(Type _Value, size_t _Begin = 0, size_t _End = SIZE_MAX)
	{
		_End = _End < m_Values.size() ? _End : m_Values.size();

		for (size_t i = _Begin; i < _End; ++i)
		{
			m_Values[i] = _Value;
		}
	}

	//!	@brief	Exchange context with right.
	void Swap(SeArray2D & _Right)
	{
		m_Values.swap(_Right.m_Values);

		SE_SWAP(m_Columns, _Right.m_Columns);

		SE_SWAP(m_Rows, _Right.m_Rows);
	}

	void Clear()
	{
		m_Values.clear();

		m_Values.shrink_to_fit();

		m_Rows = m_Columns = 0;
	}

public:

	const Type * operator[](size_t i) const { SE_ASSERT(i < m_Rows);  return &m_Values[m_Columns * i]; }

	Type * operator[](size_t i) { SE_ASSERT(i < m_Rows);  return &m_Values[m_Columns * i]; }

	const Type * Ptr() const { return m_Values.data(); }

	bool IsEmpty() const { return m_Values.empty(); }

	size_t Size() const { return m_Values.size(); }

	size_t Capacity() const { return m_Values.capacity(); }

	size_t Columns() const { return m_Columns; }

	size_t Rows() const { return m_Rows; }

	Type * Ptr() { return m_Values.data(); }

private:

	std::vector<Type> m_Values;

	size_t m_Rows, m_Columns;
};

SE_NAMESPACE_END
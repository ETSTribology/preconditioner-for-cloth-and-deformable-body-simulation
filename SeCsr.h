#pragma once

#include "SeOmp.h"
#include "SeArray2D.h"
#include "SeUtility.h"

SE_NAMESPACE_BEGIN

template<typename Type> class SeCompressSparseData
{
public:

	SeCompressSparseData() {}
	SeCompressSparseData(const std::vector<int>& starts, const std::vector<int>& idxs, const std::vector<Type>& values)
		:
		m_starts(starts),
		m_idxs(idxs),
		m_values(values)
	{}

	virtual ~SeCompressSparseData() {}

	void InitIdxs(const std::vector<std::vector<int>> & array2D)
	{
		Clear();

		int size = array2D.size();

		m_starts.resize(size + 1); Utility::MemsetZero(m_starts);

		for (int i = 0; i < size; ++i)
		{
			int num = array2D[i].size();

			m_starts[i + 1] = m_starts[i] + num;
		}

		m_idxs.resize(m_starts.back());

		OMP_PARALLEL_FOR

		for (int i = 0; i < size; ++i)
		{
			int num = array2D[i].size();
			std::memcpy(m_idxs.data() + m_starts[i], array2D[i].data(), sizeof(int) * num);
		}
	}

	void InitIdxs(const SeArray2D<int> & array2D, bool isRowMajor)
	{
		Clear();

		int DIM = isRowMajor ? array2D.Rows() : array2D.Columns();

		m_starts.resize(DIM + 1); Utility::MemsetZero(m_starts);

		for (int i = 0; i < DIM; ++i)
		{
			int num = isRowMajor ? array2D[i][0] : array2D[0][i];

			m_starts[i + 1] = m_starts[i] + num;
		}

		m_idxs.resize(m_starts.back());

		OMP_PARALLEL_FOR

		for (int i = 0; i < DIM; ++i)
		{
			int * address = m_idxs.data() + m_starts[i];

			int num = Size(i);

			for (int k = 1; k <= num; ++k)
			{
				address[k - 1] = isRowMajor ? array2D[i][k] : array2D[k][i];
			}
		}
	}

	void Clear()
	{
		Utility::ClearAndShrink(m_starts);
		Utility::ClearAndShrink(m_idxs);
		Utility::ClearAndShrink(m_values);
	}

	int Size() const 
	{
		return m_starts.back();
	}

	int Size(int id) const
	{
		return -m_starts[id] + m_starts[id + 1];
	}

	int Start(int id) const 
	{
		return m_starts[id];
	}

	const int* StartPtr(int id) const 
	{
		return &(m_starts[id]);
	}

	const int Idx(int id) const
	{
		return m_idxs[id];
	}

	const int * IdxPtr(int id) const
	{
		return m_idxs.data() + m_starts[id];
	}

	const Type * ValuePtr(int id) const 
	{
		return m_values.data() + m_starts[id];
	}

	virtual const SeCompressSparseData * Ptr() const
	{
		return this;
	}

protected:

	std::vector<int>	m_starts;
	std::vector<int>	m_idxs;
	std::vector<Type>	m_values;
};

template<typename Type> class SeCsr : public SeCompressSparseData<Type>
{
public:
	SeCsr() {}
	SeCsr(const std::vector<int>& starts, const std::vector<int>& idxs, const std::vector<Type>& values) :SeCompressSparseData<Type>(starts, idxs, values) {}

	int Rows() const { return SeCompressSparseData<Type>::m_starts.size() - 1; }

	virtual const SeCsr * Ptr() const override
	{
		return this;
	}
};


template<typename Type> class SeCsc : public SeCompressSparseData<Type>
{
public:

	int Columns() const { return SeCompressSparseData<Type>::m_starts.size() - 1; }

	virtual const SeCsc * Ptr() const override
	{
		return this;
	}
};

SE_NAMESPACE_END
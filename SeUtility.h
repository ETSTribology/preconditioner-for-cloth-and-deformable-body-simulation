#pragma once

#include "SePreDefine.h"

SE_NAMESPACE_BEGIN

namespace Utility
{
	template <typename Type>
	size_t ByteSize(const std::vector<Type> & data)
	{
		return sizeof(Type) * data.size();
	}

	template <typename Type>
	void Memcpy(Type * dstData, const Type * srcData, size_t size)
	{
		std::memcpy(dstData, srcData, size * sizeof(Type));
	}

	template <typename Type1, typename Type2>
	void Memcpy(std::vector<Type1> & data, const std::vector<Type2> & srcData, size_t size)
	{
		/*if(ByteSize(data) < ByteSize(srcData))
		{
			SE_WARNING_LOG("DesSize is less than Src Size!");
		}*/
		std::memcpy(data.data(), srcData.data(), SE_MIN(SE_MIN(ByteSize(data), ByteSize(srcData)), size * sizeof(Type1)));
	}

	template <typename Type>
	void Memset(std::vector<Type>& data, const Type & value)
	{
		std::fill(data.begin(), data.end(), value);
	}

	template <typename Type>
	void Memset(Type* data, const Type& value, size_t size)
	{
		std::fill(data, data + size, value);
	}

	template <typename Type>
	void MemsetZero(std::vector<Type> & data)
	{
		std::memset(data.data(), 0, ByteSize(data));
	}

	template <typename Type>
	void MemsetZero(Type * data, size_t size)
	{
		std::memset(data, 0, sizeof(Type) * size);
	}

	template <typename Type>
	void MemsetMinusOne(std::vector<Type> & data)
	{
		std::memset(data.data(), -1, ByteSize(data));
	}

	template <typename Type>
	void MemsetMinusOne(Type * data, size_t size)
	{
		std::memset(data, -1, sizeof(Type) * size);
	}

	template <typename Type>
	void ClearAndShrink(std::vector<Type> & data)
	{
		data.clear(); data.shrink_to_fit();
	}

	template <typename Type>
	void ResizeAndShrink(std::vector<Type> & data, size_t dim)
	{
		data.resize(dim); data.shrink_to_fit();
	}

	template <typename Type>
	void CopyAndShrink(std::vector<Type> & desData, const std::vector<Type> & srcData)
	{
		desData = srcData; desData.shrink_to_fit();
	}
}

SE_NAMESPACE_END

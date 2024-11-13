#pragma once

#include <atomic>
#include <stdint.h>
#include <intrin.h>

#include "SeMatrix.h"

SE_NAMESPACE_BEGIN

namespace Intrinsic
{
	/*************************************************************************
	**************************    Count of bits    ***************************
	*************************************************************************/

#ifdef WIN32
    inline int Clz32(unsigned int Val) { return __lzcnt(Val); }
    inline int Clz64(unsigned __int64 Val) { return __lzcnt64(Val); }
    inline int Popcount32(unsigned int Val) { return __popcnt(Val); }
    inline int Popcount64(unsigned __int64 Val) { return __popcnt64(Val); }

    #pragma intrinsic(_BitScanForward)
    inline int Ffs(int s)
    {
        unsigned long index = -1;
        unsigned char isNonzero = _BitScanForward(&index, s);
        /*s should be greater than 0; index is zero-based*/
        return isNonzero ? (index + 1) : 0;
    }

#else
    inline int Clz32(unsigned int Val) { return std::countl_zero(Val); }
    inline int Clz64( uint64_t Val) { return std::countl_zero(Val); }
    inline int Popcount32(unsigned int Val) { return std::popcount(Val); }
    inline int Popcount64(uint64_t Val) { return std::popcount(Val); }
    inline int Ffs(int s) { return ffs(s); }
#endif

	/*************************************************************************
	************************    Atomic operations    *************************
	*************************************************************************/


	template<typename Type> inline Type AtomicOr(Type * Address, Type Val) { return reinterpret_cast<std::atomic<Type>*>(Address)->fetch_or(Val,std::memory_order_relaxed); }
	template<typename Type> inline Type AtomicXor(Type * Address, Type Val) { return reinterpret_cast<std::atomic<Type>*>(Address)->fetch_xor(Val,std::memory_order_relaxed); }
	template<typename Type> inline Type AtomicAnd(Type * Address, Type Val) { return reinterpret_cast<std::atomic<Type>*>(Address)->fetch_and(Val,std::memory_order_relaxed); }
	template<typename Type> inline Type AtomicAdd(Type * Address, Type Val) { return reinterpret_cast<std::atomic<Type>*>(Address)->fetch_add(Val,std::memory_order_relaxed); }
	template<typename Type> inline Type AtomicSub(Type * Address, Type Val) { return reinterpret_cast<std::atomic<Type>*>(Address)->fetch_sub(Val,std::memory_order_relaxed); }
	template<typename Type> inline Type AtomicExch(Type * Address, Type Val) { return reinterpret_cast<std::atomic<Type>*>(Address)->exchange(Val,std::memory_order_relaxed); }
	template<typename Type> inline Type AtomicCAS(Type* Address, Type Exp, Type Val) { reinterpret_cast<std::atomic<Type>*>(Address)->compare_exchange_strong(Exp, Val, std::memory_order_relaxed); return Exp; }

	template< typename Type, typename Op > Type AtomicOperationByCas(Type* addr, Type value, Op op)
	{
		Type oldMyValue = *addr;
		bool isChangedByOtherThread = true;
		while (isChangedByOtherThread)
		{
			oldMyValue = *addr;
			Type m = op(value, oldMyValue);
			float newMyValue = AtomicCAS<Type>(addr, oldMyValue, m);
			isChangedByOtherThread = oldMyValue != newMyValue;
		}
		return oldMyValue;
	}


	template<typename Type> inline Type AtomicMax(Type* addr, Type value) 
	{ 
		return AtomicOperationByCas<Type>(addr, value, [](const auto& a, const auto& b) { return a > b ? a : b; });
	}

	template<typename Type> inline Type AtomicMin(Type* addr, Type value) 
	{ 
		return AtomicOperationByCas<Type>(addr, value, [](const auto& a, const auto& b) { return a < b ? a : b; });
	}

#if defined(WIN32) && (_MSVC_LANG > 201703L) // only for C++ 20 on Windows
	inline void AtomicAdd(SeMatrix3f* address, SeMatrix3f value)
	{
		for (int i = 0; i < 3; i++)
        {
			for (int j = 0; j < 3; j++)
            {
                    AtomicAdd(&(*address)(i, j), value(i, j));
            }
        }
	}

	template<typename Type, int Desc> inline void AtomicAdd(SeVector<Type, Desc> * address, SeVector<Type, Desc> value)
	{
		for (int i = 0; i < SeVector<Type, Desc>::Elements; i++)
        {
            AtomicAdd(&(*address)[i], value[i]);
        }
	}
#else
    inline void AtomicAdd(SeMatrix3f* address, SeMatrix3f value)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
            AtomicOperationByCas<float>( &(*address)(i, j), value(i, j), [](const auto& a, const auto& b) { return a + b; });
            }
        }
    }

    template<typename Type, int Desc> inline void AtomicAdd(SeVector<Type, Desc> * address, SeVector<Type, Desc> value)
    {
        for (int i = 0; i < SeVector<Type, Desc>::Elements; i++)
        {
            AtomicOperationByCas<float>(&(*address)[i], value[i], [](const auto& a, const auto& b) { return a + b; });
        }
    }

#endif

	/*************************************************************************
	*************************    Warp operations    **************************
	*************************************************************************/


	 inline void SyncWarp() {}
	 inline void SyncBlock() {}
	 inline unsigned int ActiveMask();
	 inline unsigned int LanemaskLt();
	 inline unsigned int LanemaskLt(unsigned int laneId) { return  (1U << laneId) - 1; }
}

SE_NAMESPACE_END
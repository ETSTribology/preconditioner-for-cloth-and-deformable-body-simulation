#pragma once

#include <memory>
#include <vector>
#include <assert.h>

/*************************************************************************
***************************    Min_Max_Swap    ***************************
*************************************************************************/

#define SE_MIN(a, b)		(((a) < (b)) ? (a) : (b))
#define SE_MAX(a, b)		(((a) > (b)) ? (a) : (b))
#define SE_SWAP(a, b)		{ auto c = a; a = b; b = c;}

/*************************************************************************
****************************    Namespace    *****************************
*************************************************************************/

#define SE_NAMESPACE SE
#define SE_NAMESPACE_BEGIN namespace SE_NAMESPACE {
#define SE_USING_NAMESPACE using namespace SE_NAMESPACE; 
#define SE_NAMESPACE_END }

/*************************************************************************
***************************    Noncopyable    ****************************
*************************************************************************/

#define SE_NONCOPYABLE(className)										\
																		\
	className(const className&) = delete;								\
																		\
	void operator=(const className&) = delete;							\

/*************************************************************************
****************************    DLL_Export    ****************************
*************************************************************************/

	
#define SE_INLINE					__inline
#define SE_ALIGN(n)					__declspec(align(n))		//!	Only for windows platform.
#define SE_ASSERT(expression)		assert(expression)


/*************************************************************************
*****************************    Casting    ******************************
*************************************************************************/

#define SE_SCI(ClassObject)			static_cast<int>(ClassObject)
#define SE_SCF(ClassObject)			static_cast<float>(ClassObject)
#define SE_SCD(ClassObject)			static_cast<double>(ClassObject)
#define SE_SCU(ClassObject)			static_cast<unsigned int>(ClassObject)

#ifndef NOMINMAX
	#define NOMINMAX
#endif
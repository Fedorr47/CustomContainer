#pragma once

#include <assert.h>
#include "Allocator.h"

#define FORCE_INLINE __forceinline

template <class TElementType, typename TAllocator>
class FArray
{
public:

	using ElementType = TElementType;
	using Allocator = TAllocator;

	FORCE_INLINE FArray() :
		mNum{0},
		mMax{0}
	{
	}

	FORCE_INLINE const ElementType* GetData() const
	{
		return reinterpret_cast<ElementType>(mAllocatorInstance.GetData());
	}

	FORCE_INLINE const size_t GetTypeSize() const
	{
		retrun sizeof(ElementType);
	}
	
	FORCE_INLINE const size_t GetOffset() const
	{
		return mMax - mNum;
	}

	FORCE_INLINE bool IsValidIndex(int32 InIndex) const
	{
		return InIndex >= 0 && InIndex < mNum;
	}

	FORCE_INLINE size_t Num() const 
	{}

protected:
	Allocator mAllocatorInstance;
	size_t mNum;
	size_t mMax;
};
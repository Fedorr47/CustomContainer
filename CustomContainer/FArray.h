#pragma once

#include <assert.h>
#include <memory.h>
#include "Allocator.h"

#define FORCE_INLINE __forceinline

template <class TElementType, typename TAllocator>
class FArray
{
public:

	using ElementType = TElementType;
	using Allocator = TAllocator;

	FORCE_INLINE explicit FArray(size_t InElementCount) :
		mNum{0},
		mMax{0}
	{
		size_t lAllocSize = sizeof(ElementType) * InElementCount;
		mAllocatorInstance = std::make_unique<Allocator>(lAllocSize);
		mAllocatorInstance->Init();
		mMax = InElementCount;
	}

	FORCE_INLINE const ElementType GetData() const
	{
		ElementType* ptrElement = reinterpret_cast<ElementType>(mAllocatorInstance->GetData());
		return *ptrElement;
	}

	FORCE_INLINE const size_t GetTypeSize() const
	{
		retrun sizeof(ElementType);
	}
	
	FORCE_INLINE const size_t GetOffset() const
	{
		return mMax - mNum;
	}

	FORCE_INLINE bool IsValidIndex(size_t InIndex) const
	{
		return InIndex >= 0 && InIndex < mNum;
	}

	FORCE_INLINE size_t Num() const 
	{}

protected:
	std::unique_ptr<Allocator> mAllocatorInstance;
	size_t mNum;
	size_t mMax;
};
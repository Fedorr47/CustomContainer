#pragma once

#include <assert.h>
#include <memory.h>
#include <utility>
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
		mAllocatorInstance = std::make_unique<Allocator>(InElementCount);
		mAllocatorInstance->Init<ElementType>();
		mMax = InElementCount;
	}

	FORCE_INLINE ElementType* GetData() const
	{
		ElementType* ptrElement = reinterpret_cast<ElementType*>(mAllocatorInstance->GetData());
		return ptrElement;
	}

	FORCE_INLINE const size_t GetTypeSize() const
	{
		return sizeof(ElementType);
	}
	
	FORCE_INLINE const size_t GetOffset() const
	{
		return mMax - mNum;
	}

	FORCE_INLINE void CheckInvariants() const
	{
		assert(mNum >= 0 && mMax >= mNum);
	}

	FORCE_INLINE bool RangeCheck(size_t InIndex) const
	{
		return (InIndex >= 0 && InIndex < mNum);
	}

	FORCE_INLINE size_t Num() const 
	{
		return mNum;
	}

	template <class... ArgsType>
	FORCE_INLINE size_t Emplace(ArgsType&& ...Args)
	{
		CheckInvariants();
		const size_t lIndex = mNum;
		new(GetData() + lIndex) ElementType(std::forward<ArgsType>(Args)...);
		++mNum;
		return lIndex;
	}

	FORCE_INLINE ElementType& operator[](size_t InIndex)
	{
		return GetData()[InIndex];
	}

protected:
	std::unique_ptr<Allocator> mAllocatorInstance;
	size_t mNum;
	size_t mMax;
};
#pragma once

#include <assert.h>
#include <memory.h>
#include <utility>
#include <initializer_list>
#include "Allocator.h"
#include "Utils.h"

#define FORCE_INLINE __forceinline

template <class TElementType, typename TAllocator>
class FArray
{
private:

	using ElementType = TElementType;
	using Allocator = TAllocator;
	using ReferenceType = ElementType&;
	using PointerType = ElementType*;
	using ConstPointerType = const ElementType*;

public:

	struct Iterator
	{
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = ElementType;
		using pointer = ElementType*;
		using reference = ElementType&;

		Iterator(pointer InPtr) :
			mPtr(InPtr)
		{}

		FORCE_INLINE reference operator*() const { return *mPtr; }
		FORCE_INLINE pointer operator->() { return mPtr; }
		FORCE_INLINE Iterator& operator++()
		{ ++mPtr; return *this; }
		FORCE_INLINE Iterator& operator++(int)
		{ Iterator tmp = *this;  ++mPtr;  return tmp; }
		FORCE_INLINE friend	bool operator==(const Iterator& first, const Iterator& second) { return first.mPtr == second.mPtr; }
		FORCE_INLINE friend	bool operator!=(const Iterator& first, const Iterator& second) { return first.mPtr != second.mPtr; }
	private:
		pointer mPtr;
	};



	FORCE_INLINE explicit FArray(size_t InElementCount) :
		mNum{0},
		mMax{0}
	{
		mAllocatorInstance = std::make_unique<Allocator>(InElementCount);
		mAllocatorInstance->Init<ElementType>();
		mMax = InElementCount;
	}


	FORCE_INLINE FArray(std::initializer_list<ElementType> InList) {};

	template <
		class OtherElementType,
		class OtherAllocator,
		FArrayElementsAreCompatible T
	>
	FORCE_INLINE FArray(const FArray<OtherElementType, OtherAllocator>& InOther) {}

	FORCE_INLINE ElementType* GetData()
	{
		ElementType* ptrElement = reinterpret_cast<ElementType*>(mAllocatorInstance->GetData());
		return ptrElement;
	}

	FORCE_INLINE const ElementType* GetData() const
	{
		const ElementType* ptrElement = reinterpret_cast<const ElementType*>(mAllocatorInstance->GetData());
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

	template <class ComporationType>
	bool Contains(const ComporationType& Item) const
	{
		for (const ElementType* __restrict Data = GetData(), *__restrict DataEnd = Data + mNum; Data != DataEnd; ++Data)
		{
			if (*Data == Item)
			{
				return true;
			}
		}
		return false;
	}

	void ClearAll()
	{
		
	}

	Iterator begin() { return Iterator(&GetData()[0]); }
	Iterator end() { return Iterator(&GetData()[mMax]); }

protected:
	std::unique_ptr<Allocator> mAllocatorInstance;
	size_t mNum;
	size_t mMax;
};
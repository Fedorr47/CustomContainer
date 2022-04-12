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

	struct Iterator;
	friend class Iterator;

	struct Iterator
	{
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = ElementType;
		using pointer = ElementType*;
		using reference = ElementType&;

		Iterator(pointer InPtr, Allocator* InAllocatorInstance) :
			mPtr{ InPtr },
			mAllocatorInstance{ InAllocatorInstance },
			mIndex{0}
		{}

		FORCE_INLINE reference operator*() const { return *mPtr; }
		FORCE_INLINE pointer operator->() { return mPtr; }
		FORCE_INLINE Iterator& operator++()
		{ 
			++mIndex;
			mPtr = reinterpret_cast<ElementType*>(mAllocatorInstance->GetData(mIndex));
			return *this; 
		}
		FORCE_INLINE Iterator& operator++(int)
		{ 
			Iterator tmp = *this;  
			++mIndex;
			mPtr = reinterpret_cast<ElementType*>(mAllocatorInstance->GetData(mIndex));
			return tmp; 
		}
		FORCE_INLINE friend	bool operator==(const Iterator& first, const Iterator& second) { return first.mPtr == second.mPtr; }
		FORCE_INLINE friend	bool operator!=(const Iterator& first, const Iterator& second) { return first.mPtr != second.mPtr; }
	private:
		pointer mPtr{nullptr};
		Allocator* mAllocatorInstance{nullptr};
		size_t mIndex{ 0 };
	};

	

	FORCE_INLINE explicit FArray(size_t InElementCount) :
		mNum{0},
		mMax{0}
	{
		mAllocatorInstance = new Allocator(InElementCount);
		mAllocatorInstance->Init<ElementType>();
		mMax = InElementCount;
	}

	~FArray()
	{
		delete mAllocatorInstance;
	}

	//FORCE_INLINE FArray(std::initializer_list<ElementType...> InList) {};

	template <
		class OtherElementType,
		class OtherAllocator,
		FArrayElementsAreCompatible T
	>
	FORCE_INLINE FArray(const FArray<OtherElementType, OtherAllocator>& InOther) {}

	FORCE_INLINE ElementType* GetData(size_t InIndex) const
	{
		ElementType* ptrElement = reinterpret_cast<ElementType*>(mAllocatorInstance->GetData(InIndex));
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
	FORCE_INLINE void Emplace(ArgsType&& ...Args)
	{
		CheckInvariants();
		void* lCurrentAddress = mAllocatorInstance->Allocate(sizeof(ElementType), 0);
		new(lCurrentAddress) ElementType(std::forward<ArgsType>(Args)...);
		++mNum;
	}

	FORCE_INLINE ElementType& operator[](size_t InIndex)
	{
		return *GetData(InIndex);
	}

	FORCE_INLINE void Resize(size_t InElementCount)
	{
		//size_t lResizeCount = std::min(mMax, InElementCount);
		//mNum = std::min(lResizeCount, mNum);
		//mMax = InElementCount;
		//Allocator* lAllocatorInstance = new Allocator(InElementCount);

		//lAllocatorInstance->Init<ElementType>();
		//std::memcpy(lAllocatorInstance->GetRawData(), mAllocatorInstance->GetRawData(), lResizeCount);
		//delete mAllocatorInstance;
		//mAllocatorInstance = lAllocatorInstance;
	}

	FORCE_INLINE void ClearAll()
	{
		mAllocatorInstance->Reset();
		mNum = 0;
	}

	template <class IsPositiveInteger>
	FORCE_INLINE void RemoveByindex(size_t InIndex)
	{
		return RemoveByIndexImpl(InIndex, 1);
	}

	template <class ComporationType>
	FORCE_INLINE bool Contains(const ComporationType& Item)
	{
		return Find(Item) == INDEX_NONE ? false : true;
	}

	template <class ComporationType>
	FORCE_INLINE size_t Find(const ComporationType& InItem)
	{
		size_t Index = 0;
		for (ElementType* Data = GetData(0), *DataEnd = GetLast(); Data != DataEnd; 
			++Index, Data = reinterpret_cast<ElementType*>(GetData(Index)))
		{
			if (*Data == InItem)
			{
				return Index;
			}
		}
		return INDEX_NONE;
	}

	FORCE_INLINE bool Find(const ElementType& InItem, size_t& OutIndex)
	{
		OutIndex = Find(InItem);
		return OutIndex != INDEX_NONE;
	}

	void Sort()
	{

	}

	Iterator begin() { return Iterator(GetData(0), mAllocatorInstance); }
	Iterator end() { return Iterator(GetData(mMax), mAllocatorInstance); }

private:

	template <class IsPositiveInteger>
	void RemoveByIndexImpl(size_t InIndex, IsPositiveInteger InCount)
	{
		CheckInvariants();

		while (InCount)
		{
			mAllocatorInstance->Free(GetByIndex(InIndex));
			--InCount;
			++InIndex;
		}
	}

	FORCE_INLINE ElementType* GetLast() const
	{
		return reinterpret_cast<ElementType*>(GetData(mMax));
	}

	FORCE_INLINE ElementType* GetByIndex(size_t InIndex) const
	{
		return reinterpret_cast<ElementType*>(GetData(InIndex));
	}

protected:
	Allocator* mAllocatorInstance;
	size_t mNum;
	size_t mMax;
};
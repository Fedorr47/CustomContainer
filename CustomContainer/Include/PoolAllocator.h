#pragma once

#include "Allocator.h"
#include "StackLinkedList.h"

class PoolAllocator : public Allocator
{
protected:

	void* mStartPointer = nullptr;
	size_t mChunckSize;

	struct FreeHeader{};

	using Node = StackLinkedList<FreeHeader>::Node;
	StackLinkedList<FreeHeader> mFreeBlocksList;	

	void Reset();

public:
	PoolAllocator(const size_t InTotalAllocSize);
	virtual ~PoolAllocator();

	void Init() override {};
	void* Allocate(const size_t InAllocSize, const size_t InAligment) override;
	void Free(void* InPointer) override;

	void* GetData(const size_t InIndex) const override;
	virtual void* GetRawData() const override;

	template <class ChunckType>
	void Init()
	{
		if (mStartPointer != nullptr)
		{
			free(mStartPointer);
		}
		mChunckSize = sizeof(ChunckType);
		mTotalAllocSize = mTotalAllocSize * (mChunckSize + sizeof(Node));
		mStartPointer = malloc(mTotalAllocSize);
		Reset();
	}
};
#define max(a,b) ((a)>(b)?(a):(b))

#include <assert.h>
#include <stdlib.h>
#include <algorithm>

#include "Include/PoolAllocator.h"

PoolAllocator::PoolAllocator(const size_t InTotalAllocSize) :
	Allocator{ InTotalAllocSize },
	mStartPointer{ nullptr },
	mChunckSize{ 0 }
{
}

PoolAllocator::~PoolAllocator()
{
	if (mStartPointer != nullptr)
	{
		free(mStartPointer);
	}
}

void* PoolAllocator::GetData(const size_t InIndex) const
{
	void* lCurrentPointer = mStartPointer;
	const size_t ChunckWithTitleSize = mChunckSize + sizeof(Node);
	if (lCurrentPointer != nullptr)
	{
		size_t lCurrentPointerInt = reinterpret_cast<size_t>(lCurrentPointer) + (InIndex * ChunckWithTitleSize) + sizeof(Node);
		lCurrentPointer = reinterpret_cast<void*>(lCurrentPointerInt);
	}
	return lCurrentPointer;
}

void* PoolAllocator::GetRawData() const
{
	return mStartPointer;
}

void* PoolAllocator::Allocate(const size_t InAllocSize, const size_t InAligment)
{
	assert(InAllocSize == this->mChunckSize && "Allocation size must be equal to chunk size");

	Node* pFreePosition = mFreeBlocksList.pop();

	assert(pFreePosition != nullptr && "The pool allocator is full");

	mUsed += mChunckSize;
	mPeak = max(mPeak, mUsed);

	size_t AddressAfterNode = reinterpret_cast<size_t>(pFreePosition) + sizeof(Node);
	return reinterpret_cast<void*>(AddressAfterNode);
}

void PoolAllocator::Free(void* InPointer)
{
	mUsed -= mChunckSize;
	mFreeBlocksList.push(static_cast<Node*>(InPointer));
}

void PoolAllocator::Reset()
{
	mUsed = mPeak = 0;
	const size_t ChunckWithTitleSize = mChunckSize + sizeof(Node);
	const size_t ChunksCount = mTotalAllocSize / ChunckWithTitleSize;
	Node* node;
	for (int i = 0; i < ChunksCount; ++i)
	{
		void* lAddress = reinterpret_cast<void*>(reinterpret_cast<size_t>(mStartPointer) + (i * ChunckWithTitleSize));
		node = new(lAddress) Node;
		mFreeBlocksList.push(node);
	}
}


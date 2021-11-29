#define max(a,b) ((a)>(b)?(a):(b))

#include <assert.h>
#include <stdlib.h>
#include <algorithm>

#include "PoolAllocator.h"

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

void* PoolAllocator::GetData()
{
	void* lCurrentPointer = mStartPointer;
	if (lCurrentPointer != nullptr)
	{
		size_t lCurrentPointerInt = reinterpret_cast<size_t>(lCurrentPointer) + mUsed;
		lCurrentPointer = reinterpret_cast<void*>(lCurrentPointerInt);
	}
	return lCurrentPointer;
}

void* PoolAllocator::Allocate(const size_t InAllocSize, const size_t InAligment)
{
	assert(InAllocSize == this->mChunckSize && "Allocation size must be equal to chunk size");

	Node* pFreePosition = mFreeBlocksList.pop();

	assert(pFreePosition != nullptr && "The pool allocator is full");

	mUsed += mChunckSize;
	mPeak = max(mPeak, mUsed);

	return reinterpret_cast<void*>(pFreePosition);
}

void PoolAllocator::Free(void* InPointer)
{
	mUsed -= mChunckSize;
	mFreeBlocksList.push(static_cast<Node*>(InPointer));
}

void PoolAllocator::Reset()
{
	mUsed = mPeak = 0;
	const size_t ChunksCount = mTotalAllocSize / (mChunckSize + sizeof(Node));
	for (int i = 0; i < ChunksCount; ++i)
	{
		size_t lAddress = reinterpret_cast<size_t>(mStartPointer) + (i * mChunckSize);
		mFreeBlocksList.push(reinterpret_cast<Node*>(lAddress));
	}
}


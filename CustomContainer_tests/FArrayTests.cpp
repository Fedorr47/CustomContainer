#include "pch.h"

#include "FArrayTests.h"

TEST(FArrayTests, InitArray)
{
	FArray<int, PoolAllocator> ptrIntFArray(10);
}
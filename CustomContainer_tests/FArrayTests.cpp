#include "pch.h"

#include "FArrayTests.h"

TEST(FArrayTests, InitIntArray)
{
	FArray<int, PoolAllocator> ptrIntFArray(10);
	EXPECT_EQ(ptrIntFArray.GetOffset(), 10);
}

TEST(FArrayTests, InitTestallocStructArray)
{
	FArray<TestAllocStruct, PoolAllocator> ptrTestAllocStructFArray(10);
	EXPECT_EQ(ptrTestAllocStructFArray.GetOffset(), 10);
}

TEST(FArrayTests, EmplaceTestallocStructArray)
{
	FArray<TestAllocStruct, PoolAllocator> ptrTestAllocStructFArray(10);
	ptrTestAllocStructFArray.Emplace();
	auto res = ptrTestAllocStructFArray[0];
	EXPECT_EQ(res.BoolValue, true);
	EXPECT_EQ(res.IntegerValue, 1);
	EXPECT_EQ(res.FloatValue, 1.1f);
	EXPECT_EQ(res.ShortString, "A");
}
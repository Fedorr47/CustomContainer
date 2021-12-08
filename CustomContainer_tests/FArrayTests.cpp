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

TEST(FArrayTests, EmplaceTestAllocStructArray)
{
	FArray<TestAllocStruct, PoolAllocator> ptrTestAllocStructFArray(10);
	ptrTestAllocStructFArray.Emplace();
	auto res = ptrTestAllocStructFArray[0];
	EXPECT_EQ(res.BoolValue, true);
	EXPECT_EQ(res.IntegerValue, 1);
	EXPECT_EQ(res.FloatValue, 1.1f);
	EXPECT_EQ(res.ShortString, "A");
}

TEST(FArrayTests, IteratorTestAllocStructArray)
{
	FArray<TestAllocStruct, PoolAllocator> ptrTestAllocStructFArray(10);
	for (int i = 0; i < 10; ++i)
	{
		ptrTestAllocStructFArray.Emplace();
	}
	for (auto TestAllocInstance : ptrTestAllocStructFArray)
	{
		EXPECT_EQ(TestAllocInstance.BoolValue, true);
		EXPECT_EQ(TestAllocInstance.IntegerValue, 1);
		EXPECT_EQ(TestAllocInstance.FloatValue, 1.1f);
		EXPECT_EQ(TestAllocInstance.ShortString, "A");
	}
}

TEST(FArrayTests, RandomAccessesTestAllocStructArray)
{
	FArray<TestAllocStruct, PoolAllocator> ptrTestAllocStructFArray(10);
	for (int i = 0; i < 10; ++i)
	{
		ptrTestAllocStructFArray.Emplace(i, 1.1f, false, "B", std::string(255, 'B'));
	}

	EXPECT_EQ(ptrTestAllocStructFArray[5].BoolValue, false);
	EXPECT_EQ(ptrTestAllocStructFArray[5].IntegerValue, 5);
	EXPECT_EQ(ptrTestAllocStructFArray[5].FloatValue, 1.1f);
	EXPECT_EQ(ptrTestAllocStructFArray[5].ShortString, "B");
}

TEST(FArrayTests, ContainsTestAllocStructArray)
{
	FArray<TestAllocStruct, PoolAllocator> ptrTestAllocStructFArray(10);
	size_t SpecificElement = 5;
	TestAllocStruct FifthElement(SpecificElement, 2.0f, true, "F", std::string(5, 'F'));

	for (int i = 0; i < 10; ++i)
	{
		if (i == SpecificElement)
		{
			ptrTestAllocStructFArray.Emplace(FifthElement);
		}
		else
		{
			ptrTestAllocStructFArray.Emplace(i, 1.1f, false, "B", std::string(255, 'B'));
		}
	}

	EXPECT_TRUE(ptrTestAllocStructFArray.Contains(FifthElement));
}

TEST(FArrayTests, ClearTestAllocStructArray)
{
}

TEST(FArrayTests, RemoveByindexTestAllocStructArray)
{
}

TEST(FArrayTests, FindTestAllocStructArray)
{
}

TEST(FArrayTests, SortAllocStructArray)
{
}
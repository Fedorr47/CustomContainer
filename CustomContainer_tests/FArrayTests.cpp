#include "pch.h"

#include "FArrayTests.h"

TEST(FArrayTests, InitIntArray)
{
	FArray<int, PoolAllocator> ptrIntFArray(10);
	EXPECT_EQ(ptrIntFArray.GetOffset(), 10);
}

TEST(FArrayTests, InitTestallocStructArray)
{
	int lArraySize = 10;
	FArray<TestAllocStruct, PoolAllocator> ptrTestAllocStructFArray(lArraySize);
	EXPECT_EQ(ptrTestAllocStructFArray.GetOffset(), lArraySize);
}

TEST(FArrayTests, EmplaceTestAllocStructArray)
{
	int lArraySize = 10;
	FArray<TestAllocStruct, PoolAllocator> ptrTestAllocStructFArray(lArraySize);
	ptrTestAllocStructFArray.Emplace();
	auto res = ptrTestAllocStructFArray[0];
	EXPECT_EQ(res.BoolValue, true);
	EXPECT_EQ(res.IntegerValue, 1);
	EXPECT_EQ(res.FloatValue, 1.1f);
	EXPECT_EQ(res.ShortString, "A");
}

TEST(FArrayTests, IteratorTestAllocStructArray)
{
	int lArraySize = 2;
	FArray<TestAllocStruct, PoolAllocator> ptrTestAllocStructFArray(lArraySize);

	for (int i = 0; i < lArraySize; ++i)
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
	int SpecificElement = 5;
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

TEST(FArrayTests, FindTestAllocStructArray)
{
	FArray<TestAllocStruct, PoolAllocator> ptrTestAllocStructFArray(10);
	int InSpecificElementNumber = 5;
	TestAllocStruct FifthElement(InSpecificElementNumber, 2.0f, true, "F", std::string(5, 'F'));


	for (int i = 0; i < 10; ++i)
	{
		if (i == InSpecificElementNumber)
		{
			ptrTestAllocStructFArray.Emplace(FifthElement);
		}
		else
		{
			ptrTestAllocStructFArray.Emplace(i, 1.1f, false, "B", std::string(255, 'B'));
		}
	}

	size_t OutSpecificElementNumber = 0;
	ptrTestAllocStructFArray.Find(FifthElement, OutSpecificElementNumber);
	EXPECT_EQ(InSpecificElementNumber, OutSpecificElementNumber);
}

//TEST(FArrayTests, ResizeExtend)
//{
//	FArray<TestAllocStruct, PoolAllocator> ptrTestAllocStructFArray(10);
//	for (int i = 0; i < 10; ++i)
//	{
//		ptrTestAllocStructFArray.Emplace(i, 1.1f, false, "B", std::string(255, 'B'));
//	}
//
//	ptrTestAllocStructFArray.Resize(20);
//
//	for (int i = 10; i < 20; ++i)
//	{
//		ptrTestAllocStructFArray.Emplace(i, 1.1f, false, "B", std::string(255, 'B'));
//	}
//
//	EXPECT_EQ(ptrTestAllocStructFArray[19].BoolValue, false);
//	EXPECT_EQ(ptrTestAllocStructFArray[19].IntegerValue, 19);
//	EXPECT_EQ(ptrTestAllocStructFArray[19].FloatValue, 1.1f);
//	EXPECT_EQ(ptrTestAllocStructFArray[19].ShortString, "B");
//
//}
//
//TEST(FArrayTests, ResizeShrink)
//{
//	FArray<TestAllocStruct, PoolAllocator> ptrTestAllocStructFArray(10);
//	for (int i = 0; i < 10; ++i)
//	{
//		ptrTestAllocStructFArray.Emplace(i, 1.1f, false, "B", std::string(255, 'B'));
//	}
//
//	ptrTestAllocStructFArray.Resize(5);
//
//
//	EXPECT_EQ(ptrTestAllocStructFArray[4].BoolValue, false);
//	EXPECT_EQ(ptrTestAllocStructFArray[4].IntegerValue, 4);
//	EXPECT_EQ(ptrTestAllocStructFArray[4].FloatValue, 1.1f);
//	EXPECT_EQ(ptrTestAllocStructFArray[4].ShortString, "B");
//
//}
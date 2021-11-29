#include "pch.h"

#include "PoolAllocatorTests.h"

TEST(PoolAllocatorTests, CreatePoolAllocator) {
	PoolAllocator tStacAllocator(8);
	tStacAllocator.Init<int>();
	int* ptrStartPointer = reinterpret_cast<int*>(tStacAllocator.GetData());
	EXPECT_TRUE(ptrStartPointer != nullptr);
}

TEST_F(TestPoolAllocator, Allocate) {
	int* ptrStartPointer = reinterpret_cast<int*>(ptrPoolAllocator->GetData());
	EXPECT_TRUE(ptrStartPointer != nullptr);
	void* ptrVoidAllocated = ptrPoolAllocator->Allocate(sizeof(TestAllocStruct), 0);
	int* ptrAllocated = reinterpret_cast<int*>(ptrVoidAllocated);
	EXPECT_TRUE(ptrAllocated != nullptr);
	new(ptrStartPointer) TestAllocStruct();
	TestAllocStruct* ptrTestAllocStruct = reinterpret_cast<TestAllocStruct*>(ptrStartPointer);
	EXPECT_EQ(ptrTestAllocStruct->IntegerValue, 1);
	EXPECT_EQ(ptrTestAllocStruct->FloatValue, 1.1f);
	EXPECT_EQ(ptrTestAllocStruct->BoolValue, true);
	EXPECT_EQ(ptrTestAllocStruct->ShortString, "A");
}

TEST_F(TestPoolAllocator, AllocateFour) {
	int* ptrStartPointer = reinterpret_cast<int*>(ptrPoolAllocator->GetData());

	std::vector<int> vAllocateIndexes(4);
	std::generate(vAllocateIndexes.begin(), vAllocateIndexes.end(), [n = 0]() mutable { return ++n; });
	void* ptrVoidAllocated = nullptr;
	int* ptrAllocated = nullptr;
	TestAllocStruct* ptrTestAllocStruct = nullptr;
	
	for (int AllocateIndex : vAllocateIndexes)
	{
		ptrVoidAllocated = ptrPoolAllocator->Allocate(sizeof(TestAllocStruct), 0);
		ptrAllocated = reinterpret_cast<int*>(ptrVoidAllocated);
		new(ptrAllocated) TestAllocStruct();
		ptrTestAllocStruct = reinterpret_cast<TestAllocStruct*>(ptrAllocated);
		EXPECT_EQ(ptrTestAllocStruct->IntegerValue, 1);
		EXPECT_EQ(ptrTestAllocStruct->FloatValue, 1.1f);
		EXPECT_EQ(ptrTestAllocStruct->BoolValue, true);
		EXPECT_EQ(ptrTestAllocStruct->ShortString, "A");
	}
}

TEST_F(TestPoolAllocator, Free) {
	int* ptrStartPointer = reinterpret_cast<int*>(ptrPoolAllocator->GetData());
	void* ptrVoidAllocated = ptrPoolAllocator->Allocate(sizeof(TestAllocStruct), 0);
	int* ptrAllocated = reinterpret_cast<int*>(ptrVoidAllocated);
	new(ptrAllocated) TestAllocStruct();
	TestAllocStruct* ptrTestAllocStruct = reinterpret_cast<TestAllocStruct*>(ptrAllocated);
	EXPECT_EQ(ptrTestAllocStruct->IntegerValue, 1);
	EXPECT_EQ(ptrTestAllocStruct->FloatValue, 1.1f);
	EXPECT_EQ(ptrTestAllocStruct->BoolValue, true);
	EXPECT_EQ(ptrTestAllocStruct->ShortString, "A");

	ptrPoolAllocator->Free(ptrVoidAllocated);
}



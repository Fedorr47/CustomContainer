#include "pch.h"

#include "StackAllocatorTest.h"

TEST(StackAllocatorTests, CreateStackAllocator) {
	StackAllocator tStacAllocator(100);
	tStacAllocator.Init();
	int* ptrStartPointer = reinterpret_cast<int*>(tStacAllocator.GetData(0));
	EXPECT_TRUE(ptrStartPointer != nullptr);
}

TEST_F(TestStackAllocator, Allocate) {
	int* ptrStartPointer = reinterpret_cast<int*>(ptrStackAllocator->GetData(0));
	EXPECT_TRUE(ptrStartPointer != nullptr);
	void* ptrVoidAllocated = ptrStackAllocator->Allocate(sizeof(TestAllocStruct), 0);
	int* ptrAllocated = reinterpret_cast<int*>(ptrVoidAllocated);
	EXPECT_TRUE(ptrAllocated != nullptr && ptrAllocated > ptrStartPointer);
	new(ptrStartPointer) TestAllocStruct();
	TestAllocStruct* ptrTestAllocStruct = reinterpret_cast<TestAllocStruct*>(ptrStartPointer);
	EXPECT_EQ(ptrTestAllocStruct->IntegerValue, 1);
	EXPECT_EQ(ptrTestAllocStruct->FloatValue, 1.1f);
	EXPECT_EQ(ptrTestAllocStruct->BoolValue, true);
	EXPECT_EQ(ptrTestAllocStruct->ShortString, "A");
}



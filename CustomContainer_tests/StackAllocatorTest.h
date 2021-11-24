#pragma once

#include "StackAllocator.h"

struct TestAllocStruct
{
	int IntegerValue;
	float FloatValue;
	bool BoolValue;
	std::string ShortString;
	std::string LongString;

	TestAllocStruct() :
		IntegerValue{ 1 },
		FloatValue{ 1.1f },
		BoolValue{ true },
		ShortString{ "A" }
	{
		LongString = std::string(255, 'A');
	}
};

class TestStackAllocator : public ::testing::Test
{
protected:
	void SetUp()
	{
		ptrStackAllocator = std::make_shared<StackAllocator>(sizeof(TestAllocStruct) + 8);
		ptrStackAllocator->Init();
	}
	void TearDown()
	{
	}
	std::shared_ptr<StackAllocator> ptrStackAllocator;
};
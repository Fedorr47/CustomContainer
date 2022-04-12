#pragma once

#include "Include/StackAllocator.h"

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
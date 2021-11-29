#pragma once

#include "PoolAllocator.h"

class TestPoolAllocator : public ::testing::Test
{
protected:
	void SetUp()
	{
		ptrPoolAllocator = std::make_shared<PoolAllocator>(sizeof(TestAllocStruct) * 4);
		ptrPoolAllocator->Init<TestAllocStruct>();
	}
	void TearDown()
	{
	}
	std::shared_ptr<PoolAllocator> ptrPoolAllocator;
};
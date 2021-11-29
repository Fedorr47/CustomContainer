#include <iostream>
#include "PoolAllocator.h"
#include "StackAllocator.h"
#include "FArray.h"

int main()
{
	PoolAllocator poolAllocator(100);
	poolAllocator.Init<int>();
	return 0;
}
#include <iostream>
#include "PoolAllocator.h"
#include "StackAllocator.h"
#include "FArray.h"

int main()
{
	FArray<int, PoolAllocator> a(10);
	return 0;
}
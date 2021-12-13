#include <iostream>
#include "PoolAllocator.h"
#include "StackAllocator.h"
#include "FArray.h"

#include <vector>

int main()
{
	FArray<int, PoolAllocator> a(10);

	std::vector<char> VecTest(10, 'a');
	auto res = VecTest[0];
	return 0;
}
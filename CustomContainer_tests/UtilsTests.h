#pragma once

#include <iostream>

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
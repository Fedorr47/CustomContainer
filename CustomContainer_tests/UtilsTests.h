#pragma once

#include <iostream>

struct TestAllocStruct
{
	int  IntegerValue;
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
		//LongString = std::string(255, 'A');
		LongString = std::string(1, 'A');
	}

	TestAllocStruct(
		int				InIntegerValue,
		float			InFloatValue,
		bool			InBoolValue,
		std::string		InShortString,
		std::string		InLongString
	) :
		IntegerValue{ InIntegerValue },
		FloatValue{ InFloatValue },
		BoolValue{ InBoolValue }	
	{
		ShortString = InShortString;
		LongString = InLongString;
	}
};

constexpr bool operator==(const TestAllocStruct& lhs, const TestAllocStruct& rhs)
{
	return  lhs.IntegerValue == rhs.IntegerValue &&
		lhs.FloatValue == rhs.FloatValue &&
		lhs.BoolValue == rhs.BoolValue &&
		lhs.ShortString == rhs.ShortString &&
		lhs.LongString == rhs.LongString;
}
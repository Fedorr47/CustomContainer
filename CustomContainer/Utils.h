#pragma once
#include <type_traits>
#include <cstdint>

template <class TypeFirst, class TypeSecond>
concept FArrayElementsAreCompatible =
	requires (TypeFirst First, TypeSecond Second)
{
	typename std::disjunction<typename std::is_same<TypeFirst, std::decay_t<TypeFirst>>::value, std::is_constructible<TypeFirst,TypeSecond>>;
};
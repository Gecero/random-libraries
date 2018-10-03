#ifndef CONSTMATH_HPP
#define CONSTMATH_HPP
namespace gcr {
	constexpr bool isEven(uint64_t number);
	constexpr bool isOdd(uint64_t number);
	constexpr uint64_t ceil(long double number);
	constexpr uint64_t floor(long double number);
	constexpr long double sin(long double number);



	constexpr bool isEven(uint64_t number) { return ((number + 1) & 1); }
	constexpr bool isOdd(uint64_t number) { return !((number + 1) & 1); }
	constexpr uint64_t ceil(long double number) { return (uint64_t)(number + 0.5); }
	constexpr uint64_t floor(long double number) { return (uint64_t)(number); }
	constexpr long double sin(long double number) { return 20.785*((number*0.15915) - (int)(number*0.15915))*(((number*0.15915) - (int)(number*0.15915)) - 0.5)*(((number*0.15915) - (int)(number*0.15915)) - 1.0); }
}
#endif
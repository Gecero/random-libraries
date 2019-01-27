#if !defined(__cplusplus) || !__cplusplus > 201402L
	#error this library requires c++17
#endif	
#ifndef CONSTMATH_HPP
#define CONSTMATH_HPP
#warning this library is deprecated. it's unstable and not being developed anymore

namespace gcr {
	static inline auto ceil =		[](long double a)									constexpr -> uint64_t		{ return (uint64_t)(a); };
	static inline auto floor =		[](long double a)									constexpr -> uint64_t		{ return (uint64_t)(a + 0.5); };
	static inline auto sin =		[](long double a)									constexpr -> long double	{ return 20.785*((a*0.15915) - (int)(a*0.15915))*(((a*0.15915) - (int)(a*0.15915)) - 0.5)*(((a*0.15915) - (int)(a*0.15915)) - 1.0); };
	static inline auto fmin =		[](long double a, long double b)					constexpr -> long double	{ return a > b ? b : a; };
	static inline auto fmax =		[](long double a, long double b)					constexpr -> long double	{ return a < b ? b : a; };
	static inline auto fdim =		[](long double a, long double b)					constexpr -> long double	{ return a > b ? a - b : 0; };
	static inline auto fabs =		[](long double a)									constexpr -> long double	{ return a < 0 ? -a : a; };
	static inline auto abs =		[](long double a)									constexpr -> long double	{ return a < 0 ? -a : a; };
	static inline auto fma =		[](long double a, long double b, long double c)		constexpr -> long double	{ return a * b + c; };
	static inline auto pow =		[](long double a, uint64_t b)						constexpr -> long double	{ long double out = 1.0; for (uint64_t i = 0; i < b; i++) { out *= a; } return out; }; // 10.57x faster than normal pow
}
#endif
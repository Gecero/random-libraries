//TO-DO:
//	- memory usage benchmarking
//	- mac compability
//	- compability for std::chrono::seconds, std::chrono::milliseconds and so on

#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP
#include <chrono>
#include <vector>
#ifdef _WIN32
	#include <Windows.h>
#elif defined(__APPLE__)
	#error this library does not support the macintosh blast processing technology yet
#endif

#if !defined(__cplusplus) || !__cplusplus >= 201103L
	#error this library needs c++11
#endif

template<typename T>
class benchmark {
	static_assert(!(std::is_convertible<T, std::chrono::seconds>::value ||
					std::is_convertible<T, std::chrono::milliseconds>::value ||
					std::is_convertible<T, std::chrono::microseconds>::value ||
					std::is_convertible<T, std::chrono::nanoseconds>::value ||
					std::is_convertible<T, std::chrono::minutes>::value ||
					std::is_convertible<T, std::chrono::hours>::value),
					"std::chrono time units are not supported yet");
private:
	std::chrono::high_resolution_clock::time_point timeSync1;
	std::chrono::high_resolution_clock::time_point timeSync2;
	uint64_t cycleSync1;
	uint64_t cycleSync2;
	std::vector<std::chrono::duration<T>> benchmarkTimes;
	std::vector<uint64_t> benchmarkCycles;
	uint64_t benchmarks;
	#ifdef _WIN32
		__forceinline inline uint64_t __fastcall cpuCycles() noexcept { return __rdtsc(); }
	#elif defined(__linux__)
		inline uint64_t cpuCycles() {
			unsigned int lo, hi;
			__asm__ __volatile__("rdtsc" : "=a" (lo), "=d" (hi));
			return ((uint64_t)hi << 32) | lo;
		}
	#endif
public:
	// make a benchmarker that can test the speed of your code
	benchmark() {
		benchmarkTimes.clear();
		benchmarkCycles.clear();
		benchmarks = 0;
	}
	// deconstruct the benchmarker
	~benchmark() {
		benchmarkTimes.clear();
		benchmarkCycles.clear();
	}
	// get the average run times of your code from the benchmarks in seconds
	T getAverageBenchmarkTime() {
		long double sum = 0;
		uint64_t size = benchmarkTimes.size();
		for (int i = 0; i < size; i++)
			sum += benchmarkTimes[i].count();
		return (T)(sum / size);
	}
	// get the average amount of cycles needed from the benchmarks
	T getAverageBenchmarkCycles() {
		long double sum = 0;
		uint64_t size = benchmarkCycles.size();
		for (uint64_t i = 0; i != size; i++)
			sum += benchmarkCycles[i];
		return (T)(sum / size);
	}
	// get the amount of benchmarks already made
	inline uint64_t getNumberOfBenchmarks() {
		return benchmarks;
	}
	// set the number of estimated benchmarks that are going to be made. this can make the benchmarking a lot faster
	inline void setNumberOfEstimatedBenchmarks(uint64_t estimatedNumberOfBenchmarks) {
		benchmarkTimes.reserve(estimatedNumberOfBenchmarks);
		benchmarkCycles.reserve(estimatedNumberOfBenchmarks);
	}
	// benchmark a function
	void runFunctionBenchmark(void(*function)()) {
		timeSync1 = std::chrono::high_resolution_clock::now();
		cycleSync1 = cpuCycles();
		function();
		cycleSync2 = cpuCycles();
		timeSync2 = std::chrono::high_resolution_clock::now();
		benchmarkTimes.push_back(timeSync2 - timeSync1);
		benchmarkCycles.push_back(cycleSync2 - cycleSync1);
		benchmarks++;
	}
	// start an independent benchmark that needs no function as argument
	void startIndependentBenchmark() {
		timeSync1 = std::chrono::high_resolution_clock::now();
		cycleSync1 = cpuCycles();
	}
	// stop the independent benchmark
	void stopIndependentBenchmark() {
		cycleSync2 = cpuCycles();
		timeSync2 = std::chrono::high_resolution_clock::now();
		benchmarkTimes.push_back(timeSync2 - timeSync1);
		benchmarkCycles.push_back(cycleSync2 - cycleSync1);
		benchmarks++;
	}
};
#endif

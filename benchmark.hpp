//TO-DO:
//	- memory usage benchmarking
//	- mac compability (could be compatible but i didn't tested it yet)
//	- compability for std::chrono::seconds, std::chrono::milliseconds and so on

#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP
#include <chrono>
#include <vector>
#ifdef _WIN32
	#include <intrin.h>
#else
	#include <x86intrin.h>
#endif

#if !defined(__cplusplus) || !__cplusplus >= 201103L
	#error this library needs c++11
#endif

#ifdef __APPLE__
	#warning there is no offical support for apple platforms
#endif

template<class T>
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
	template<typename return_type>
	return_type runFunctionBenchmark(return_type(*function)()) {
		return_type returnValue;
		timeSync1 = std::chrono::high_resolution_clock::now();
		cycleSync1 = __rdtsc();
		returnValue = function();
		cycleSync2 = __rdtsc();
		timeSync2 = std::chrono::high_resolution_clock::now();
		benchmarkTimes.push_back(timeSync2 - timeSync1);
		benchmarkCycles.push_back(cycleSync2 - cycleSync1);
		benchmarks++;
		return returnValue;
	}
	void runFunctionBenchmark(void(*function)()) {
		timeSync1 = std::chrono::high_resolution_clock::now();
		cycleSync1 = __rdtsc();
		function();
		cycleSync2 = __rdtsc();
		timeSync2 = std::chrono::high_resolution_clock::now();
		benchmarkTimes.push_back(timeSync2 - timeSync1);
		benchmarkCycles.push_back(cycleSync2 - cycleSync1);
		benchmarks++;
	}
	// start an independent benchmark that needs no function as argument
	void startIndependentBenchmark() {
		timeSync1 = std::chrono::high_resolution_clock::now();
		cycleSync1 = __rdtsc();
	}
	// stop the independent benchmark
	void stopIndependentBenchmark() {
		cycleSync2 = __rdtsc();
		timeSync2 = std::chrono::high_resolution_clock::now();
		benchmarkTimes.push_back(timeSync2 - timeSync1);
		benchmarkCycles.push_back(cycleSync2 - cycleSync1);
		benchmarks++;
	}
};
#endif

#include <chrono>
#include <vector>
#include <thread>
#include <string>
#ifdef _WIN32
	#include <intrin.h>
	#include <Windows.h>
#else
	#include <cstring>
#endif
template<typename T>
class benchmark {
private:
	std::chrono::steady_clock::time_point tp1;
	std::chrono::steady_clock::time_point tp2;
	uint64_t cp1 = 0;
	uint64_t cp2 = 0;
	std::vector<std::chrono::duration<T>> benchmarkTimes;
	std::vector<uint64_t> benchmarkCycles;
	uint64_t benchmarks = 0;
	#ifdef _WIN32
		uint64_t cpuCycles() {
			return __rdtsc();
		}
	#else
		uint64_t cpuCycles() {
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
		tp1 = std::chrono::steady_clock::now();
		tp2 = std::chrono::steady_clock::now();
	}
	// destruct the benchmarker
	~benchmark() {
		benchmarkTimes.clear();
		benchmarkCycles.clear();
		#ifdef _WIN32
			ZeroMemory(&this->benchmarkCycles, sizeof(this->benchmarkCycles));
			ZeroMemory(&this->benchmarks, sizeof(this->benchmarks));
			ZeroMemory(&this->benchmarkTimes, sizeof(this->benchmarkTimes));
			ZeroMemory(&this->cp1, sizeof(this->cp1));
			ZeroMemory(&this->cp2, sizeof(this->cp2));
			ZeroMemory(&this->tp1, sizeof(this->tp1));
			ZeroMemory(&this->tp2, sizeof(this->tp2));
		#else
			memset(&this->benchmarkCycles, 0, sizeof(benchmarkCycles));
			memset(&this->benchmarks, 0, sizeof(benchmarks));
			memset(&this->benchmarkTimes, 0, sizeof(benchmarkTimes));
			memset(&this->cp1, 0, sizeof(cp1));
			memset(&this->cp2, 0, sizeof(cp2));
			memset(&this->tp1, 0, sizeof(tp1));
			memset(&this->tp2, 0, sizeof(tp2));
		#endif
	}
	// get the average run times of your code from the benchmarks
	T getAverageBenchmarkTimes() {
		double sum = 0;
		for (int i = 0; i < benchmarkTimes.size(); i++)
			sum += benchmarkTimes[i].count();
		return (T)(sum / benchmarkTimes.size());
	}
	// get the average amount of cycles needed from the benchmarks
	T getAverageBenchmarkCycles() {
		double sum = 0;
		for (int i = 0; i < benchmarkCycles.size(); i++)
			sum += benchmarkCycles[i];
		return (T)(sum / benchmarkCycles.size());
	}
	// get the amount of benchmarks already made
	uint64_t getNumberOfBenchmarks() {
		return benchmarks;
	}
	// set the number of estimated benchmarks that are going to be made. using this can make the benchmarking extremely fast
	void setNumberOfEstimatedBenchmarks(uint64_t estimatedNumberOfBenchmarks) {
		benchmarkTimes.reserve(estimatedNumberOfBenchmarks);
		benchmarkCycles.reserve(estimatedNumberOfBenchmarks);
	}
	// benchmark a function
	void runFunctionBenchmark(void(*function)()) {
		tp1 = std::chrono::steady_clock::now();
		cp1 = cpuCycles();
		function();
		cp2 = cpuCycles();
		tp2 = std::chrono::steady_clock::now();
		std::chrono::duration<T> dur = tp2 - tp1;
		uint64_t cyc = cp2 - cp1;
		benchmarkTimes.push_back(dur);
		benchmarkCycles.push_back(cyc);
		benchmarks++;
	}
	// start an independent benchmark that needs no function as argument
	void startIndependentBenchmark() {
		tp1 = std::chrono::steady_clock::now();
		tp2 = std::chrono::steady_clock::now();
		cp1 = cpuCycles();
		cp2 = cpuCycles();
	}
	// stop the independent benchmark
	void stopIndependentBenchmark() {
		cp2 = cpuCycles();
		tp2 = std::chrono::steady_clock::now();
		std::chrono::duration<T> dur = tp2 - tp1;
		uint64_t cyc = cp2 - cp1;
		benchmarkTimes.push_back(dur);
		benchmarkCycles.push_back(cyc);
		benchmarks++;
	}
};
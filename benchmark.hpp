#include <chrono>
#include <vector>
#ifdef _WIN32
#include <intrin.h>
#endif
template<typename T>
class benchmark {
private:
	std::chrono::system_clock::time_point tp1;
	std::chrono::system_clock::time_point tp2;
	uint64_t cp1 = 0;
	uint64_t cp2 = 0;
	std::vector<std::chrono::duration<T>> benchmarkTimes;
	std::vector<long long> benchmarkCycles;
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
	benchmark() {
		benchmarkTimes.clear();
		tp1 = std::chrono::system_clock::now();
		tp2 = std::chrono::system_clock::now();

	}
	T getAverageBenchmarkTimes() {
		double sum = 0;
		for (int i = 0; i < benchmarkTimes.size(); i++)
			sum += benchmarkTimes[i].count();
		return (T)(sum / benchmarkTimes.size());
	}
	T getAverageBenchmarkCycles() {
		double sum = 0;
		for (int i = 0; i < benchmarkCycles.size(); i++)
			sum += benchmarkCycles[i];
		return (T)(sum / benchmarkCycles.size());
	}

	void runFunctionBenchmark(void(*function)()) {
		tp1 = std::chrono::system_clock::now();
		cp1 = cpuCycles();
		function();
		cp2 = cpuCycles();
		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<T> tmp = tp2 - tp1;
		uint64_t tmp2 = cp2 - cp1;
		benchmarkCycles.reserve(benchmarkCycles.size()+1);
		benchmarkTimes.reserve(benchmarkTimes.size()+1);
		benchmarkTimes.push_back(tmp);
		benchmarkCycles.push_back(tmp2);
	}
};
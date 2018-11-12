#pragma once

#include <ctime>
#include <math.h>
#include <vector>
#include <string>
#include <atlstr.h>
#include <limits.h>
#include <thread>
#include "Benchmark.h"
#include <cmath>

class Benchmark {

public:

	int* get_duration();
	Benchmark(HWND hwnd, int* affinity);
	void start_benchmark();

private:
	HWND h, running;
	int primes[78498], seive[1000000], duration[10];
	int index = 0, j, count = 0;
	int* a;
	clock_t start;
	double score;
	CString str;
	bool affinity_flag;

	int run();
	void calc_primes();
	int int_single_cache_hit(volatile int x, volatile int y);
	int int_single_cache_miss(volatile int x, volatile int y);
};
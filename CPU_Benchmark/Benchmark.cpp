#include "stdafx.h"
#include "Benchmark.h"

Benchmark::Benchmark(HWND hwnd, int* affinity)
	{
		h = hwnd;
		a = affinity;
	}
	
void Benchmark::start_benchmark() {
	std::thread run_bench(&Benchmark::run, this);
	running = CreateWindow(TEXT("STATIC"), L"Running Benchmark", WS_CHILD | WS_VISIBLE, 750, 750, 198, 17, h, NULL, NULL, NULL);
	run_bench.detach();
}

int Benchmark::run() {
		int z = 0;
		calc_primes();
		start = clock();
		std::thread run_int_cache_hit(&Benchmark::int_single_cache_hit, this, 0, 0);
		run_int_cache_hit.join();
		duration[0] = clock() - start;
		start = clock();
		std::thread run_int_cache_miss(&Benchmark::int_single_cache_miss, this, 0, 0);
		run_int_cache_miss.join();
		duration[1] = clock() - start;
		str.Format(L"%d", duration[0]);
		MessageBox(h, LPCWSTR(str), L"TEST", MB_OK);
		str.Format(L"%d", duration[1]);
		MessageBox(h, LPCWSTR(str), L"TEST", MB_OK);
		start = clock();
		return z;
	}

int* Benchmark::get_duration() {
	return duration;
}

void Benchmark::calc_primes() {
	for (int i = 0; i < 1000000; i++) {
		seive[i] = 0;
	}
	start = clock();
	for (int i = 2; i < sqrt(1000000); i++)
	{
		for (long long j = i * i; j < 1000000; j += i)
		{
			seive[j - 1] = 1;
		}
	}
	for (int i = 1; i < 1000000; i++)
	{
		if (seive[i - 1] == 0) {
			primes[index] = i;
			index++;
		}
	}
}

int Benchmark::int_single_cache_hit(volatile int x, volatile int y) {
	for (int i = 1; i < INT_MAX - 2; i+=3) {
		x = y + (primes[std::abs(i) % 78497]);
		y = x + (primes[std::abs(i - 1) % 78497]);
	}
	for (int i = INT_MIN; i < -2; i+=3) {
		x = y + (primes[std::abs(i % 78497)]);
		y = x + (primes[std::abs((i + 1) % 78497)]);
	}
	return x;
}

int Benchmark::int_single_cache_miss(volatile int x, volatile int y) {
	for (int i = 1; i < INT_MAX - 2; i+=3) {
		x = y + primes[std::abs(i * 3) % 78497];
		y = x + primes[std::abs(i / 3) % 78497];
	}
	for (int i = INT_MIN; i < -2; i+=3) {
		x = y - primes[std::abs(i * 3 % 78497)];
		y = x - primes[std::abs(i / 3 % 78497)];
	}
	return x;
}
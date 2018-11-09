#include "stdafx.h"
#include <ctime>
#include <math.h>
#include <vector>
#include <string>
#include <atlstr.h>

class Benchmark {
public:

	HWND h;

	Benchmark(HWND hwnd)
	{
		h = hwnd;
	}
	
	void run() {
		calc_primes();
		start = clock();

		duration[0] = clock() - start;
		start = clock();
	}

	int* get_duration() {
		return duration;
	}

private:

	int primes[78498], seive[1000000];
	int index = 0, j;
	clock_t start;
	int duration[10];
	double score;
	CString str;

	void calc_primes() {
		for (int i = 0; i < 1000000; i++) {
			seive[i] = 0;
		}
		HWND status_primes = CreateWindow(TEXT("STATIC"), NULL, WS_CHILD | WS_VISIBLE, 250, 200, 198, 17, h, NULL, NULL, NULL);
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

	
};
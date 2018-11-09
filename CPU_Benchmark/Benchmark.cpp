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
	}

private:

	int primes[78498], seive[1000000];
	int index = 0, j;
	clock_t start;
	int duration;
	double score;
	CString str;

	void calc_primes() {
		HWND status_primes = CreateWindow(TEXT("STATIC"), NULL, WS_CHILD | WS_VISIBLE, 250, 200, 198, 17, h, NULL, NULL, NULL);
		start = clock();
		for (int i = 2; i < 1000000; i++)
		{
			for (int j = i * i; j < 1000000; j += i)
			{
				seive[j - 1] = 1;
			}
		}
		for (int i = 1; i < 1000000; i++)
		{
			if (seive[i - 1] == 0) {
				primes[index] = i;
			}
		}
		duration = (clock() - start);
		str.Format(L"%d", duration);
		score = primes[78497];
		CreateWindow(TEXT("STATIC"), LPCWSTR(str), WS_CHILD | WS_VISIBLE, 250, 250, 198, 17, h, NULL, NULL, NULL);
		str.Format(L"%.0f", score);
		CreateWindow(TEXT("STATIC"), LPCWSTR(str), WS_CHILD | WS_VISIBLE, 250, 300, 198, 17, h, NULL, NULL, NULL);
		
	}

	
};
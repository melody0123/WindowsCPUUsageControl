#include <Windows.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

const double pi = acos(-1.0);

DWORD WINAPI draw_sine_curve() // y = A * sin(w * pi) + A
{
	double delta = 0.01; // step length
	int amplitude = 50;
	double omega = 0.0; // coefficent of pi

	// sample on the sine curve
	double busy[200] = { 0.0 };
	double idle[200] = { 0.0 };
	for (int i = 0; i < 200; i ++)
	{
		busy[i] = amplitude * sin(omega * pi) + amplitude;
		idle[i] = 2 * amplitude - busy[i];
		omega += delta;
	}

	// run
	int i = 0;
	while (true)
	{
		clock_t start = clock();
		while (clock() - start <= busy[i]) ;
		Sleep(idle[i]);
		i = (i + 1) % 200;
	}

	ExitThread(0);
}

int main()
{
	HANDLE threads[16];
	int CPU_index = 0;

	for (int i = 0; i < 16; i++)
	{
		threads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)draw_sine_curve, NULL, 0, NULL);
		SetThreadAffinityMask(threads[i], 1 << CPU_index);
		CPU_index ++;
	}

	for (int i = 0; i < 16; i++)
		WaitForSingleObject(threads[i], INFINITE);

	ExitThread(0);
}
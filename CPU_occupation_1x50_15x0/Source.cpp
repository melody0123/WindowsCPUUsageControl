#include <stdio.h>
#include <Windows.h>
#include <time.h>

DWORD WINAPI func()
{
	clock_t runtime = 12; // ms

	while (true) // 50% usage
	{
		clock_t start = clock();
		while (clock() - start <= runtime) ;
		Sleep(runtime);
	}

	ExitThread(0);
}

DWORD WINAPI zero_usage()
{
	while (true) // 0% usage
	{
		Sleep(INFINITE);
	}

	ExitThread(0);
}

int main()
{
	HANDLE threads[16];
	int CPU_index = 0;

	// bond threads[0] to core 0
	threads[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)func, NULL, 0, NULL);
	SetThreadAffinityMask(threads[0], 1 << CPU_index);
	CPU_index++;

	// bond other threads to core 1~15
	for (int i = 1; i < 16; i++)
	{
		threads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)zero_usage, NULL, 0, NULL);
		SetThreadAffinityMask(threads[0], 1 << CPU_index);
		CPU_index ++;
	}

	for (int i = 0; i < 16; i++)
		WaitForSingleObject(threads[i], INFINITE);

	ExitThread(0);
}
#include <Windows.h>
#include <stdio.h>
#include <time.h>

DWORD WINAPI func()
{
	int runtime = 12;

	while (true)
	{
		clock_t start = clock();
		while (clock() - start <= runtime) ;
		Sleep(runtime);
	}

	ExitThread(0);
}

int main()
{
	HANDLE threads[16]; // threads array
	int CPU_index = 0;

	for (int i = 0; i < 16; i++)
	{
		threads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)func, NULL, 0, NULL);
		SetThreadAffinityMask(threads[i], 1 << CPU_index);
		CPU_index++;
	}

	for (int i = 0; i < 16; i++)
		WaitForSingleObject(threads[i], INFINITE);

	ExitThread(0);
}
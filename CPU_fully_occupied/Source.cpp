#include <Windows.h>
#include <stdio.h>

DWORD WINAPI func()
{
	while (true); // do nothing but occupy CPU core in busy state

	ExitThread(0);
}

int main()
{
	HANDLE threads[16]; // an array of thread
	int CPU_index = 0; // used in SetThreadAffinityMask(). Bond thread with certain CPU core

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
// MultiThreadPrac.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>

using namespace std;

HANDLE hSem;
CRITICAL_SECTION cs;
HANDLE hEvent;

#define MAX 10

int data[MAX];
int top = -1;
bool isFinished = false;

DWORD WINAPI Push(LPVOID)
{
	int i = 0;

	EnterCriticalSection(&cs);
	while(top < MAX - 1 ) {

		data[++top] = i;
		++i;
		ReleaseSemaphore(hSem, 1, NULL);

		if( i > 100) break;
		LeaveCriticalSection(&cs);
		EnterCriticalSection(&cs);
	}

	isFinished = true;
	LeaveCriticalSection(&cs);
	return 0;
}

DWORD WINAPI Pop(LPVOID)
{
	while(1){
		WaitForSingleObject(hSem, INFINITE);

		EnterCriticalSection(&cs);
		cout << data[top--] << endl;
		if(top == -1 && isFinished) SetEvent(hEvent);
		LeaveCriticalSection(&cs);
	}

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	hSem = CreateSemaphore(NULL, 0, MAX, NULL);
	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	InitializeCriticalSection(&cs);

	CreateThread(NULL, 0, &Push, NULL, TRUE, NULL);

	CreateThread(NULL, 0, &Pop, NULL, TRUE, NULL);
	CreateThread(NULL, 0, &Pop, NULL, TRUE, NULL);
	CreateThread(NULL, 0, &Pop, NULL, TRUE, NULL);
	CreateThread(NULL, 0, &Pop, NULL, TRUE, NULL);
	CreateThread(NULL, 0, &Pop, NULL, TRUE, NULL);

	WaitForSingleObject(hEvent, INFINITE);

	system("pause");
	return 0;
}


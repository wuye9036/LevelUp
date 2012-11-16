#pragma once

class EventTest
{
public:
	EventTest(void);
public:
	~EventTest(void);
};
/*
DWORD WINAPI Set(LPVOID)
{
	for(int i = 0; i < MAX; ++i){
		//等待空事件触发
		WaitForSingleObject(hEmptyEvent, INFINITE);

		ResetEvent(hEmptyEvent);
		cout << "Set!" << isFull << endl;
		isFull = true;

		SetEvent(hFullEvent);
	}

	return 0;
}

DWORD WINAPI Get(LPVOID)
{	
	for(int i = 0; i < MAX; ++i){
		WaitForSingleObject(hFullEvent, INFINITE);

		ResetEvent(hFullEvent);
		cout << "Get!" << isFull << endl;
		isFull = false;
		SetEvent(hEmptyEvent);
	}

	return 0;
}bool isFull;
HANDLE hFullEvent;
HANDLE hEmptyEvent;
*/

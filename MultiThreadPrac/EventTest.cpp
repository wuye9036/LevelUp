#include "StdAfx.h"
#include "EventTest.h"

EventTest::EventTest(void)
{
}

EventTest::~EventTest(void)
{
}

	/*
	hFullEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
	hEmptyEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	isFull = false;

	HANDLE hs[2];
	hs[0] = CreateThread(NULL, 0, &Get, NULL, 0, NULL);
	hs[1] = CreateThread(NULL, 0, &Set, NULL, 0, NULL);

	WaitForMultipleObjects(2, &hs[0], TRUE, INFINITE);

	CloseHandle(hs[0]);
	CloseHandle(hs[1]);
	*/
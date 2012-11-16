#pragma once
#include "windows.h"
#include "assert.h"
#include <platform/typedef.h>

static BOOL QueryPerformanceCounterMP(LARGE_INTEGER* lpPerformanceCounter) {
	
	if(!lpPerformanceCounter) return FALSE;

	HANDLE hCurrentProcess = GetCurrentProcess();
	DWORD dwProcessAffinity;
	DWORD dwSystemAffinity;

	// Get the current affinity.
	GetProcessAffinityMask (hCurrentProcess,
		&dwProcessAffinity,
		&dwSystemAffinity);

	// Assert that we can use the first processor.
	assert ((dwSystemAffinity & 0x1) != 0);

	// Force to the first processor.  It can be any one, but it must always be
	// the same one.
	SetProcessAffinityMask (hCurrentProcess, 1);

	// Get current counter.
	QueryPerformanceCounter(lpPerformanceCounter);

	// Restore affinity to its previous state.
	SetProcessAffinityMask (hCurrentProcess, dwProcessAffinity);

	return TRUE;
}

#if defined(MULTI_PROCESSOR_VER)
#define QueryPerformanceCounter QueryPerformanceCounterMP
#endif

class Timer
{
	// unit: second
	double startTime_;
	double ticksPerSec_;
	double perfFreq_;
public:
	Timer(uint32 ms = 100/*unit: second*/) 
	{
		LARGE_INTEGER start, end, freq;
		uint64 sRdtsc, eRdtsc;

		QueryPerformanceFrequency(&freq);
		perfFreq_ = double(freq.QuadPart);

		QueryPerformanceCounter(&start);
		sRdtsc = GetRDTSC();
		Sleep(ms);
		eRdtsc = GetRDTSC();
		QueryPerformanceCounter(&end);

		ticksPerSec_ = double(eRdtsc - sRdtsc) / ( double(end.QuadPart - start.QuadPart) / perfFreq_);
	}

	void StartTimer() { startTime_ = GetTime(); }
	double EndTimer(){ return GetTime() - startTime_; }

	uint64 GetRDTSC(){ __asm RDTSC }
	double GetTime(){
#if defined(MULTI_PROCESSOR_VER)
		LARGE_INTEGER t;
		QueryPerformanceCounter(&t);
		return double(t.QuadPart) / perfFreq_;
#else
		return double(GetRDTSC()) / ticksPerSec_; 
#endif
	}
};

class BenchmarkHelper{
	HANDLE hThread_;
	HANDLE hProc_;
public:
	BenchmarkHelper(){
		hProc_ = GetCurrentProcess();
		hThread_ = GetCurrentThread();
		SetPriorityClass(hProc_, REALTIME_PRIORITY_CLASS);
		//SetThreadPriority(hThread_, THREAD_PRIORITY_TIME_CRITICAL);
	}

	~BenchmarkHelper(){
		SetPriorityClass(hProc_, NORMAL_PRIORITY_CLASS);
		SetThreadPriority(hThread_, THREAD_PRIORITY_NORMAL);
	}
};


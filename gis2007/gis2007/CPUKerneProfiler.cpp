// gis2007.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "math.h"
float foo(float x)
{
	return sin(x);
}

#include "Timer.h"
#include "omp.h"
#include <vector>
#include <iostream>

using namespace std;

#define N 262114
const int threadNum = 4;
#define innerLoop 100

struct CPUBenchInfo
{
	float* out;
	int		threadId;
	int		threadNum;
};

DWORD WINAPI LoopThreadFunction (LPVOID input) {

	float* out = ((CPUBenchInfo*)input)->out;
	int threadId = ((CPUBenchInfo*)input)->threadId;
	int threadNum = ((CPUBenchInfo*)input)->threadNum;

	int start_pos = threadId * (N / threadNum);
	int end_pos = (threadId + 1) * (N / threadNum);

	for(int j = start_pos; j < end_pos; ++j)
	{
		out[j] = 0.00f;
	}
	for(int i = 0; i < 100; ++i){
		for(int j = start_pos; j < end_pos; ++j)
		{
			out[j] += 0.02f * ((j % 4) + 1);
			out[j] = foo(out[j]);
		}
	}
	return 0;
}
volatile long c = 0;

class PingpongKernel
{
	Timer tr;
	double ecpu_mt;

	vector<float> out_cpu;
	typedef void (*PBenchmark)(vector<float>&,  int);

public:
	static	void DoCPUBenchmark(vector<float>& out, int threadId)
	{
		int start_pos = threadId * (N / threadNum);
		int end_pos = (threadId + 1) * (N / threadNum);

		for(int j = start_pos; j < end_pos; ++j)
		{
			out[j] = 0.00f;
		}
		for(int i = 0; i < innerLoop; ++i){
			for(int j = start_pos; j < end_pos; ++j)
			{
				out[j] +=  0.02f * ((j % 4) + 1);
				out[j] = foo(out[j]);
			}
		}
	}

	PingpongKernel():out_cpu(N)
	{
	}

	~PingpongKernel(){
	}

	void Execute(){
		//BenchmarkHelper bh;

		printf("The Number of Processors : %d\n", omp_get_num_procs());
		printf("The Maximum Number of Hardware Threads : %d\n", omp_get_max_threads());

		printf("CPU Profiler Begin...\n");

		omp_set_num_threads(4);

		HANDLE hThreads[4];
		CPUBenchInfo cb[4];

		//cpu benchmark
		tr.StartTimer();
#pragma omp parallel for
		for(int threadid = 0 ; threadid < 4; ++threadid){
			DoCPUBenchmark(out_cpu, threadid);
		}
		double ecpu_omp = tr.EndTimer();

		tr.StartTimer();
		for(int i = 0; i < 4; ++i)
		{
			cb[i].out = &(out_cpu[0]);
			cb[i].threadId = i;
			cb[i].threadNum = 4;
			hThreads[i] = CreateThread(NULL, 0, LoopThreadFunction, &cb, 0, NULL);
		}
		WaitForMultipleObjects(4, hThreads, TRUE, INFINITE);
		ecpu_mt = tr.EndTimer();


		cout << "CPU MultiThread:" << ecpu_mt << endl
			<< "CPU OpenMP:" << ecpu_omp << endl;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{	
	PingpongKernel ppk;
	ppk.Execute();

	system("pause");
	return 0;
}
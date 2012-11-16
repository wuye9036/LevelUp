// OpenMPProfiler.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "omp.h"
#include "Timer.h"
#include <math.h>
#include <vector>

using namespace std;

#define innerLoop 65536
#define outterLoop 100

typedef void (*PF) (vector<float>&, int);

class Test
{
public:
	static	vector<float> data;

	static	void DoLoopRange(vector<float>& out, int threadId)
	{
		int start = threadId * (innerLoop / 4);
		int end = (threadId+1) * (innerLoop/4);

		for(int j = start; j < end; ++j)
		{
			out[j] = 0.00f;
		}
		for(int i = 0; i < outterLoop; ++i){
			for(int j = start; j < end; ++j)
			{
				out[j] += 0.02f * ((j % 4) + 1);
				out[j] = sin(cos(out[j]));
			}
		}
	}
	static void Initialize(vector<float>& data)
	{
		for(int i = 0; i < innerLoop; ++i)
		{
			data[i] = float(i);
		}
	}
	void Execute()
	{
		BenchmarkHelper bh;
		
		printf("The Number of Processors : %d\n", omp_get_num_procs());
		printf("The Maximum Number of Hardware Threads : %d\n", omp_get_max_threads());

		omp_set_num_threads(4);
		
		Timer	 tr;
		double t;

		PF pF = &DoLoopRange;

		Initialize(data);
		//----------------------------------------------------
		tr.StartTimer();
		for(int k = 0; k < 4; ++k)
		{
			for(int j = 0; j < outterLoop; ++j)
			{
				for(int i = k * (innerLoop / 4); i < (k+1) * (innerLoop / 4); ++i)
				{
					data[i] += (j * 0.001f);
					data[i] = sin(cos(data[i]));
				}
			}
		}
		t = tr.EndTimer();
		printf("Dependency - Serial - Direct Code: %6.4f\n", t);
		//----------------------------------------------------	

		Initialize(data);
		//----------------------------------------------------
		tr.StartTimer();
		for(int i = 0; i < 4; ++i)
		{
			DoLoopRange(data, i);
		}
		t = tr.EndTimer();
		printf("Dependency - Serial - Function Call: %6.4f\n", t);
		//----------------------------------------------------

		Initialize(data);
		//----------------------------------------------------
		tr.StartTimer();
		for(int i = 0; i < 4; ++i) (*pF) (data, i);
		t = tr.EndTimer();
		printf("Dependency - Serial - Indirectly Call: %6.4f\n", t);
		//----------------------------------------------------

		omp_set_num_threads(4);
		printf("test\n");

		Initialize(data);
		//----------------------------------------------------
		tr.StartTimer();
#pragma omp parallel for
		for(int i  = 0; i < 4; ++i)
		{
			DoLoopRange(data, i);
		}
		t = tr.EndTimer();
		printf("Dependency - OpenMP - Function Call: %6.4f\n", t);
		//----------------------------------------------------

		Initialize(data);
		//----------------------------------------------------
		tr.StartTimer();
#pragma omp parallel for
		for(int i  = 0; i < 4; ++i)
		{
			(*pF)(data, i);
		}
		t = tr.EndTimer();
		printf("Dependency - OpenMP - Indirectly Call: %6.4f\n", t);
	}
};


vector<float> Test::data(innerLoop);

int _tmain(int argc, _TCHAR* argv[])
{
	Test t;
	t.Execute();
	//----------------------------------------------------
	//system("pause");
	return 0;
}


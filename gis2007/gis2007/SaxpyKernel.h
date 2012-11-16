#pragma once

#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include "aligned_allocator.h"
#include "GraphicProcessor.h"

struct Saxpy_Data
{
	float		a;
	float*		x;
	float*		y;
	float*		out;
	int			itnum;
};

static const char saxpy_ps[] = \
"uniform float alpha;"\
"uniform sampler2DRect x;"\
"void main()"\
"{"\
"	vec4 t = texture2DRect(x, gl_TexCoord[0].st);" 
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	t = alpha * t + t;"
"	gl_FragColor = t;"\
"}";

#define ARRAY_X_STAGE 0
#define ARRAY_OUTPUT_STAGE 1

class SaxpyKernel :
	public Kernel
{
	GraphicProcessor*	pGP_;
	glShaderManager*	pGLSM_;
	glShader*				pShader_;
	PerformanceReport	pr_;

	int		blockSize_;
	int		vec_size;

	int		itnum_;
	float	a_;
	vector<float, aligned_allocator<float, 16> > x_;
	vector<float, aligned_allocator<float, 16> > y_;

	vector<float, aligned_allocator<float, 16> > cpu_out;
	vector<float, aligned_allocator<float, 16> > gpu_out;

	Timer tr, tr_kernel;

	static DWORD WINAPI LoopThreadFunction(LPVOID pInput);
	static void SaxPy_SSE(float* out, float a, float* x, float* y, int n);
	static void DoCPUBenchmark(TEI* pInfo)
	{
		Saxpy_Data* data = (Saxpy_Data*)(pInfo->data);

		for(int it = 0; it < data->itnum; ++it){
			for(int i = pInfo->range_begin; i < pInfo->range_end; ++i)	{
				data->out[i] = data->x[i] ;
			}
			for(int i = pInfo->range_begin; i < pInfo->range_end; ++i)	{
				for(int j = 0; j < 30; ++j){
					data->out[i] = data->out[i] * data->a + data->out[i];
				}
			}
			//SaxPy_SSE(&(data->out[pInfo->range_begin]), data->a, &(data->x[pInfo->range_begin]), NULL, pInfo->range_end - pInfo->range_begin);
		}
	}
public:

	void InitializeData()
	{
		printf("Now Initialize the data. Please Waiting...\n");
		srand(uint32(time(NULL)));
		a_ = float(rand()) / float(RAND_MAX);
		for(int i = 0; i < vec_size; ++i){
			x_[i] = float(rand()) / float(RAND_MAX);
			y_[i] = float(rand()) / float(RAND_MAX);
		}
		printf("Data Initialize Done.\n");
	}

	void ExecuteOnCPU(){
		Saxpy_Data data;
		data.a = a_;
		data.out = &(cpu_out[0]);
		data.x = &(x_[0]);
		data.y = &(y_[0]);
		data.itnum = itnum_;

		//... ... Do CPU Benchmark ... ...
		ThreadExecutionInfos teis(&data, 0, vec_size, 1);
		tr.StartTimer();
		DoCPUBenchmark(&(teis[0]));
		pr_[PIID_CPU] = tr.EndTimer();
		//..........................................
		
		//
		tr.StartTimer();
		for(int i = 0; i < itnum_; ++i){
			SaxPy_SSE(data.out, data.a, data.x, NULL, vec_size);
		}
		double sse_time = tr.EndTimer();
		printf("CPU SSE: %8.6f\n", sse_time);

		//... ... Do CPU Benchmark ... ...
		data.out = &(gpu_out[0]);
		ThreadExecutionInfos teis_mt(&data, 0, vec_size, 4, sizeof(float), 16);
		omp_set_num_threads(4);
		tr.StartTimer();
#pragma omp parallel for
		for(int i = 0; i < 4; ++i){
			DoCPUBenchmark(&(teis_mt[i]));
		}
		pr_[PIID_CPU_OMP] = tr.EndTimer();
		//------------------------------------------
		
		HANDLE hThreads[4];
		tr.StartTimer();
		for(int i = 0; i < 4; ++i)
		{
			hThreads[i] = CreateThread(NULL, 0, LoopThreadFunction, &(teis_mt[i]), 0, NULL);
		}
		WaitForMultipleObjects(4, hThreads, TRUE, INFINITE);
		pr_[PIID_CPU_MT] = tr.EndTimer();
		
		/*for(int i = 0; i < vec_size; ++i){
			if(abs(cpu_out[i] - gpu_out[i]) > 0.01)
			{
				printf("%d error!", i);
			}
		}
		*/
		printf("CPU: %8.6f\n", pr_[PIID_CPU]);
		printf("CPU MultiThread: %8.6f\n", pr_[PIID_CPU_MT]);
		printf("CPU OpenMP: %8.6f\n", pr_[PIID_CPU_OMP]);
	}

	void Execute(bool isPerfCPUBench){
		InitializeData();
		BenchmarkHelper bh;
		
		if(isPerfCPUBench) ExecuteOnCPU();

		pGP_ = new GraphicProcessor(vec_size);
		pGLSM_ = new glShaderManager;
		pShader_ = pGLSM_->loadfromMemory(NULL, saxpy_ps);
		pGP_ -> RegisterKernel(this);
		pGP_ -> SetCacheOptimization(blockSize_);

		vector<GLuint> arrIDs = pGP_->AllocArrays(2);
		
		pGP_ -> SetArrayInputStage(arrIDs[ARRAY_X_STAGE], ARRAY_X_STAGE);
		pGP_ -> SetArrayInputStage(arrIDs[ARRAY_OUTPUT_STAGE], ARRAY_OUTPUT_STAGE);

		tr.StartTimer();
		pGP_ -> WriteArray(&(x_[0]), arrIDs[ARRAY_X_STAGE]);
		
		pGP_ -> PerformComputationMultiAttachments(arrIDs[ARRAY_OUTPUT_STAGE]);

		pGP_ -> ReadLastWriteBuffer(&(gpu_out[0]));
		pr_[PIID_GPU] = tr.EndTimer();
		pGP_ -> FreeArrays(arrIDs);
		//------------------------------------------
		
		printVector(&(gpu_out[0]), 10);
		printVector(&(cpu_out[0]), 10);

		printf("GPU : %8.6f\nGPU Kernel: %8.6f\n", pr_[PIID_GPU], pr_[PIID_GPU_KR]);
		
	}

	void CreateKernelEnv(){
		pShader_->begin();

		pShader_->setUniform1i("x", ARRAY_X_STAGE);
		pShader_->setUniform1f("alpha", a_);

		tr_kernel.StartTimer();
	}

	void DestoryKernelEnv(){
		pr_[PIID_GPU_KR] = tr_kernel.EndTimer();
		pShader_->end();
	}

	bool IterateCalculate(GLenum srcAttachment, GLenum* changedAttachment)
	{	
		static int it = 0;
		if(++it < itnum_) {
			return true;
		}
		return false;
	}

	SaxpyKernel(int vsize, int blockSize) :	vec_size(vsize), blockSize_(blockSize), pr_(5), 
									pGP_(NULL), pGLSM_(NULL),
									x_(vec_size), y_(vec_size), cpu_out(vec_size), gpu_out(vec_size),
									itnum_(20)
	{
	}

	virtual ~SaxpyKernel(void){
		delete pGLSM_;
		delete pGP_;
	}

protected:
};
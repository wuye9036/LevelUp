#pragma once

#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <xmmintrin.h>

#include "aligned_allocator.h"
#include "graphicprocessor.h"

static const char mr_ps[] = \
"uniform sampler2DRect r1;"\
"uniform sampler2DRect r2;"\
"uniform sampler2DRect r3;"\
"uniform sampler2DRect r4;"\
"void main()"\
"{"\
"	vec4 v1 = texture2DRect(r1, gl_TexCoord[0].st);"\
"	vec4 v2 = texture2DRect(r2, gl_TexCoord[0].st);"\
"	vec4 v3 = texture2DRect(r3, gl_TexCoord[0].st);"\
"	vec4 v4 = texture2DRect(r4, gl_TexCoord[0].st);"\
"	vec4 w = vec4(0.25);"
"	mat4 m = mat4(v1, v2, v3, v4);"\
"	vec4 ov = m*w;"
"	gl_FragColor = ov;"\
"}";
/*



*/
struct MR_Data
{
	float*			a;
	float**		r;
	float*			out;
	int				itnum;
};

#define ARRAY_R1_STAGE 0
#define ARRAY_R2_STAGE 1
#define ARRAY_R3_STAGE 2
#define ARRAY_R4_STAGE 3
#define ARRAY_OUTPUT_STAGE_MR 4

class MRKernel :
	public Kernel
{
	GraphicProcessor*	pGP_;
	glShaderManager*	pGLSM_;
	glShader*				pShader_;
	PerformanceReport	pr_;

	int		blockSize_;
	int		vec_size;

	int		itnum_;
	float	a_[4];
	vector<float, aligned_allocator<float, 16> > r1_;
	vector<float, aligned_allocator<float, 16> > r2_;
	vector<float, aligned_allocator<float, 16> > r3_;
	vector<float, aligned_allocator<float, 16> > r4_;

	vector<float, aligned_allocator<float, 16> > cpu_out;
	vector<float, aligned_allocator<float, 16> > gpu_out;

	Timer tr, tr_kernel;

	static DWORD WINAPI LoopThreadFunction(LPVOID pInput)
	{
		DoCPUBenchmark((TEI*)pInput);
		return TRUE;
	}

	static void MR_C(float* out, float* a, float* r[], int n)
	{
		for(int i = 0; i < n; ++i){
			out[i] = a[0] * r[0][i] + a[1] * r[1][i] + a[2] * r[2][i];// + a[3] * r[3][i];
		}
	}
	static void MR_SSE(float* out, float* a, float* r[], int n)
	{
		__m128 w1, w2, w3, w4, r1, r2, r3, r4;
		w1 = _mm_load_ps1(&(a[0]));
		w2 = _mm_load_ps1(&(a[1]));
		w3 = _mm_load_ps1(&(a[2]));
		w4 = _mm_load_ps1(&(a[3]));

		float* pr[4];
		pr[0] = r[0];
		pr[1] = r[1];
		pr[2] = r[2];
		pr[3] = r[3];

		float* pr0, *pr1, *pr2, *pr3;
		pr0 = pr[0];
		pr1 = pr[1];
		pr2 = pr[2];
		pr3 = pr[3];
		for(int i = 0; i < n; i+=8)
		{
			__asm{
				push eax;
				mov eax, [pr0];
				mov eax, [pr1];
				mov eax, [pr2];
				mov eax, [pr3];
				pop eax
			}

			r1 = _mm_load_ps(pr[0]);
			r2 = _mm_load_ps(pr[1]);
			r3 = _mm_load_ps(pr[2]);
			r4 = _mm_load_ps(pr[3]);

			r1 = _mm_mul_ps(r1, w1);
			r2 = _mm_mul_ps(r2, w2);
			r3 = _mm_mul_ps(r3, w3);
			r4 = _mm_mul_ps(r4, w4);

			r1 = _mm_add_ps(r1, r2);
			r3 = _mm_add_ps(r3, r4);
			r1 = _mm_add_ps(r1, r3);

			_mm_stream_ps(out, r1);

			r1 = _mm_load_ps(pr[0]+4);
			r2 = _mm_load_ps(pr[1]+4);
			r3 = _mm_load_ps(pr[2]+4);
			r4 = _mm_load_ps(pr[3]+4);

			r1 = _mm_mul_ps(r1, w1);
			r2 = _mm_mul_ps(r2, w2);
			r3 = _mm_mul_ps(r3, w3);
			r4 = _mm_mul_ps(r4, w4);

			r1 = _mm_add_ps(r1, r2);
			r3 = _mm_add_ps(r3, r4);
			r1 = _mm_add_ps(r1, r3);

			_mm_stream_ps(out+4, r1);

			pr[0]+=8;
			pr[1]+=8;
			pr[2]+=8;
			pr[3]+=8;

			out+=8;
		}
	}

	static void DoCPUBenchmark(TEI* pInfo)
	{
		MR_Data* data = (MR_Data*)(pInfo->data);

		for(int it = 0; it < data->itnum; ++it){
			float* pr[4];
			pr[0] = data->r[0] + pInfo->range_begin; 
			pr[1] = data->r[1] + pInfo->range_begin; 
			pr[2] = data->r[2] + pInfo->range_begin; 
			pr[3] = data->r[3] + pInfo->range_begin;
			MR_SSE(&(data->out[pInfo->range_begin]), data->a, pr, pInfo->range_end - pInfo->range_begin);
		}
	}
public:

	void InitializeData()
	{
		printf("Now Initialize the data. Please Waiting...\n");
		srand(uint32(time(NULL)));
		a_[0] = a_[1] = a_[2] = a_[3] = float(rand()) / float(RAND_MAX);
		for(int i = 0; i < vec_size; ++i){
			r1_[i] = r2_[i] = r3_[i] = r4_[i] = float(rand()) / float(RAND_MAX);
		}
		printf("Data Initialize Done.\n");
	}

	void ExecuteOnCPU(){

		float* pr[4];
		pr[0] = &(r1_[0]);
		pr[1] = &(r2_[0]);
		pr[2] = &(r3_[0]);
		pr[3] = &(r4_[0]);

		MR_Data data;
		data.a = a_;
		data.out = &(cpu_out[0]);
		data.r = pr;
		data.itnum = itnum_;

		//
		tr.StartTimer();
		for(int i = 0; i < itnum_; ++i){
			MR_SSE(data.out, data.a, data.r, vec_size);
		}
		double sse_time = tr.EndTimer();
		printf("CPU SSE: %8.6f\n", sse_time);

		tr.StartTimer();
		for(int i = 0; i < itnum_; ++i){
			MR_C(data.out, data.a, data.r, vec_size);
		}
		pr_[PIID_CPU] = tr.EndTimer();

		//... ... Do CPU Benchmark ... ...
		data.out = &(gpu_out[0]);
		ThreadExecutionInfos teis_mt(&data, 0, vec_size, 4, sizeof(float), 16);

		HANDLE hThreads[4];
		tr.StartTimer();
		for(int i = 0; i < 4; ++i)
		{
			hThreads[i] = CreateThread(NULL, 0, LoopThreadFunction, &(teis_mt[i]), 0, NULL);
		}
		WaitForMultipleObjects(4, hThreads, TRUE, INFINITE);
		pr_[PIID_CPU_MT] = tr.EndTimer();

		printf("CPU: %8.6f\n", pr_[PIID_CPU]);
		printf("CPU MultiThread: %8.6f\n", pr_[PIID_CPU_MT]);
	}

	void Execute(bool isPerfCPUBench){
		InitializeData();
		BenchmarkHelper bh;

		if(isPerfCPUBench) ExecuteOnCPU();

		pGP_ = new GraphicProcessor(vec_size);
		pGLSM_ = new glShaderManager;
		pShader_ = pGLSM_->loadfromMemory(NULL, mr_ps);
		pGP_ -> RegisterKernel(this);
		pGP_ -> SetCacheOptimization(blockSize_);

		vector<GLuint> arrIDs = pGP_->AllocArrays(5);

		pGP_ -> SetArrayInputStage(arrIDs[ARRAY_R1_STAGE], ARRAY_R1_STAGE);
		pGP_ -> SetArrayInputStage(arrIDs[ARRAY_R2_STAGE], ARRAY_R2_STAGE);
		pGP_ -> SetArrayInputStage(arrIDs[ARRAY_R3_STAGE], ARRAY_R3_STAGE);
		pGP_ -> SetArrayInputStage(arrIDs[ARRAY_R4_STAGE], ARRAY_R4_STAGE);

		tr.StartTimer();
		pGP_ -> WriteArray(&(r1_[0]), arrIDs[ARRAY_R1_STAGE]);
		pGP_ -> WriteArray(&(r2_[0]), arrIDs[ARRAY_R2_STAGE]);
		pGP_ -> WriteArray(&(r3_[0]), arrIDs[ARRAY_R3_STAGE]);
		pGP_ -> WriteArray(&(r4_[0]), arrIDs[ARRAY_R4_STAGE]);

		pGP_ -> PerformComputationMultiAttachments(arrIDs[ARRAY_OUTPUT_STAGE_MR]);

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

		pShader_->setUniform1i("r1", ARRAY_R1_STAGE);
		pShader_->setUniform1i("r2", ARRAY_R2_STAGE);
		pShader_->setUniform1i("r3", ARRAY_R3_STAGE);
		pShader_->setUniform1i("r4", ARRAY_R4_STAGE);
		//pShader_->setUniform4f("w", a_[0], a_[1], a_[2], a_[3]);

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

	MRKernel(int vsize, int blockSize) :	vec_size(vsize), blockSize_(blockSize), pr_(5), 
		pGP_(NULL), pGLSM_(NULL),
		r1_(vec_size), r2_(vec_size),r3_(vec_size),r4_(vec_size), cpu_out(vec_size), gpu_out(vec_size),
		itnum_(20)
	{
	}

	virtual ~MRKernel(void){
		delete pGLSM_;
		delete pGP_;
	}
	
protected:
};
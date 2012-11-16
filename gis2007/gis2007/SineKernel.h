#pragma once

#include <omp.h>

#include "GraphicProcessor.h"
#include "Timer.h"

static char vs[] = "#version 110\n"                 \
"void main(void)"                                           \
"{"                                                         \
"   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"\
"}\0";

static char ps[] = "uniform sampler2DRect x;"\
"void main (void)"\
"{"\
"vec4 t = texture2DRect(x, gl_TexCoord[0].st) + vec4(0.02, 0.04, 0.06, 0.08);"\
"gl_FragColor = sin(t);"\
"}\0";

static int N;
const int threadNum = 4;

struct CPUBenchInfo
{
	float* out;
	int		threadId;
	int		threadNum;
};

static DWORD WINAPI LoopThreadFunction (LPVOID input) {

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
			out[j] = sin(out[j]);
		}
	}
	return TRUE;
}

typedef float (*F) (float);

class SineKernel: public Kernel
{
	static CRITICAL_SECTION cs;
	Timer tr,tr2;
	double ecpu, egpu, egpu_min,ecpu_mt,ecpu_omp;

	vector<float> test;
	vector<float> out_gpu;
	vector<float> out_cpu;

	GraphicProcessor* pgp;

	glShaderManager* glsm_;
	glShader*			pshader_;
	int						iternum;
	uint32				aid;

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
		for(int i = 0; i < 100; ++i){
			for(int j = start_pos; j < end_pos; ++j)
			{
				out[j] +=  0.02f * ((j % 4) + 1);
				out[j] = sin(out[j]);
			}
		}
	}

	SineKernel(uint32 nVec):out_cpu(nVec),pgp(NULL), iternum(0), aid(0), test(nVec), out_gpu(nVec),  glsm_(NULL)//,
	{
		N = nVec;
		for(int i = 0; i < N; ++i){test[i] = 0.0f;}
	}

	virtual ~SineKernel(){
		delete glsm_;
		delete pgp;
	}

	void Execute(){
		BenchmarkHelper bh;

		printf("The Number of Processors : %d\n", omp_get_num_procs());
		printf("The Maximum Number of Hardware Threads : %d\n", omp_get_max_threads());

		//set this thread highest priority for timing exactly

		//--------------------------------------------------------------------------
		omp_set_num_threads(4);
		tr.StartTimer();
#pragma omp parallel for
		for(int threadid = 0 ; threadid < 4; ++threadid){
			DoCPUBenchmark(out_cpu, threadid);
		}
		ecpu_omp = tr.EndTimer();
		//--------------------------------------------------------------------------

		//--------------------------------------------------------------------------
		tr.StartTimer();
		for(int threadid = 0 ; threadid < 4; ++threadid){
			DoCPUBenchmark(out_cpu, threadid);
		}
		double ecpu = tr.EndTimer();
		//---------------------------------------------------------------------------

		//---------------------------------------------------------------------------
		tr.StartTimer();
		HANDLE hThreads[4];
		CPUBenchInfo cb[4];
		for(int i = 0; i < 4; ++i)
		{
			cb[i].out = &(out_cpu[0]);
			cb[i].threadId = i;
			cb[i].threadNum = 4;
			hThreads[i] = CreateThread(NULL, 0, LoopThreadFunction, &cb, 0, NULL);
		}
		WaitForMultipleObjects(4, hThreads, TRUE, INFINITE);
		ecpu_mt = tr.EndTimer();
		//----------------------------------------------------------------------------

		//----------------------------------------------------------------------------
		pgp = new GraphicProcessor(N);
		glsm_ = new glShaderManager;
		pshader_ = glsm_->loadfromMemory(vs, ps);
		pgp->RegisterKernel(this);
		//allocate video memory blocks
		vector<GLuint> arrIDs = pgp->AllocArrays(2);	
		//set input stages
		pgp->SetArrayInputStage(arrIDs[0], 0);
		pgp->SetArrayInputStage(arrIDs[1], 1);
		pgp->WriteArray(&(test[0]), arrIDs[1]);
		tr.StartTimer();
		pgp->PerformComputationMultiAttachments(arrIDs[0], arrIDs[1]);
		//read data from frame buffer
		pgp->ReadLastWriteBuffer(&(out_gpu[0]));
		egpu = tr.EndTimer();
		//free video memory
		pgp->FreeArrays(arrIDs);
		//----------------------------------------------------------------------------

		printVector(&(out_gpu[0]), 20);
		printVector(&(out_cpu[0]), 20);

		cout << "CPU MultiThread:" << ecpu_mt << endl 
			<< "CPU OpenMP:" << ecpu_omp << endl 
			<< "CPU:" << ecpu << endl 
			<< "GPU:" << egpu << endl 
			<< "GPU Kernel:" << egpu_min << endl;
	}

	void CreateKernelEnv()
	{
		pshader_->begin();
		pshader_->setUniform1i("x", 1);
		tr2.StartTimer();
	}

	void DestoryKernelEnv(){
		egpu_min = tr2.EndTimer();
		pshader_->end();
	}

	bool IterateCalculate(GLenum originAttachment, GLenum* changedAttachment)
	{
		if(++iternum < 100){
			*changedAttachment = (originAttachment == 0) ? 1 : 0;
			pshader_->setUniform1i("x", pgp->GetArrayStateByOutputAttachment(originAttachment)->arrInputStage);
			return true;
		}
		return false;
	}
};
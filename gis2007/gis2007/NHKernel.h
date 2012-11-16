#pragma once
#include "graphicprocessor.h"

#pragma once

#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <xmmintrin.h>

#include "aligned_allocator.h"
#include "GraphicProcessor.h"

struct NH_Data
{
	float*		x;
	int			pitch;
	float*		out;
	int			itnum;
};

static vector<float, aligned_allocator<float, 16> > temp_mem;

static int sqrt(int x)
{
	return int(sqrt(double(x)));
}

static const char nh_ps[] = \
"uniform sampler2DRect x;"\
"void main()"\
"{"\
"	float t00 = texture2DRect(x, (gl_TexCoord[0].st + vec2(-1.0, -1.0))).x;"\
"	float t01 = texture2DRect(x, (gl_TexCoord[0].st + vec2(-1.0, 0.0))).x;"\
"	float t02 = texture2DRect(x, (gl_TexCoord[0].st + vec2(-1.0, 1.0))).x;"\
"	float t10 = texture2DRect(x, (gl_TexCoord[0].st + vec2(-0.0, -1.0))).x;"\
"	float t11 = texture2DRect(x, (gl_TexCoord[0].st + vec2(-0.0, 0.0))).x;"\
"	float t12 = texture2DRect(x, (gl_TexCoord[0].st + vec2(-0.0, 1.0))).x;"\
"	float t20 = texture2DRect(x, (gl_TexCoord[0].st + vec2(1.0, -1.0))).x;"\
"	float t21 = texture2DRect(x, (gl_TexCoord[0].st + vec2(1.0, 0.0))).x;"\
"	float t22 = texture2DRect(x, (gl_TexCoord[0].st + vec2(1.0, 1.0))).x;"\
"	gl_FragColor.x = t00+t01+t02+t10+t11+t12+t20+t21+t22;"\
"}";

/*
HLSL
uniform sampler2D x;
float4 main(float2 tex:TEXCOORD0):COLOR0
{
	float t00 = tex2D(x, (tex + float2(-1.0, -1.0))).x;
	float t01 = tex2D(x, (tex + float2(-1.0, 0.0))).x;
	float t02 = tex2D(x, (tex + float2(-1.0, 1.0))).x;
	float t10 = tex2D(x, (tex + float2(-0.0, -1.0))).x;
	float t11 = tex2D(x, (tex + float2(-0.0, 0.0))).x;
	float t12 = tex2D(x, (tex + float2(-0.0, 1.0))).x;
	float t20 = tex2D(x, (tex + float2(1.0, -1.0))).x;
	float t21 = tex2D(x, (tex + float2(1.0, 0.0))).x;
	float t22 = tex2D(x, (tex + float2(1.0, 1.0))).x;
	return float4(t00+t01+t02+t10+t11+t12+t20+t21+t22, 0.0f, 0.0f, 0.0f);
};
*/
#define ARRAY_X_STAGE 0
#define ARRAY_OUTPUT_STAGE 1

class NHKernel :
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
	
	vector<float, aligned_allocator<float, 16> > cpu_out;
	vector<float, aligned_allocator<float, 16> > gpu_out;

	Timer tr, tr_kernel;

	static DWORD WINAPI LoopThreadFunction(LPVOID pInput)
	{
		TEI* pInfo = (TEI*)pInput;
		NH_Data* data = (NH_Data*)(pInfo->data);

		int chunk_id = pInfo->range_begin / (data->pitch * data->pitch / 4);
		int chunk_size = pInfo->range_end - pInfo->range_begin;
		float*	pos;
		float* out_pos;
		float* trans_out_pos;
		float* temp = &(temp_mem[0]);
		switch (chunk_id) {
case 0 : {
	pos = 0 + data->x;
	out_pos = data->out + 0;
	temp += 0;
	break;
		 }
case 1 :{
	pos = data->x + data->pitch / 2;
	out_pos = data->out + data->pitch / 2;
	temp += (data->pitch / 2);
	break;
		}
case 2:{
	pos = data->x + data->pitch * data->pitch / 2;
	out_pos = data->out + data->pitch * data->pitch / 2;
	temp += (data->pitch * data->pitch / 2);
	break;
	   }
case 3:{
	pos = data->x + (data->pitch + 1)* data->pitch / 2;
	out_pos = data->out + (data->pitch + 1)* data->pitch / 2;
	temp += ( (data->pitch + 1)* data->pitch / 2);
	break;
	   }
		}
		for(int i = 0; i < data->itnum; ++i){
			//NH_SSE(out_pos, pos, pInfo->range_end - pInfo->range_begin, data->pitch);
			//NH_SSE_Transpose(temp, out_pos, pInfo->range_end - pInfo->range_begin, data->pitch); //此步是分块矩阵的就地转置。
			//NH_SSE(out_pos, temp, pInfo->range_end - pInfo->range_begin, data->pitch);
			NH_C(out_pos, pos, pInfo->range_end - pInfo->range_begin, data->pitch);
		}
		return TRUE;
	}

	static void NH_C(float* out, float* x, int n, int pitch)
	{
		n = sqrt(n);

		for(int i = 1; i < n - 1; ++i)
		{
			for(int j = 1; j < n -1; ++j)
			{
				out[i*pitch+j] =	x[i*pitch+j - 1*pitch - 1] + x[i*pitch+j - 1*pitch + 0] + x[i*pitch+j - 1*pitch + 1] +
										x[i*pitch+j + 0*pitch - 1] + x[i*pitch+j + 0*pitch + 0] + x[i*pitch+j + 0*pitch + 1] +
										x[i*pitch+j + 1*pitch - 1] + x[i*pitch+j + 1*pitch + 0] + x[i*pitch+j + 1*pitch + 1];
			}
		}
	}

#define PF2M(pf) (*((__m128*)(pf)))
#define PM2PF(pm) ((__m128*)(pm))
#define M2PF(m) ((__m128*)(&(m)))
#define F2M(f) (*((__m128*)&(f)))

	static void NH_SSE(float* out, float* x, int n, int pitch)
	{
		n = sqrt(n);
		__m128 x1,x2,x3,x4,lv,x5;
		//__m128 temp[pitch];

		//先做横向
		//先做第一至四行
		float* pos = x;
		float* pos_out = out;
		for(int i = 0; i < n; i +=4)
		{
			x1 = _mm_load_ps(pos);
			x2 = _mm_load_ps(pos+pitch);
			x3 = _mm_load_ps(pos+pitch*2);
			x4 = _mm_load_ps(pos+pitch*3);
			
			x1 = _mm_add_ps(x1, x2);
			x4 = _mm_add_ps(x4, x3);
			x3 = _mm_add_ps(x3, x1);
			x2 = _mm_add_ps(x2, x4);
			
			_mm_stream_ps(pos_out, x1);
			_mm_stream_ps(pos_out+pitch, x3);
			_mm_stream_ps(pos_out+pitch*2, x2);
			_mm_stream_ps(pos_out+pitch*3, x4);
			pos+=4;
			pos_out+=4;
		}

		//做其余的行数
		for(int i = 3; i < n-4; i+=4)
		{
			pos = x + pitch * i;
			pos_out = out + pitch * i;
			for(int j = 0; j < n; j+=4)
			{
				lv = _mm_load_ps(pos_out);
				x1 = _mm_load_ps(pos);
				x2 = _mm_load_ps(pos+pitch);
				x3 = _mm_load_ps(pos+pitch*2);
				x4 = _mm_load_ps(pos+pitch*3);
				x5 = _mm_load_ps(pos+pitch*4);

				lv = _mm_add_ps(lv, x2);
				x5 = _mm_add_ps(x5, x4);
				x1 = _mm_add_ps(x1, x2);
				x2 = _mm_add_ps(x2, x4);
				x1 = _mm_add_ps(x1, x3);
				x2 = _mm_add_ps(x2, x3);
				x3 = _mm_add_ps(x3, x5);

				_mm_stream_ps(pos_out, lv);

				_mm_stream_ps(pos_out+pitch, x1);
				_mm_stream_ps(pos_out+pitch*2, x2);
				_mm_stream_ps(pos_out+pitch*3, x3);
				_mm_stream_ps(pos_out+pitch*4, x5);

				pos+=4;
				pos_out +=4;
			}
		}
	}

	static void NH_SSE_Transpose(float* out, float* x, int n, int pitch)
	{
		__m128 mat[4], tmp[4];

		n = sqrt(n);

		//i, j 分别是块的行列号
		for(int i = 0; i < n/4; ++i)
		{
			for(int j = 0; j < n/4; ++j)
			{
				float* inpos = x + i *4 * pitch + j * 4;
				float* outpos = out + j * 4 * pitch +i * 4;

				for(int k = 0; k < 4; ++k)
				{
					mat[k] = _mm_load_ps(inpos + pitch * k);
				}		
				
				tmp[0] = _mm_shuffle_ps(mat[0], mat[1], 0x44);
				tmp[1] = _mm_shuffle_ps(mat[2], mat[3], 0x44);
				tmp[2] = _mm_shuffle_ps(mat[0], mat[1], 0xEE);
				tmp[3] = _mm_shuffle_ps(mat[2], mat[3], 0xEE);      


				mat[0] = _mm_shuffle_ps(tmp[0], tmp[1], 0x88);
				mat[1] = _mm_shuffle_ps(tmp[0], tmp[1], 0xDD);
				mat[2] = _mm_shuffle_ps(tmp[2], tmp[3], 0x88);          
				mat[3] = _mm_shuffle_ps(tmp[2], tmp[3], 0xDD); 

				for(int k = 0; k < 4; ++k)
				{
					_mm_stream_ps(outpos + pitch * k, mat[k]);
				}		
			}
		}
	}

	static void DoCPUBenchmark(TEI* pInfo)
	{
		/*
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
		*/
	}
public:

	void InitializeData()
	{
		printf("Now Initialize the data. Please Waiting...\n");
		srand(uint32(time(NULL)));
		for(int i = 0; i < vec_size; ++i){
			x_[i] = rand() / float(RAND_MAX);
		}
		printf("Data Initialize Done.\n");
	}

	void ExecuteOnCPU(){
		temp_mem.resize(vec_size);

		NH_Data data;
		data.pitch = sqrt(vec_size);
		data.out = &(cpu_out[0]);
		data.x = &(x_[0]);
		data.itnum = itnum_;

		/*
		tr.StartTimer();
		for(int i = 0; i < itnum_; ++i){
			NH_SSE(data.out, data.x, vec_size, sqrt(vec_size));
			NH_SSE_Transpose(&(temp_mem[0]), data.out, vec_size, sqrt(vec_size)); //此步是分块矩阵的就地转置。
			NH_SSE(data.out, data.x, vec_size, sqrt(vec_size));
		}
		double sse_time = tr.EndTimer();
		printf("CPU SSE: %8.6f\n", sse_time);
		*/

		tr.StartTimer();
		for(int i = 0; i < itnum_; ++i){
			NH_C(data.out, data.x, vec_size, sqrt(vec_size));
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
		
		/*
		for(int i = 0; i < vec_size; ++i){
			if(abs(cpu_out[i] - gpu_out[i]) > 0.01)	{
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
		pShader_ = pGLSM_->loadfromMemory(NULL, nh_ps);
		printf("\nload shader finished.\n");
		pGP_ -> RegisterKernel(this);
		pGP_ -> SetCacheOptimization(blockSize_);

		vector<GLuint> arrIDs = pGP_->AllocArrays(2);
		printf("\nalloc texture\n");

		pGP_ -> SetArrayInputStage(arrIDs[ARRAY_X_STAGE], ARRAY_X_STAGE);
		pGP_ -> SetArrayInputStage(arrIDs[ARRAY_OUTPUT_STAGE], ARRAY_OUTPUT_STAGE);

		printf("\nset input stage\n");
		tr.StartTimer();
		pGP_ -> WriteArray(&(x_[0]), arrIDs[ARRAY_X_STAGE]);

		printf("\nwrite array\n");
		pGP_ -> PerformComputationMultiAttachments(arrIDs[ARRAY_OUTPUT_STAGE]);

		printf("\nwrite array\n");
		pGP_ -> ReadLastWriteBuffer(&(gpu_out[0]));
		pr_[PIID_GPU] = tr.EndTimer();
		pGP_ -> FreeArrays(arrIDs);
		//------------------------------------------

		//printVector(&(gpu_out[0]), 3);
		printVector(&(x_[0]), 3);
		printVector(&(x_[sqrt(vec_size)]), 3);
		printVector(&(x_[sqrt(vec_size)*2]), 3);
		printVector(&(cpu_out[sqrt(vec_size)]), 3);

		printf("GPU : %8.6f\nGPU Kernel: %8.6f\n", pr_[PIID_GPU], pr_[PIID_GPU_KR]);

	}

	void CreateKernelEnv(){
		pShader_->begin();

		pShader_->setUniform1i("x", ARRAY_X_STAGE);

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

	NHKernel(int vsize, int blockSize) :	vec_size(vsize), blockSize_(blockSize), pr_(5), 
		pGP_(NULL), pGLSM_(NULL),
		x_(vec_size), cpu_out(vec_size), gpu_out(vec_size),
		itnum_(40)
	{
	}

	virtual ~NHKernel(void){
		delete pGLSM_;
		delete pGP_;
	}

protected:
};
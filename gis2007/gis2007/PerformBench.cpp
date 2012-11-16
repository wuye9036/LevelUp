// PerformBench.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <xmmintrin.h>
#include "timer.h"
#include "aligned_allocator.h"
#include <vector>


using namespace std;

template<class T, class Allocator>
double CalcSpeedM(const vector<T, Allocator>& vec, int nPerf, double time){
	return double(sizeof(T)*vec.size())/time/1024.0/1024.0*nPerf;
}

//内存拷贝速度测试
template<class T>
void memcpy_C(T* dest, const T* src, size_t nElem){
	for(int i = 0; i < nElem; ++i){
		dest[i] = src[i];
	}
}

//SSE内存拷贝测试
void memcpy_SSE(void* pdest, const void* psrc, size_t size)
{
	const float* src = (float*)psrc;
	float* dest = (float*)pdest;

	int nBatch = size / 128;

	__m128 m1, m2, m3, m4, m5, m6, m7, m8;
	
	for(int i = 0; i < nBatch; ++i){
		m1 = _mm_load_ps(src);
		m2 = _mm_load_ps(src+4);
		m3 = _mm_load_ps(src+8);
		m4 = _mm_load_ps(src+12);
		m5 = _mm_load_ps(src+16);
		m6 = _mm_load_ps(src+20);
		m7 = _mm_load_ps(src+24);
		m8 = _mm_load_ps(src+28);

		_mm_stream_ps(dest, m1);
		_mm_stream_ps(dest+4, m2);
		_mm_stream_ps(dest+8, m3);
		_mm_stream_ps(dest+12, m4);
		_mm_stream_ps(dest+16, m5);
		_mm_stream_ps(dest+20, m6);
		_mm_stream_ps(dest+24, m7);
		_mm_stream_ps(dest+28, m8);

		src += 32;
		dest += 32;
	}
}

//SSE内存拷贝测试
void memcpy_SSE_plus(void* pdest, const void* psrc, size_t size)
{
	const float* src = (float*)psrc;
	float* dest = (float*)pdest;

	//测试总共要进行的操作批次，每次128字节（16×8）
	int nBatch = size / 128;

	//计算需要的预读缓存的次数，每次读512B
	int nCachePrefetch = nBatch / (512 / 128);

	__m128 m1, m2, m3, m4, m5, m6, m7, m8;

	for(int i = 0; i < nCachePrefetch; ++i){
		_asm{
			push	eax;
			push	ecx;
			lea		eax, [src]
			mov	ecx, dword ptr[eax];
			mov	ecx, dword ptr[eax+64];
			mov	ecx, dword ptr[eax+128];
			mov	ecx, dword ptr[eax+192];
			mov	ecx, dword ptr[eax+256];
			mov	ecx, dword ptr[eax+320];
			mov	ecx, dword ptr[eax+384];
			mov	ecx, dword ptr[eax+448];
			pop	ecx;
			pop	eax
		}

		for(int i = 0; i < 4; ++i){
			_mm_prefetch((char*)src+512, _MM_HINT_NTA);
			m1 = _mm_load_ps(src);
			m2 = _mm_load_ps(src+4);
			m3 = _mm_load_ps(src+8);
			m4 = _mm_load_ps(src+12);
			m5 = _mm_load_ps(src+16);
			m6 = _mm_load_ps(src+20);
			m7 = _mm_load_ps(src+24);
			m8 = _mm_load_ps(src+28);

			_mm_stream_ps(dest, m1);
			_mm_stream_ps(dest+4, m2);
			_mm_stream_ps(dest+8, m3);
			_mm_stream_ps(dest+12, m4);
			_mm_stream_ps(dest+16, m5);
			_mm_stream_ps(dest+20, m6);
			_mm_stream_ps(dest+24, m7);
			_mm_stream_ps(dest+28, m8);

			src += 32;
			dest += 32;
		}
	}
}

//Saxpy浮点性能测试
void saxpy_C(float* out, float a, float* x, float* y, int n)
{
	for(int i = 0; i < n; ++i)	{
			out[i] = x[i] * a + y[i];
		}
}

//SSE Saxpy浮点性能测试
void saxpy_SSE_Opt1(float* out, float a, float* x, float* y, int n)
{
	//Validate Alignment
	if(	size_t(out) % 16 != 0 ||
		size_t(x) % 16 != 0 ||
		size_t(y) % 16 != 0 ||
		n % 4 !=0
		) {
			printf("输入数据未对齐, 无法使用sse加速!");
			return;
	}

	__m128 _a = _mm_load_ps1(&a);

	__m128 _x, _y, _o;
	//_mm_prefetch((const char*)x, _MM_HINT_T0);
	//_mm_prefetch((const char*)y, _MM_HINT_T0);

	for(int i = 0; i < n; i += 8){
		_x = _mm_load_ps(x);
		_y = _mm_load_ps(y);
		_o = _mm_mul_ps(_x, _a);
		_o = _mm_add_ps(_o, _y);

		_mm_store_ps(out, _o);

		_x = _mm_load_ps(x+4);			
		_y = _mm_load_ps(y+4);			
		_o = _mm_mul_ps(_x, _a);		
		_o = _mm_add_ps(_o, _y);

		_mm_store_ps(out+4, _o);

		x+=8;
		y+=8;
		out+=8;
	}

	if( n % 2 == 1){
		__m128 _x = _mm_load_ps(x + 4);
		__m128 _y = _mm_load_ps(y + 4);
		__m128 _o = _mm_mul_ps(_x, _a);
		_o = _mm_add_ps(_o, _y);
		_mm_store_ps(out + 4, _o);
	}
}

void saxpy_SSE_Opt2(float* out, float a, float* x, float* y, int n)
{
	//Validate Alignment
	/*
	if(	size_t(out) % 16 != 0 ||
		size_t(x) % 16 != 0 ||
		size_t(y) % 16 != 0 ||
		n % 4 !=0
		) {
			printf("输入数据未对齐, 无法使用sse加速!");
			return;
	}
	*/

	__m128 _a = _mm_load_ps1(&a);

	__m128 _x, _y, _o;
	//_mm_prefetch((const char*)x, _MM_HINT_T0);
	//_mm_prefetch((const char*)y, _MM_HINT_T0);

	for(int i = 0; i < n; i += 8){
		_x = _mm_load_ps(x);
		_y = _mm_load_ps(y);
		_x = _mm_mul_ps(_x, _a);
		_x = _mm_add_ps(_x, _y);

		_mm_stream_ps(out, _x);

		_x = _mm_load_ps(x+4);			
		_y = _mm_load_ps(y+4);			
		_x = _mm_mul_ps(_x, _a);		
		_x = _mm_add_ps(_x, _y);

		_mm_stream_ps(out+4, _x);

		x+=8;
		y+=8;
		out+=8;
	}

	if( n % 2 == 1){
		_x = _mm_load_ps(x + 4);
		_y = _mm_load_ps(y + 4);
		_x = _mm_mul_ps(_x, _a);
		_x = _mm_add_ps(_x, _y);
		_mm_stream_ps(out + 4, _x);
	}
}

void saxpy_SSE_Opt3(float* out, float a, float* x, float* y, int n)
{
	//Validate Alignment
	/*
	if(	size_t(out) % 16 != 0 ||
	size_t(x) % 16 != 0 ||
	size_t(y) % 16 != 0 ||
	n % 4 !=0
	) {
	printf("输入数据未对齐, 无法使用sse加速!");
	return;
	}
	*/

	__m128 _a = _mm_load_ps1(&a);

	__m128 _x, _y, _o, _x2, _y2, _o2;
	//_mm_prefetch((const char*)x, _MM_HINT_T0);
	//_mm_prefetch((const char*)y, _MM_HINT_T0);

	for(int i = 0; i < n; i += 16){
		_mm_prefetch((const char*)x+64, _MM_HINT_NTA);
		_mm_prefetch((const char*)y+64, _MM_HINT_NTA);

		_x = _mm_load_ps(x);
		_y = _mm_load_ps(y);
		_x = _mm_mul_ps(_x, _a);
		_x = _mm_add_ps(_x, _y);

		_mm_stream_ps(out, _x);

		_x2 = _mm_load_ps(x+4);			
		_y2 = _mm_load_ps(y+4);			
		_x2 = _mm_mul_ps(_x, _a);		
		_x2 = _mm_add_ps(_x, _y);

		_mm_stream_ps(out+4, _x2);

		_x = _mm_load_ps(x+8);
		_y = _mm_load_ps(y+8);
		_x = _mm_mul_ps(_x, _a);
		_x = _mm_add_ps(_x, _y);

		_mm_stream_ps(out+8, _x);

		_x2 = _mm_load_ps(x+12);			
		_y2 = _mm_load_ps(y+12);			
		_x2 = _mm_mul_ps(_x, _a);		
		_x2 = _mm_add_ps(_x, _y);

		_mm_stream_ps(out+12, _x2);

		x+=16;
		y+=16;
		out+=16;
	}

	if( n % 2 == 1){
		__m128 _x = _mm_load_ps(x + 4);
		__m128 _y = _mm_load_ps(y + 4);
		__m128 _o = _mm_mul_ps(_x, _a);
		_o = _mm_add_ps(_o, _y);
		_mm_store_ps(out + 4, _o);
	}
}

void saxpy_C_inner_loop(float* out, float a, float* x, float* y, int n, int loopCount){
	for(int i = 0; i < n; ++i){
		out[i] = x[i];
		int ty = y[i];
		for(int j = 0; j < loopCount; ++j){
			out[i] = out[i] * a + ty;
		}
	}
}

void saxpy_SSE_inner_loop_Opt1(float* out, float a, float* x, float* y, int n, int loopCount){
	__m128 _a = _mm_load_ps1(&a);
	__m128 _x, _y, _x2, _y2,_x3,_y3;
	//_mm_prefetch((const char*)x, _MM_HINT_T0);
	//_mm_prefetch((const char*)y, _MM_HINT_T0);

	for(int i = 0; i < n; i += 12){
		_x = _mm_load_ps(x);
		_y = _mm_load_ps(y);
		_x2 = _mm_load_ps(x+4);
		_y2 = _mm_load_ps(y+4);
		_x3 = _mm_load_ps(x+8);
		_y3 = _mm_load_ps(y+8);
		for(int j = 0; j < loopCount; ++j){
			_x = _mm_mul_ps(_x, _a);
			_x = _mm_add_ps(_x, _y);
			_x2 = _mm_mul_ps(_x2, _a);
			_x2 = _mm_add_ps(_x2, _y);
			_x3 = _mm_mul_ps(_x3, _a);
			_x3 = _mm_add_ps(_x3, _y);
		}
		_mm_stream_ps(out, _x);
		_mm_stream_ps(out+4, _x2);
		_mm_stream_ps(out+8, _x3);
		x+=12;
		y+=12;
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	int nCircles = 1000;
	int vec_size = 1024*1024;
	if(argc > 1){
		vec_size = _ttoi(argv[1]);
	}

	//预备数据
	vector<float, aligned_allocator<float, 16> > src(vec_size);
	vector<float, aligned_allocator<float, 16> > srcy(vec_size);
	vector<float, aligned_allocator<float, 16> > dest(vec_size);

	float*		psrc = &(src[0]);
	float*		psrcy = &(srcy[0]);
	float*		pdest = &(dest[0]);

	Timer tr;
	BenchmarkHelper bh;

	//结果
	double
		copy_memcpy,
		copy_c,
		copy_sse,
		copy_sse_plus;

	double
		flops_C,
		flops_sse_opt1,
		flops_sse_opt2,
		flops_sse_opt3,
		flops_c_inner_loop,
		flops_sse_inner_loop_opt1;

	//执行浮点性能测试
	/*
	memcpy(pdest, psrc, sizeof(float) * vec_size);
	tr.StartTimer();
	for(int i = 0; i < nCircles; ++i) memcpy(pdest, psrc, sizeof(float) * vec_size);
	copy_memcpy = tr.EndTimer();

	memcpy_C(pdest, psrc, vec_size);
	tr.StartTimer();
	for(int i = 0; i < nCircles; ++i) memcpy_C(pdest, psrc, vec_size);
	copy_c = tr.EndTimer();

	memcpy_SSE(pdest, psrc, vec_size);
	tr.StartTimer();
	for(int i = 0; i < nCircles; ++i) memcpy_SSE(pdest, psrc, vec_size*sizeof(float));
	copy_sse = tr.EndTimer();

	memcpy_SSE_plus(pdest, psrc, vec_size);
	tr.StartTimer();
	for(int i = 0; i < nCircles; ++i) memcpy_SSE_plus(pdest, psrc, vec_size*sizeof(float));
	copy_sse_plus = tr.EndTimer();
	*/

	tr.StartTimer();
	for(int i = 0; i < nCircles; ++i) saxpy_C(pdest, 1.927f, psrc, psrcy, vec_size);
	flops_C = tr.EndTimer();

	tr.StartTimer();
	for(int i = 0; i < nCircles; ++i) saxpy_SSE_Opt1(pdest, 1.927f, psrc, psrcy, vec_size);
	flops_sse_opt1 = tr.EndTimer();

	tr.StartTimer();
	for(int i = 0; i < nCircles; ++i) saxpy_SSE_Opt2(pdest, 1.927f, psrc, psrcy, vec_size);
	flops_sse_opt2 = tr.EndTimer();

	tr.StartTimer();
	for(int i = 0; i < nCircles; ++i) saxpy_SSE_Opt3(pdest, 1.927f, psrc, psrcy, vec_size);
	flops_sse_opt3 = tr.EndTimer();

	tr.StartTimer();
	saxpy_C_inner_loop(pdest, 1.927f, psrc, psrcy, vec_size, nCircles);
	flops_c_inner_loop = tr.EndTimer();

	tr.StartTimer();
	saxpy_SSE_inner_loop_Opt1(pdest, 1.927f, psrc, psrcy, vec_size, nCircles);
	flops_sse_inner_loop_opt1 = tr.EndTimer();

	//output
	/*
	printf("Time of Copy via memcpy : %8.6f\n", copy_memcpy);
	printf("The Copy Speed : %8.6f\n", CalcSpeedM(dest, nCircles*2, copy_memcpy));

	printf("Time of Copy via C : %8.6f\n", copy_c);
	printf("The Copy Speed : %8.6f\n", CalcSpeedM(dest, nCircles*2, copy_c));

	printf("Time of Copy via SSE : %8.6f\n", copy_sse);
	printf("The Copy Speed : %8.6f\n", CalcSpeedM(dest, nCircles*2, copy_sse));

	printf("Time of Copy via SSE Plus: %8.6f\n", copy_sse_plus);
	printf("The Copy Speed : %8.6f\n", CalcSpeedM(dest, nCircles*2, copy_sse_plus));
	*/

	printf("Time of Saxpy via C : %8.6f\n", flops_C);
	printf("The Bandwidth : %8.6f\n", CalcSpeedM(dest, nCircles*3, flops_C));
	printf("The MFLOPS : %8.6f\n", CalcSpeedM(dest, nCircles*2/sizeof(float), flops_C));

	printf("Time of Saxpy via SSE Opt1 : %8.6f\n", flops_sse_opt1);
	printf("The Bandwidth : %8.6f\n", CalcSpeedM(dest, nCircles*3, flops_sse_opt1));
	printf("The MFLOPS : %8.6f\n", CalcSpeedM(dest, nCircles*2/sizeof(float), flops_sse_opt1));

	printf("Time of Saxpy via SSE Opt2 : %8.6f\n", flops_sse_opt2);
	printf("The Bandwidth : %8.6f\n", CalcSpeedM(dest, nCircles*3, flops_sse_opt2));
	printf("The MFLOPS : %8.6f\n", CalcSpeedM(dest, nCircles*2/sizeof(float), flops_sse_opt2));

	printf("Time of Saxpy via SSE Opt3 : %8.6f\n", flops_sse_opt3);
	printf("The Bandwidth : %8.6f\n", CalcSpeedM(dest, nCircles*3, flops_sse_opt3));
	printf("The MFLOPS : %8.6f\n", CalcSpeedM(dest, nCircles*2/sizeof(float), flops_sse_opt3));

	printf("Time of Saxpy via C inner loop : %8.6f\n", flops_c_inner_loop);
	printf("The Bandwidth : %8.6f\n", CalcSpeedM(dest, nCircles*3, flops_c_inner_loop));
	printf("The MFLOPS : %8.6f\n", CalcSpeedM(dest, nCircles*2/sizeof(float), flops_c_inner_loop));

	printf("Time of Saxpy via C inner loop : %8.6f\n", flops_sse_inner_loop_opt1);
	printf("The Bandwidth : %8.6f\n", CalcSpeedM(dest, nCircles*3, flops_sse_inner_loop_opt1));
	printf("The MFLOPS : %8.6f\n", CalcSpeedM(dest, nCircles*2/sizeof(float), flops_sse_inner_loop_opt1));

	system("pause");
	return 0;
}


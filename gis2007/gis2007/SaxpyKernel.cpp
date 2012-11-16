#include "SaxpyKernel.h"
#include <xmmintrin.h>
#include <memory>
/*
SaxpyKernel::SaxpyKernel(void)
{
}

SaxpyKernel::~SaxpyKernel(void)
{
}
*/

DWORD WINAPI SaxpyKernel::LoopThreadFunction(LPVOID pInput)
{
	TEI* pInfo = (TEI*)pInput;
	Saxpy_Data* data = (Saxpy_Data*)(pInfo->data);
	for(int i = 0; i < data->itnum; ++i){
		SaxPy_SSE(&(data->out[pInfo->range_begin]), data->a, &(data->x[pInfo->range_begin]), NULL, pInfo->range_end - pInfo->range_begin);
	}
	
	return TRUE;
}

void SaxpyKernel::SaxPy_SSE(float* out, float a, float* x, float* y, int n)
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

	__m128 _x1, _x2, _o1, _o2, _a;
	_a = _mm_load_ps1(&a);

	int i = 0;
	//_mm_prefetch((const char*)x, _MM_HINT_T0);
	//_mm_prefetch((const char*)y, _MM_HINT_T0);

	for(i = 0; i < n; i += 8){
		_x1 = _mm_load_ps(x);
		_x2 = _mm_load_ps(x+4);
		
		_o1 = _x1;
		_o2 = _x2;
		for(int j = 0; j < 6; ++j)
		{
			_x1 = _mm_mul_ps(_o1, _a);
			_o1 = _mm_add_ps(_x1, _o1);
			_x2 = _mm_mul_ps(_o2, _a);
			_o2 = _mm_add_ps(_x2, _o2);

			_x1 = _mm_mul_ps(_o1, _a);
			_o1 = _mm_add_ps(_x1, _o1);
			_x2 = _mm_mul_ps(_o2, _a);
			_o2 = _mm_add_ps(_x2, _o2);

			_x1 = _mm_mul_ps(_o1, _a);
			_o1 = _mm_add_ps(_x1, _o1);
			_x2 = _mm_mul_ps(_o2, _a);
			_o2 = _mm_add_ps(_x2, _o2);

			_x1 = _mm_mul_ps(_o1, _a);
			_o1 = _mm_add_ps(_x1, _o1);
			_x2 = _mm_mul_ps(_o2, _a);
			_o2 = _mm_add_ps(_x2, _o2);

			_x1 = _mm_mul_ps(_o1, _a);
			_o1 = _mm_add_ps(_x1, _o1);
			_x2 = _mm_mul_ps(_o2, _a);
			_o2 = _mm_add_ps(_x2, _o2);
		}

		_mm_stream_ps(out, _o1);
		_mm_stream_ps(out+4, _o2);

		x+=8;
		out+=8;
	}

	if( n % 2 == 1){
		__m128 _x = _mm_load_ps(x);
		__m128 _y = _mm_load_ps(y);
		__m128 _o = _mm_mul_ps(_x, _a);
		_o = _mm_add_ps(_o, _y);
		_mm_store_ps(out, _o);
	}
}
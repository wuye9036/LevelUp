// gis2007.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "omp.h"
#include "SineKernel.h"
#include "SaxpyKernel.h"
#include "MRKernel.h"
#include "NHKernel.h"

int _tmain(int argc, _TCHAR* argv[])
{	
	bool inEnviroment = false;
	int vec_size = 1024;
	int block_size = 0;
	bool isPerfCPUBench = false;

	if(argc < 2){
		inEnviroment = true;
		isPerfCPUBench = true;
	} else {
		vec_size = _ttoi(argv[1]);
		if(argc > 2){
			block_size =  _ttoi(argv[2]);
		}
		if(argc > 3){
			isPerfCPUBench =
				(_tcscmp(_T("TRUE"), argv[3]) == 0);
		}
	}
	//
	printf("The Length of Input Vector is: %d\n", vec_size);

#if defined(SAXPY_VER)
	SaxpyKernel ppk(vec_size, block_size);
#elif defined(MR_VER)
	MRKernel ppk(vec_size, block_size);
#elif defined(NH_VER)
	NHKernel ppk(vec_size, block_size);
#else
	SineKernel ppk(vec_size);
#endif
	
	ppk.Execute(isPerfCPUBench);
	printf("\n\n\n");
	
	if(inEnviroment) 
		system("pause");
	return 0;
}
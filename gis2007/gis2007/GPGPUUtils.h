#pragma once

#include <gl/glew.h>
#include "gl/glut.h"
#include "source/glsl.h"

#include <vector>

#include "platform/typedef.h"

using namespace std;

typedef vector<double> PerformanceReport;

enum PerformItemsID
{
	PIID_CPU			= 0,
	PIID_CPU_MT		= 1,
	PIID_CPU_OMP	= 2,
	PIID_GPU			= 3,
	PIID_GPU_KR		= 4
};

// error codes
extern int ERROR_GLSL;
extern int ERROR_GLEW;
extern int ERROR_TEXTURE;
extern int ERROR_BINDFBO;
extern int ERROR_FBOTEXTURE;
extern int ERROR_PARAMS;

void checkGLErrors (const char *label);
bool checkFramebufferStatus();
void printVector (const float *p, const int N);

struct TEI // Thread Execution Info
{
	void* data;
	int		range_begin;
	int		range_end;
};

struct ThreadExecutionInfos
{
	vector<TEI> teiList_;
	TEI& operator [](int index){return teiList_[index];}
	ThreadExecutionInfos(void* data, int first_index, int last_index, int nThread):teiList_(nThread) // range : [first_index, last_index)
	{
		UnalignedBalanceTaskShedular(data, first_index, last_index, nThread);
	}

	//线性函数分段算法的对齐版本,用于指令集加速. size 需要加速的数据的大小.
	//例如Saxpy就是指x,y,out的每个浮点数的字节数
	ThreadExecutionInfos(void* data, int first_index, int last_index, int nThread, size_t size, size_t alignment): teiList_(nThread)
	{
		int nData = last_index - first_index;
		
		if(	alignment == 0 || size == 0 ||
			alignment % size != 0 ||				//不能以整单元方式对齐,例如不能用浮点完成10字节对齐的划分
			(nData * size) % alignment != 0		//整个数据无法以收尾均对齐的方式划分
			) {
				printf("warning : data unaligned!\n");
				UnalignedBalanceTaskShedular(data, first_index, last_index, nThread);
				return;
		}
		
		//开始实行对齐-均衡划分
		int nDataPerAlignedBlock = int(alignment / size);				//每个对齐的块有几个数据
		int nAlignedBlock = int(nData / nDataPerAlignedBlock);		//总共有多少对齐的块
		int nBlocksPerThread = nAlignedBlock / nThread;				//每个线程至少要执行多少个块
		int balance = nAlignedBlock % nThread;							//有多少线程要比其余线程多分一个块

		for(int i = 0; i < balance; ++i){
			teiList_[i].range_begin = i * (nBlocksPerThread + 1) * nDataPerAlignedBlock;
			teiList_[i].range_end = (i + 1) *  (nBlocksPerThread + 1) * nDataPerAlignedBlock;
			teiList_[i].data = data;
		}
		int base_index = balance * (nBlocksPerThread + 1) * nDataPerAlignedBlock;
		for(int i = 0; i < nThread - balance; ++i)
		{
			teiList_[i].range_begin = base_index + i * nBlocksPerThread * nDataPerAlignedBlock;
			teiList_[i].range_end = base_index + (i + 1) * nBlocksPerThread * nDataPerAlignedBlock;
			teiList_[i].data = data;
		}
		
		printf("Aligned Scheduled. \n");
		for(int i = 0; i < nThread; ++i){
			printf("Thread %d : [%d, %d)    ", i, teiList_[i].range_begin, teiList_[i].range_end);
		}
		printf("\n");
	}
private:
	void UnalignedBalanceTaskShedular(void* data, int first_index, int last_index, int nThread){
		//均衡分配算法
		//线程分配到的循环量分别是: n, n, n, ... , n+1, ... ,n+1, 也就是说,较多的线程不会至多比较小线程多一
		int nCycles = last_index - first_index;
		int balance = nCycles % nThread;
		int nCyclesPerThread = (nCycles - balance) / nThread;
		for(int i = 0; i < balance; ++i){
			teiList_[i].range_begin = i * (nCyclesPerThread + 1);
			teiList_[i].range_end = (i + 1) * (nCyclesPerThread + 1);
			teiList_[i].data = data;
		}
		int base_index = balance * (nCyclesPerThread + 1);
		for(int i = 0; i < nThread - balance; ++i)
		{
			teiList_[i].range_begin = base_index + i * nCyclesPerThread;
			teiList_[i].range_end = base_index + (i + 1) * nCyclesPerThread;
			teiList_[i].data = data;
		}

		printf("Unaligned Scheduled. \n");
		for(int i = 0; i < nThread; ++i){
			printf("Thread %d : [%d, %d)    ", i, teiList_[i].range_begin, teiList_[i].range_end);
		}
		printf("\n");
	}
};

struct GLArrayState
{
	uint32	arrInputStage;
	uint32	arrOutputAttachment;
	uint32	arrID;

	GLArrayState(uint32 aid, uint32 ais, uint32 aoa):arrID(aid), arrInputStage(ais), arrOutputAttachment(aoa){}
	GLArrayState(const GLArrayState& glas):arrID(glas.arrID), arrInputStage(glas.arrInputStage), arrOutputAttachment(glas.arrOutputAttachment){}
};

class LookupTable
{
	vector<GLArrayState> arrStates;

public:
	LookupTable()
	{
		cout << "------------------------------------------------------------------------" << endl;
		cout << "warning : class LookupTable is using but untested ! " << endl;
		cout << "------------------------------------------------------------------------" << endl;
		cout << endl;
	}

	size_t GetStateIDByArrID(uint32 arrID){
		for(size_t i = 0; i < arrStates.size(); ++i){
			if(arrStates[i].arrID == arrID){ return i; }
		}
		return size_t(-1);
	}

	size_t GetStateIDByOutputAttachment(uint32 arrOutputAttachment){
		if(arrOutputAttachment == uint32(-1)) return size_t(-1);
		for(size_t i = 0; i < arrStates.size(); ++i){
			if(arrStates[i].arrOutputAttachment == arrOutputAttachment){ return i; }
		}
		return size_t(-1);
	}

	size_t GetStateIDByInputStage(uint32 arrInputStage){
		if(arrInputStage == uint32(-1)) return size_t(-1);
		for(size_t i = 0; i < arrStates.size(); ++i){
			if(arrStates[i].arrInputStage == arrInputStage){ return i; }
		}
		return size_t(-1);
	}

	GLArrayState* GetByArrID(uint32 arrID){
		size_t statepos = GetStateIDByArrID(arrID);
		if(statepos == size_t(-1)) return NULL;
		return &(arrStates[statepos]);
	}

	GLArrayState* GetByOutputAttachment(uint32 arrOutputAttachment){
		size_t statepos = GetStateIDByOutputAttachment(arrOutputAttachment);
		if(statepos == size_t(-1)) return NULL;
		return &(arrStates[statepos]);
	}

	GLArrayState* GetByInputStage(uint32 arrInputStage){
		size_t statepos = GetStateIDByInputStage(arrInputStage);
		if(statepos == size_t(-1)) return NULL;
		return &(arrStates[statepos]);
	}

	void SetArrayState(uint32 arrID, uint32 arrInputStage = uint32(-1), uint32 arrOutputAttachment = uint32(-1))
	{
		GLArrayState* pGLas = GetByArrID(arrID);
		if(pGLas == NULL){
			arrStates.push_back(GLArrayState(arrID, arrInputStage, arrOutputAttachment));
		} else {
			pGLas->arrInputStage = arrInputStage;
			pGLas->arrOutputAttachment = arrOutputAttachment;
		}
	}

	void SetArrayInputStage(uint32 arrID, uint32 arrInputStage = uint32(-1))
	{
		GLArrayState* pGLas = GetByArrID(arrID);
		if(pGLas == NULL){
			arrStates.push_back(GLArrayState(arrID, arrInputStage, -1));
		} else {
			pGLas->arrInputStage = arrInputStage;
		}
	}

	void SetArrayOutputAttachment(uint32 arrID, uint32 arrOutputAttachment = uint32(-1)){
		GLArrayState* pGLas = GetByArrID(arrID);
		if(pGLas == NULL){
			arrStates.push_back(GLArrayState(arrID, -1, arrOutputAttachment));
		} else {
			pGLas->arrOutputAttachment = arrOutputAttachment;
		}
	}

	void DeleteArrayState(uint32 arrID){
		size_t statepos = size_t(-1);
		if((statepos = GetStateIDByArrID(arrID)) == size_t(-1)){
			return;
		}
		arrStates[statepos] = arrStates.back();
		arrStates.pop_back();
	}
};


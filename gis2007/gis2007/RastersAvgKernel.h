#pragma once
#include "graphicprocessor.h"

//提供四纹理融合功能

class RastersAvgKernel :
	public Kernel
{
public:
	RastersAvgKernel(void);
	virtual ~RastersAvgKernel(void);
};

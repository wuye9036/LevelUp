/*
	资源系统，提供基本的资源服务
*/
#pragma once
#include <windows.h>

class ResourceSystem
{
public:
	BOOL Update();
	BOOL Initialize();

	ResourceSystem(void);
	~ResourceSystem(void);
};

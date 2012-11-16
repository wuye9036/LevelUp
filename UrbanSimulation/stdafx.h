// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

// Change these values to use different versions
#define WINVER		0x0400
//#define _WIN32_WINNT	0x0400
#define _WIN32_IE	0x0400
#define _RICHEDIT_VER	0x0100
#define _CRT_SECURE_NO_DEPRECATE
#define _ATL_USE_DDX_FLOAT
#include <atlbase.h>
#include <atlapp.h>
#include <atlddx.h>

extern CAppModule _Module;

#include <atlwin.h>

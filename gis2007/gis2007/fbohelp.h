#pragma once

#include <gl/glew.h>
#include "gl/glut.h"
#include "source/glsl.h"

#include <time.h>
#include <math.h>

// error codes
static int ERROR_GLSL = -1;
static int ERROR_GLEW = -2;
static int ERROR_TEXTURE = -3;
static int ERROR_BINDFBO = -4;
static int ERROR_FBOTEXTURE = -5;
static int ERROR_PARAMS = -6;

bool InitGPGPUEnv();
bool checkFramebufferStatus(void);
void checkGLErrors(const char *label);
void compareResults(void);
void createTextures (int nTexs, GLuint* texIDs);
void createTextureParameters(void);
void initFBO(void);
void initGLEW(void);
void initGLUT();
void performComputation(GLuint destID, GLuint nSrcID, GLuint* srcIDs, Kernel* kn);
void printInfoLog(GLhandleARB obj);
void printVector(const float *p, const int N);
void setupTexture(const GLuint texID);
void transferFromTexture(float* data);
void transferToTexture(float* data, GLuint texID);
void SetVectorLength(size_t sz);
/* 
For ATI and NV, we use different configuration.
*/

// ATI Version

//NV Version
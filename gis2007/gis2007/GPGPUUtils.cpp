#include "GPGPUUtils.h"

// error codes
int ERROR_GLSL = -1;
int ERROR_GLEW = -2;
int ERROR_TEXTURE = -3;
int ERROR_BINDFBO = -4;
int ERROR_FBOTEXTURE = -5;
int ERROR_PARAMS = -6;

void checkGLErrors (const char *label) {
	GLenum errCode;
	const GLubyte *errStr;

	if ((errCode = glGetError()) != GL_NO_ERROR) {
		errStr = gluErrorString(errCode);
		printf("OpenGL ERROR: ");
		printf((char*)errStr);
		printf("(Label: ");
		printf(label);
		printf(")\n.");
	}
}

bool checkFramebufferStatus() {
	GLenum status;
	status = (GLenum) glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	switch(status) {
		case GL_FRAMEBUFFER_COMPLETE_EXT:
			return true;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
			printf("Framebuffer incomplete, incomplete attachment\n");
			return false;
		case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
			printf("Unsupported framebuffer format\n");
			return false;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
			printf("Framebuffer incomplete, missing attachment\n");
			return false;
		case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
			printf("Framebuffer incomplete, attached images must have same dimensions\n");
			return false;
		case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
			printf("Framebuffer incomplete, attached images must have same format\n");
			return false;
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
			printf("Framebuffer incomplete, missing draw buffer\n");
			return false;
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
			printf("Framebuffer incomplete, missing read buffer\n");
			return false;
	}
	return false;
}

void printVector (const float *p, const int N) {
	for (int i=0; i<N; i++) 
		printf("%5.3f ",p[i]);
	printf("\n");
}

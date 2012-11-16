#include "fbohelp.h"

// ping pong management vars
int writeTex = 0;
int readTex = 1;
GLenum attachmentpoints[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT };

int texSize = 0;
int psz = 0;
// FBO identifier
GLuint fb;

// timing vars 
clock_t start, end;

// handle to offscreen "window", only used to properly shut down the app
GLuint glutWindowHandle;

// struct for variable parts of GL calls (texture format, float format etc)
struct struct_textureParameters {
	char* name;
	GLenum texTarget;
	GLenum texInternalFormat;
	GLenum texFormat;
	char* shader_source;
} tex_param;

void SetVectorLength(size_t sz)
{
	psz = int(sz);
}

bool InitGPGPUEnv(){
	// create variables for GL
	createTextureParameters();
	initGLUT();
	initGLEW();
	// init offscreen framebuffer
	if (tex_param.texFormat == GL_RGBA)
		texSize = (int)sqrt(psz/4.0);
	else
		texSize = (int)sqrt((double)psz);
	initFBO();
	return true;
}

void ClearGPGPUEnv()
{
	glDeleteFramebuffersEXT(1,&fb);
	glutDestroyWindow (glutWindowHandle);
}

/**
* Sets up a floating point texture with NEAREST filtering.
* (mipmaps etc. are unsupported for floating point textures)
*/
void setupTexture (const GLuint texID) {
	// make active and bind
	glBindTexture(tex_param.texTarget,texID);
	// turn off filtering and wrap modes
	glTexParameteri(tex_param.texTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(tex_param.texTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(tex_param.texTarget, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(tex_param.texTarget, GL_TEXTURE_WRAP_T, GL_CLAMP);
	// define texture with floating point format
	glTexImage2D(tex_param.texTarget,0,tex_param.texInternalFormat,texSize,texSize,0,tex_param.texFormat,GL_FLOAT,0);
	// check if that worked
	if (glGetError() != GL_NO_ERROR) {
		printf("glTexImage2D():\t\t\t [FAIL]\n");
		exit (ERROR_TEXTURE);
	}
	//	printf("Created a %i by %i floating point texture.\n",texSize,texSize);
}

/**
* Transfers data from currently texture, and stores it in given array.
*/
void transferFromTexture(float* data) {
	// version (a): texture is attached
	// recommended on both NVIDIA and ATI
	glReadBuffer(attachmentpoints[0]);
	glReadPixels(0, 0, texSize, texSize,tex_param.texFormat,GL_FLOAT,data);
	// version b: texture is not neccessarily attached
	//	glBindTexture(tex_param.texTarget,yTexID[readTex]);
	//	glGetTexImage(tex_param.texTarget,0,tex_param.texFormat,GL_FLOAT,data);
}

/**
* Transfers data to texture. 
* Check web page for detailed explanation on the difference between ATI and NVIDIA.
*/
void transferToTexture (float* data, GLuint texID) {
	// version (a): HW-accelerated on NVIDIA 
	 glBindTexture(tex_param.texTarget, texID);
	 glTexSubImage2D(tex_param.texTarget,0,0,0,texSize,texSize,tex_param.texFormat,GL_FLOAT,data);
	// version (b): HW-accelerated on ATI
	/*
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, tex_param.texTarget, texID, 0);
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
	glRasterPos2i(0,0);
	glDrawPixels(texSize,texSize,tex_param.texFormat,GL_FLOAT,data);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, tex_param.texTarget, 0, 0);
	*/
}


/**
* creates textures, sets proper viewport etc.
*/
void createTextures (int nTexs, GLuint* texIDs) {
	glGenTextures (nTexs, texIDs);
	for(int i =0; i < nTexs; ++i){	setupTexture (texIDs[i]); }
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	checkGLErrors ("createFBOandTextures()");
}

void clearTextures(int nTexs, GLuint* texIDs){
	glDeleteTextures(nTexs, texIDs);
}
/**
* Sets up GLUT, creates "window" (better put: valid GL context, since the window is never displayed)
*/
void initGLUT() {
	int argc;
	char* argv = "\0";
	glutInit ( &argc, &argv );
	glutWindowHandle = glutCreateWindow("GPGPU");
}

/**
* Sets up GLEW to initialise OpenGL extensions
*/
void initGLEW (void) {
	int err = glewInit();
	// sanity check
	if (GLEW_OK != err) {
		printf((char*)glewGetErrorString(err));
		//		PAUSE();
		exit(ERROR_GLEW);
	}  
}

/**
* Creates framebuffer object, binds it to reroute rendering operations 
* from the traditional framebuffer to the offscreen buffer
*/
void initFBO(void) {
	// create FBO (off-screen framebuffer)
	glGenFramebuffersEXT(1, &fb); 
	// bind offscreen framebuffer (that is, skip the window-specific render target)
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
	// viewport for 1:1 pixel=texture mapping
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLdouble(texSize), 0.0, GLdouble(texSize));
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, texSize, texSize);
}

/**
* Performs and times saxpy on the CPU, compares results
*/
void compareResults () {
}


/**
* Perform calc.
*/
void performComputation(GLuint destID, GLuint nSrcID, GLuint* srcIDs, Kernel* kn) {
	//	glEnable(tex_param.texTarget);
	// attach two textures to FBO
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, attachmentpoints[writeTex], tex_param.texTarget, destID, 0);
	// check if that worked
	if (!checkFramebufferStatus()) {
		printf("glFramebufferTexture2DEXT():\t [FAIL]\n");
		exit (ERROR_FBOTEXTURE);
	}

	// bind textures
	for(size_t i = 0; i < nSrcID; ++i) {
		glActiveTexture(GL_TEXTURE0 + i);	
		glBindTexture(tex_param.texTarget, srcIDs[i]);
	}

	kn->CreateKernelEnv();

	// Calling glFinish() is only necessary to get accurate timings,
	// and we need a high number of iterations to avoid timing noise.
	glFinish();
	start = clock();
	// set render destination
	glDrawBuffer (attachmentpoints[writeTex]);
	// make quad filled to hit every pixel/texel 
	// (should be default but we never know)
	glPolygonMode(GL_FRONT,GL_FILL);
	// and render the quad
	if (tex_param.texTarget == GL_TEXTURE_2D) {
		// render with normalized texcoords
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); 
		glVertex2f(0.0, 0.0);
		glTexCoord2f(1.0, 0.0); 
		glVertex2f(texSize, 0.0);
		glTexCoord2f(1.0, 1.0); 
		glVertex2f(texSize, texSize);
		glTexCoord2f(0.0, 1.0); 
		glVertex2f(0.0, texSize);
		glEnd();
	} else {
		// render with unnormalized texcoords
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); 
		glVertex2f(0.0, 0.0);
		glTexCoord2f(texSize, 0.0); 
		glVertex2f(texSize, 0.0);
		glTexCoord2f(texSize, texSize); 
		glVertex2f(texSize, texSize);
		glTexCoord2f(0.0, texSize); 
		glVertex2f(0.0, texSize);
		glEnd();
	}
	// done, stop timer, calc MFLOP/s if neccessary
	glFinish();
	kn->DestoryKernelEnv();
	end = clock();
	double total = double(end-start)/CLOCKS_PER_SEC;
	// calc mflops 
	//double mflops = (2.0*N*numIterations) / (total * 1000000.0);
	//printf("MFLOP/s for N=%d:\t\t%f %f %d %d\n", N, mflops, total, end, CLOCKS_PER_SEC);
	// done, just do some checks if everything went smoothly.
	checkFramebufferStatus();
	checkGLErrors("render()");
	//	glDisable(tex_param.texTarget);
}

/**
* Sets up the various structs used to handle texture targets, texture formats etc.
*/
void createTextureParameters(void) {
	tex_param.name					= "GL_TEXTURE_RECTANGLE_ARB, GL_RGBA32F_ARB, GL_RGBA";
	tex_param.texTarget			= GL_TEXTURE_RECTANGLE_ARB;
	tex_param.texInternalFormat= GL_RGBA32F_ARB;
	tex_param.texFormat			= GL_RGBA;
	tex_param.shader_source		= "uniform sampler2DRect textureY;" \
		"uniform sampler2DRect textureX;" \
		"uniform float alpha;" \
		"void main(void) { " \
		"vec4 y = texture2DRect(textureY, gl_TexCoord[0].st);" \
		"vec4 x = texture2DRect(textureX, gl_TexCoord[0].st);" \
		"gl_FragColor = y + alpha*x;"\
		"}";
}

/**
* Checks for OpenGL errors.
* Extremely useful debugging function: When developing, 
* make sure to call this after almost every GL call.
*/
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

/**
* Checks framebuffer status.
* Copied directly out of the spec, modified to deliver a return value.
*/
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

/**
* copied from http://www.lighthouse3d.com/opengl/glsl/index.php?oglinfo
*/
void printInfoLog(GLhandleARB obj) {
	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;
	glGetObjectParameterivARB(obj, GL_OBJECT_INFO_LOG_LENGTH_ARB, &infologLength);
	if (infologLength > 1) {
		infoLog = (char *)malloc(infologLength);
		glGetInfoLogARB(obj, infologLength, &charsWritten, infoLog);
		printf(infoLog);
		printf("\n");
		free(infoLog);
	}
}

/**
* Prints out given vector for debugging purposes.
*/
void printVector (const float *p, const int N) {
	for (int i=0; i<N; i++) 
		printf("%5.3f ",p[i]);
	printf("\n");
}

/**
* swaps the role of the two y-textures (read-only and write-only)
* Can be done smarter :-)
*/
void swap(void) {
	if (writeTex == 0) {
		writeTex = 1;
		readTex = 0;
	} else {
		writeTex = 0;
		readTex = 1;
	}
}
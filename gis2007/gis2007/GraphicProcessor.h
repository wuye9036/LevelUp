#pragma once

#include <assert.h>
#include <math.h>
#include <vector>

#include "Timer.h"
#include "GPGPUUtils.h"

using namespace std;
using namespace cwc;

struct vertex
{
	float x,y;
};

struct coord
{
	float s,t;
};

typedef uint16 index_type;

class Kernel
{
public:
	virtual void CreateKernelEnv() = 0;
	virtual void DestoryKernelEnv() = 0;
	virtual bool IterateCalculate(GLenum srcAttachment, GLenum* changedAttachment)
	{return false;}
};

class GraphicProcessor
{
public:
	GraphicProcessor(size_t vecsz) : pKernel_(NULL){
		// initialize texture format;
#ifdef NH_VER
		texTarget_				= GL_TEXTURE_RECTANGLE_ARB;
		texInternalFormat_	= GL_FLOAT_R32_NV;
		texFormat_				= GL_LUMINANCE;
		printf("tex target r32 nv\n");
#else
		texTarget_				= GL_TEXTURE_RECTANGLE_ARB;
		texInternalFormat_	= GL_RGBA32F_ARB;
		texFormat_				= GL_RGBA;
#endif
		//Initialize Windows and GLUT
		int argc = 0;
		glutInit ( &argc, NULL);
		glutWindowHandle_ = glutCreateWindow("GPGPU");

		//Initialize GLEW
		int err = glewInit();
		if (GLEW_OK != err) {
			printf((char*)glewGetErrorString(err));
			//		PAUSE();
			exit(ERROR_GLEW);
		} 

		if (texFormat_ == GL_RGBA)
			defaultTexSize_ = (int)sqrt(vecsz/4.0);
		else
			defaultTexSize_ = (int)sqrt((double)vecsz);
		blockSize_ = defaultTexSize_;
		nTriangles_ = 2;

		cout << defaultTexSize_ << endl;
		// initialize off-screen frame buffer(FBO)
		glGenFramebuffersEXT(1, &fb_); 
		// bind off-screen frame buffer (that is, skip the window-specific render target)
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb_);

		// view port for 1:1 pixel=texture mapping
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0.0, GLdouble(defaultTexSize_), 0.0, GLdouble(defaultTexSize_));
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glViewport(0, 0, defaultTexSize_, defaultTexSize_);
	}

	~GraphicProcessor(){
		glDeleteFramebuffersEXT(1,&fb_);
		glutDestroyWindow (glutWindowHandle_);
	}

	void RegisterKernel(Kernel* pK){
		pKernel_ = pK;
	}

	vector<GLuint> AllocArrays(size_t nArrays, size_t arrSize)
	{
		
		int texSize = 0;
		if (texFormat_ == GL_RGBA)
			texSize = (int)sqrt(arrSize/4.0);
		else
			texSize = (int)sqrt((double)arrSize);

		return AllocTextures(nArrays, texSize);
	}

	vector<GLuint> AllocArrays(size_t nArrays){
		return AllocTextures(nArrays, defaultTexSize_);
	}

	vector<GLuint> AllocTextures(size_t nTexs, uint32 texSize)
	{
		vector<GLuint> glTexIDs(nTexs);

		glGenTextures (GLsizei(nTexs), &(glTexIDs[0]));
		for(size_t i = 0; i < nTexs; ++i) { SetupTexture (glTexIDs[i], texSize); }
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		checkGLErrors ("createFBOandTextures()");

		return glTexIDs;
	}

	void FreeArrays(const vector<GLuint>& arrIDs)
	{
		glDeleteTextures(GLsizei(arrIDs.size()), &(arrIDs[0]));
	}

	GLuint AllocateArray()
	{
		GLuint glTexID;

		glGenTextures(1, &glTexID);
		SetupTexture(glTexID, defaultTexSize_);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		checkGLErrors ("createFBOandTextures()");

		return glTexID;
	}

	void FreeArray(GLuint arrID)
	{
		glDeleteTextures(1, &arrID);
	}

	void WriteArray(float* data, GLuint arrID)
	{
		checkGLErrors("PreWriteArray()");
		// version (a): HW-accelerated on NVIDIA 
		glBindTexture(texTarget_, arrID);
		glTexSubImage2D(texTarget_,0,0,0,defaultTexSize_,defaultTexSize_,texFormat_,GL_FLOAT,data);
		checkGLErrors("WriteArray()");
		// version (b): HW-accelerated on ATI 
		/*
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, texTarget_, arrID, 0);
		glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
		glRasterPos2i(0,0);
		glDrawPixels(defaultTexSize_,defaultTexSize_,texFormat_,GL_FLOAT,data);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, texTarget_, 0, 0);
		*/
	}

	void ReadArray(float* data, GLuint arrID)
	{
		glBindTexture(texTarget_,arrID);
		glGetTexImage(texTarget_,0,texFormat_,GL_FLOAT,data);
	}

	void ReadBuffer(float* data, uint32 AttachmentID = 0){
		glReadBuffer(AttachmentID + GL_COLOR_ATTACHMENT0_EXT);
		glReadPixels(0, 0, defaultTexSize_, defaultTexSize_,texFormat_,GL_FLOAT,data);
	}

	void ReadLastWriteBuffer(float* data){
		ReadBuffer(data, lastWriteAttachmentID_);
	}

	GLuint SetArrayInputStage(GLuint arrID){
		static GLenum arrInputStage = 0;
		glActiveTexture(arrInputStage + GL_TEXTURE0);	
		glBindTexture(texTarget_, arrID);
		texUsage_.SetArrayInputStage(arrID, arrInputStage);
		checkGLErrors("SetArrayInputStage()");
		return arrInputStage++;
	}
	
	GLuint SetArrayInputStage(GLuint arrID, GLuint arrInputStage)
	{
		glActiveTexture(arrInputStage + GL_TEXTURE0);	
		glBindTexture(texTarget_, arrID);
		texUsage_.SetArrayInputStage(arrID, arrInputStage);
		checkGLErrors("SetArrayInputStage()");
		return arrInputStage;
	}

	bool SetCacheOptimization(int blockSize)
	{
		if((blockSize <= 0) || (defaultTexSize_ % blockSize != 0)){
			printf( "Cache Optimized Failed! ( Block Size = %d )\n", blockSize);
			blockSize_ = defaultTexSize_;
			return false;
		}

		blockSize_ = blockSize;

		//计算三角形列表
		int edge_len = defaultTexSize_/blockSize_;
		nTriangles_ = edge_len * edge_len * 2;
		int vertex_num = (edge_len+1)*(edge_len+1);
		
		vertexList_.resize(vertex_num);
		coordList_.resize(vertex_num);
		indexList_.resize(3*nTriangles_);
		
		//计算顶点坐标与纹理坐标
		for(int i = 0; i <= edge_len; ++i){
			for(int j = 0; j <= edge_len; ++j)
			{
				int pos = i * (edge_len+1) + j;
				coordList_[pos].s = vertexList_[pos].x = float(j * blockSize_);
				coordList_[pos].t = vertexList_[pos].y = float(i * blockSize_);
				
			}
		}

		//输出点坐标
		/*
		for (int i = 0; i < vertex_num; ++i)
		{
			printf("The Coord of Vertex %d : %5.3f, %5.3f\n", i, vertexList_[i].x, vertexList_[i].y);
		}
		*/
		//计算索引列表
		for(int i = 0; i < edge_len; ++i)
		{
			for (int j = 0 ; j < edge_len; ++j)
			{
				int pos_base = i * (edge_len + 1) + j;

				int pos_left_up = pos_base;
				int pos_left_down = pos_base + (edge_len + 1);
				int pos_right_up = pos_base + 1;
				int pos_right_down = pos_base +  (edge_len + 1) + 1;

				int base_index_pos = ((i * edge_len) + j) * 6; //每个矩形有六个浮点数
				
				indexList_[base_index_pos + 0] = index_type(pos_left_up);
				indexList_[base_index_pos + 2] = index_type(pos_right_down);
				indexList_[base_index_pos + 1] = index_type(pos_right_up);

				indexList_[base_index_pos + 3] = index_type(pos_left_up);
				indexList_[base_index_pos + 5] = index_type(pos_left_down);
				indexList_[base_index_pos + 4] = index_type(pos_right_down);
			}
		}

		/*
		for(int i = 0; i < nTriangles_; ++i){
			printf("Triangle %d: %3d, %3d, %3d\n", i, indexList_[i*3], indexList_[i*3+1], indexList_[i*3+2]);
		}
		
		printf("Texture Size: %d\n", defaultTexSize_);
		printf("Block Size: %d\n", blockSize_);
		printf("The Number of Sections Per Edge: %d\n", edge_len);
		printf("The Number of Triangles: %d\n", nTriangles_);
		printf("The Number of Vertexes: %d\n", vertex_num);
		*/
		return true;
	}

	void	PerformComputation(GLuint outputArrayID){
		//	glEnable(tex_param.texTarget);
		// attach two textures to FBO
		PerformComputationMultiAttachments(outputArrayID);
	}

	void PerformComputationMultiAttachments(GLuint outputArrayID0, GLuint outputArrayID1 = -1, GLuint outputArrayID2 = -1, GLuint outputArrayID3 = -1)
	{
		if(!pKernel_){
			assert(!"Kernel function is no exist!");
			cout << endl;
			cout << "--------------------------------------------------------------------" << endl;
			cout << "Warning: Pointer of Kernel Function is NULL!" << endl;
			cout << "--------------------------------------------------------------------" << endl;
			cout << endl;
			return;
		}

		checkGLErrors("PreFramebufferTexture2DEXT()");

		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, texTarget_, outputArrayID0, 0);
		texUsage_.SetArrayOutputAttachment(outputArrayID0, 0);
		if(outputArrayID1 != -1){
			glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT, texTarget_, outputArrayID1, 0);
			texUsage_.SetArrayOutputAttachment(outputArrayID1, 1);
			if(outputArrayID2 != -1){
				glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT2_EXT, texTarget_, outputArrayID2, 0);
				texUsage_.SetArrayOutputAttachment(outputArrayID2, 2);
				if(outputArrayID3 != -1){
					glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT3_EXT, texTarget_, outputArrayID3, 0);
					texUsage_.SetArrayOutputAttachment(outputArrayID3, 3);
				} 
			} 
		} 

		//cout << texTarget_ << " " << texFormat_ << " " << texInternalFormat_ << endl;

		checkGLErrors("FrameBufferTexture2DEXT()");

		GLenum AttachmentID = 0;

		if (!checkFramebufferStatus()) {
			printf("glFramebufferTexture2DEXT():\t [FAIL]\n");
			exit (ERROR_FBOTEXTURE);
		}	

		// Calling glFinish() is only necessary to get accurate timings,
		// and we need a high number of iterations to avoid timing noise.
		glFinish();

		pKernel_->CreateKernelEnv();
		do{
			if(nTriangles_ == 2){
				DrawBuffer(AttachmentID + GL_COLOR_ATTACHMENT0_EXT);
			} else {
				DrawBufferBlocked(AttachmentID + GL_COLOR_ATTACHMENT0_EXT);
			}
			lastWriteAttachmentID_ = AttachmentID;
		} while(pKernel_->IterateCalculate(AttachmentID, &AttachmentID));
		glFinish();
		pKernel_->DestoryKernelEnv();

		checkFramebufferStatus();
		checkGLErrors("render()");
	}

	void DrawBuffer(GLenum GLAttachmentID)
	{
#pragma warning(push)
#pragma warning(disable:4244)
		static bool isLogged = false;
		if(!isLogged){ printf("DrawBufferQuad();\n"); isLogged = true;}

		// set render destination
		glDrawBuffer (GLAttachmentID);
		// make quad filled to hit every pixel/texel 
		// (should be default but we never know)
		glPolygonMode(GL_FRONT,GL_FILL);
		// and render the quad
		if (texTarget_ == GL_TEXTURE_2D) {
			// render with normalized texcoords
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); 
			glVertex2f(0.0, 0.0);
			glTexCoord2f(1.0, 0.0); 
			glVertex2f(defaultTexSize_, 0.0);
			glTexCoord2f(1.0, 1.0); 
			glVertex2f(defaultTexSize_, defaultTexSize_);
			glTexCoord2f(0.0, 1.0); 
			glVertex2f(0.0, defaultTexSize_);
			glEnd();
		} else {
			// render with unnormalized texcoords
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); 
			glVertex2f(0.0, 0.0);
			glTexCoord2f(defaultTexSize_, 0.0); 
			glVertex2f(defaultTexSize_, 0.0);
			glTexCoord2f(defaultTexSize_, defaultTexSize_); 
			glVertex2f(defaultTexSize_, defaultTexSize_);
			glTexCoord2f(0.0, defaultTexSize_); 
			glVertex2f(0.0, defaultTexSize_);
			glEnd();
		}
#pragma warning(pop)
	}

	void DrawBufferBlocked(GLenum GLAttachmentID)
	{
		static bool isLogged = false;
		if(!isLogged){ 
			printf("DrawBufferBlocked();\n");
			printf("Block Size: %d\n", blockSize_);
			printf("The Number of Triangles: %d\n", nTriangles_);
			isLogged = true;
		}
		

		glDrawBuffer(GLAttachmentID);
		glPolygonMode(GL_FRONT, GL_FILL);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glTexCoordPointer(2, GL_FLOAT, 0, &(coordList_[0]));
		glVertexPointer(2, GL_FLOAT, 0, &(vertexList_[0]));
		
		glDrawElements(GL_TRIANGLES, nTriangles_*3, GL_UNSIGNED_SHORT, &(indexList_[0]));
	}

	const GLArrayState* GetArrayStateByArrID(uint32 arrID){
		return texUsage_.GetByArrID(arrID);
	}

	const GLArrayState* GetArrayStateByInputStage(uint32 is){
		return texUsage_.GetByInputStage(is);
	}

	const GLArrayState* GetArrayStateByOutputAttachment(uint32 oa){
		return texUsage_.GetByOutputAttachment(oa);
	}

protected:

	/**
	* Sets up a floating point texture with NEAREST filtering.
	* (mipmaps etc. are unsupported for floating point textures)
	*/
	void SetupTexture (const GLuint texID, size_t texSize) {
		// make active and bind
		glBindTexture(texTarget_, texID);
		// turn off filtering and wrap modes
		glTexParameteri(texTarget_, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(texTarget_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(texTarget_, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(texTarget_, GL_TEXTURE_WRAP_T, GL_CLAMP);
		// define texture with floating point format
		glTexImage2D(texTarget_,0,texInternalFormat_,GLsizei(texSize),GLsizei(texSize),0,texFormat_,GL_FLOAT,0);
		// check if that worked
		if (glGetError() != GL_NO_ERROR) {
			printf("glTexImage2D():\t\t\t [FAIL]\n");
			exit (ERROR_TEXTURE);
		}
		//	printf("Created a %i by %i floating point texture.\n",defaultTexSize_,defaultTexSize_);
	}

	int			blockSize_;
	int			nTriangles_;
	int			defaultTexSize_;		// size of texture. a texture is defaultTexSize_*defaultTexSize_.
	int			vectorSize_;			// size of data.
	Kernel*	pKernel_;				// the kernel function gpu used.
	
	vector<vertex>			vertexList_;
	vector<index_type>	indexList_;
	vector<coord>			coordList_;
	
	GLenum	texTarget_;			// target texture coordinate format.
	GLenum texInternalFormat_;	// internal format of texture.
	GLenum texFormat_;			// texture format.
	GLuint	glutWindowHandle_;
	GLuint	fb_;

	LookupTable	texUsage_;
	uint32	lastWriteAttachmentID_;
};
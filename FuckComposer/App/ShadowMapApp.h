#ifndef _SHADOWMAPAPP_H
#define _SHADOWMAPAPP_H

#include "../FCEngine/D3DApp.h"

class FCE_Camera;
class FCE_Effect;
class FCE_RenderPass;
class FCE_RenderObjectImpl;
class FCE_SceneNode;

class ShadowMapApp : public FCE_D3DApp{
public:
	ShadowMapApp();
	~ShadowMapApp();

	virtual void Initialize();

	virtual void CreatePasses();

protected:
	virtual void Release();
	virtual void PreDraw();
	virtual void UpdateBeforePass( FCE_RenderPass* );

	virtual void BeforeResizeBackBuffer( UINT destWith, UINT destHeight );
	virtual void AfterResizeBackBuffer( UINT destWith, UINT destHeight );

private:
	FCE_RenderPass* pCreateShadowPass;
	FCE_RenderPass* pRenderShadowPass;

	FCE_Effect* pCreateShadowEffect;
	FCE_Effect* pRenderShadowEffect;

	FCE_RenderObjectImpl* pPlane;
	FCE_RenderObjectImpl* pBox;

	FCE_SceneNode* pRootNode;
	FCE_SceneNode* pPlaneNode;
	FCE_SceneNode* pBoxNode;

	FCE_Camera* pSceneCamera;
	FCE_Camera* pShadowCamera;
};

#endif
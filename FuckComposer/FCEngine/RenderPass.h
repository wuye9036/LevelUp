#ifndef FCE_RENDER_PASS_H
#define FCE_RENDER_PASS_H

#include <windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <vector>

class FCE_D3DApp;
class FCE_RenderObject;
class FCE_Effect;
class FCE_Camera;
class FCE_Geometry;
class FCE_SceneNode;

class FCE_RenderPass{
public:
	FCE_RenderPass( FCE_D3DApp* pApp );

	void BindTarget( ID3D10RenderTargetView* pRTView, ID3D10DepthStencilView* pDSView );
	void BindScene( FCE_SceneNode* sceneRoot );
	void BindCamera( FCE_Camera* pCam );

	void AddToRenderQueue( FCE_RenderObject* );
	void ClearRenderQueue();

	void Render();

private:
	void ResetTargets();

	void ApplyEffect( FCE_Effect* pEff );
	void ApplyTransform( const FCE_RenderObject* );
	void ApplyCamera( );

	void RenderGeometry( FCE_Geometry* geom );

	FCE_D3DApp* pApp;
	ID3D10RenderTargetView* pRTView;
	ID3D10DepthStencilView* pDSView;

	std::vector<FCE_RenderObject*> objs;

	D3DXMATRIX viewProjMat;
	D3DXMATRIX worldMat;

	FCE_Effect* pEffect;
	FCE_SceneNode* pScene;
	FCE_Camera* pCam;
};

#endif
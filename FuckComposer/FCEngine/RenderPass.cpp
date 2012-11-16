#include "RenderPass.h"

#include "D3DApp.h"
#include "Effect.h"
#include "Geometry.h"
#include "RenderObject.h"
#include "Camera.h"
#include "SceneNode.h"

#include <boost/foreach.hpp>
#include <cassert>

void FCE_RenderPass::BindTarget( ID3D10RenderTargetView* pRTView, ID3D10DepthStencilView* pDSView ){
	ResetTargets();

	this->pRTView = pRTView;
	this->pDSView = pDSView;

	pApp->Device()->OMSetRenderTargets(1, &(this->pRTView), this->pDSView);
}

void FCE_RenderPass::Render()
{
	// Clear
	float color[4] = {0.0f, 0.0f, 0.15f, 1.0f};
	pApp->Device()->ClearRenderTargetView( pRTView, color );
	if( pDSView ){
		pApp->Device()->ClearDepthStencilView( pDSView, D3D10_CLEAR_DEPTH, 1.0f, 0 );
	}

	// Do Draw
	ClearRenderQueue();
	if( pScene ){
		pScene->UpdateToPass( this );
	}

	BOOST_FOREACH( FCE_RenderObject* obj, objs ){
		do{
			if( !obj->IsAvaliable() ){ break; }
			ApplyEffect( obj->Effect() );
			ApplyTransform( obj );
			// Apply Material
			RenderGeometry( obj->Geometry() );
		} while (0);
	}

	// Present
	assert( SUCCEEDED( pApp->SwapChain()->Present(0, 0) ) );
}

FCE_RenderPass::FCE_RenderPass( FCE_D3DApp* pApp )
	: pApp( pApp ), pRTView(NULL), pDSView(NULL), pEffect(NULL), pScene(NULL)
{
}

void FCE_RenderPass::AddToRenderQueue( FCE_RenderObject* obj ){
	objs.push_back(obj);
}

void FCE_RenderPass::ClearRenderQueue(){
	objs.clear();
}

void FCE_RenderPass::ApplyEffect( FCE_Effect* pEff )
{
	pEffect = pEff;
}

void FCE_RenderPass::RenderGeometry( FCE_Geometry* geom )
{
	if( !geom ){ return; }

	D3DXMATRIX transformMat;
	D3DXMatrixMultiply( &transformMat, &worldMat, pCam->ViewProjectionTransform() );

	bool hasIndexBuffer = false;

	if( pEffect ){
		pEffect->BindVariable( "WorldViewProjection", &transformMat, true );

		pEffect->ActivePass()->Apply(0);

		D3D10_PASS_DESC desc;
		pEffect->ActivePass()->GetDesc(&desc);
		pApp->Device()->IASetInputLayout( geom->InputLayout( desc ) );

		pApp->Device()->IASetPrimitiveTopology( geom->Topology() );
		UINT stride = geom->Stride();
		UINT offset = 0;
		ID3D10Buffer* pVB = geom->VertexBuffer();
		pApp->Device()->IASetVertexBuffers( 0, 1, &pVB, &stride, &offset );

		ID3D10Buffer* pIB = geom->IndexBuffer();
		if ( pIB ){
			pApp->Device()->IASetIndexBuffer( pIB, DXGI_FORMAT_R32_UINT, 0 );
			hasIndexBuffer = true;
		}
	}

	if ( hasIndexBuffer ){
		pApp->Device()->DrawIndexed( geom->IndexCount(), 0, 0  );
	} else {
		pApp->Device()->Draw( geom->VertexCount(), 0 );
	}
}

void FCE_RenderPass::ApplyTransform( const FCE_RenderObject* obj ){
	const D3DXMATRIX* pObjWorldMat = obj->Transform( FTS_World );
	if( pObjWorldMat ){
		worldMat = *pObjWorldMat;
	}
}

void FCE_RenderPass::ApplyCamera(){
	viewProjMat = *( pCam->ViewProjectionTransform() );
}

void FCE_RenderPass::BindScene( FCE_SceneNode* sceneRoot ){
	pScene = sceneRoot;
}

void FCE_RenderPass::BindCamera( FCE_Camera* pCam )
{
	this->pCam = pCam;
}

void FCE_RenderPass::ResetTargets()
{
	FCE_SafeRelease(pRTView);
	FCE_SafeRelease(pDSView);
}
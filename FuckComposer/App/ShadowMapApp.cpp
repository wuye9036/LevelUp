#include "ShadowMapApp.h"

#include "../FCEngine/Camera.h"
#include "../FCEngine/Effect.h"
#include "../FCEngine/Geometry.h"
#include "../FCEngine/RenderPass.h"
#include "../FCEngine/SceneNode.h"
#include "../FCEngine/Utility.h"

#define _USE_MATH_DEFINES
#include <math.h>

void ShadowMapApp::Initialize()
{
	FCE_D3DApp::Initialize();
}

void ShadowMapApp::Release(){
	FCE_SafeDelete( pPlane );
	FCE_SafeDelete( pBox );

	FCE_SafeDelete( pRenderShadowPass );
	FCE_SafeDelete( pCreateShadowPass );
	FCE_SafeDelete( pRootNode );

	FCE_SafeDelete( pCreateShadowEffect );
	FCE_SafeDelete( pSceneCamera );
	FCE_SafeDelete( pShadowCamera );

	FCE_D3DApp::Release();
}

ShadowMapApp::~ShadowMapApp(){
	Release();
}

void ShadowMapApp::CreatePasses()
{
	D3DXVECTOR3 pos( 2.0f, 2.0f, 2.0f );
	D3DXVECTOR3 lookAt( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3 up( 0.0f, 1.0f, 0.0f );

	pShadowCamera = new FCE_Camera();
	pShadowCamera->ViewPLU( &pos, &lookAt, &up );
	pShadowCamera->Perspective( M_PI / 2.0f, 1.0f, 0.1f, 1000.0f );

	pRootNode = new FCE_SceneNode( NULL );
	pBoxNode = new FCE_SceneNode( pRootNode );
	pPlaneNode = new FCE_SceneNode( pRootNode );

	D3DXMATRIX planeMat;
	D3DXMATRIX boxMat;
	D3DXMatrixScaling( &planeMat, 4.0f, 4.0f, 4.0f );
	D3DXMatrixTranslation( &boxMat, 0.0, 1.0, 0.0 );
	pBoxNode->Transform( &boxMat, FTS_Local );
	pPlaneNode->Transform( &planeMat, FTS_Local );

	pCreateShadowEffect = FCE_Effect::Load( std::string("Test.fx"), this );

	pPlane = new FCE_RenderObjectImpl( pPlaneNode );
	pPlane->Geometry( FCE_CreatePlane(this) );
	pPlane->Effect( pCreateShadowEffect, true);

	pBox = new FCE_RenderObjectImpl( pBoxNode );
	pBox->Geometry( FCE_CreateBox(this) );
	pBox->Effect( pCreateShadowEffect, true );

	pRenderShadowPass = new FCE_RenderPass( this );
	pRenderShadowPass->BindTarget( BackBuffer(), DefaultDepthStencilView() );
	pRenderShadowPass->BindScene( pRootNode );

	passes.push_back(pRenderShadowPass);
}

ShadowMapApp::ShadowMapApp()
	:pRenderShadowPass(NULL), pCreateShadowPass(NULL),
	pBoxNode(NULL), pRootNode(NULL), pPlaneNode(NULL),
	pCreateShadowEffect(NULL),
	pSceneCamera( NULL ), pShadowCamera( NULL ),
	pPlane(NULL), pBox(NULL)
{
}

void ShadowMapApp::PreDraw()
{
	pRootNode->Update();
}

void ShadowMapApp::UpdateBeforePass( FCE_RenderPass* pPass )
{
	pPass->ClearRenderQueue();

	if( pPass == pCreateShadowPass ){
		pPass->BindCamera( pSceneCamera );
		pCreateShadowEffect->ActivePass( "ShadowBiasTest", "ShadowCreator" );
	} else if ( pPass == pRenderShadowPass ){
		pPass->BindCamera( pShadowCamera );
		pCreateShadowEffect->ActivePass( "ShadowBiasTest", "ShadowRenderer" );
	}
}

void ShadowMapApp::BeforeResizeBackBuffer( UINT destWidth, UINT destHeight )
{
	if ( pRenderShadowPass ){
		pRenderShadowPass->BindTarget(NULL, NULL);
	}
}

void ShadowMapApp::AfterResizeBackBuffer( UINT destWidth, UINT destHeight )
{
	if ( pRenderShadowPass ){
		pRenderShadowPass->BindTarget( BackBuffer(), DefaultDepthStencilView() );
		pShadowCamera->Perspective( float(M_PI/2.0), float(destWidth) / destHeight, 0.1f, 1000.0f );
	}
}
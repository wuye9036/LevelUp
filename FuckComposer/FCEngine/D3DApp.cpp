#include "D3DApp.h"
#include "RenderPass.h"
#include "Utility.h"
#include <d3dx10.h>
#include <boost/foreach.hpp>
#include <cassert>


FCE_D3DApp::FCE_D3DApp() {
}

void FCE_D3DApp::Reset(){
	if ( hWnd == NULL ){
		return;
	}

	Release();
	ResizeBackBuffer( 1, 1, true );
}

FCE_D3DApp::~FCE_D3DApp(){
	Release();
}

void FCE_D3DApp::Release(){
	passes.clear();

	FCE_SafeRelease( pDSView );
	FCE_SafeRelease( pDSTex );
	FCE_SafeRelease( pRTView );
	FCE_SafeRelease( pRTTex );
	FCE_SafeRelease( pSwapChain );
	FCE_SafeRelease( pDev );
}

void FCE_D3DApp::Initialize()
{
	pSwapChain = NULL;
	pDev = NULL;
	pDSTex = NULL;
	pRTTex = NULL;
	pRTView = NULL;
	pDSView = NULL;
}

void FCE_D3DApp::Draw(){
	PreDraw();
	BOOST_FOREACH( FCE_RenderPass* pPass, passes ){
		UpdateBeforePass(pPass);
		pPass->Render();
	}
}

void FCE_D3DApp::WindowHandle( HWND hWnd ){
	if (hWnd != NULL && hWnd != this->hWnd ){
		this->hWnd = hWnd;
		Reset();
	}
}

IDXGISwapChain* FCE_D3DApp::SwapChain() const{
	return pSwapChain;
}

ID3D10Device* FCE_D3DApp::Device() const{
	return pDev;
}

void FCE_D3DApp::PreDraw(){
	// do nothing
}

void FCE_D3DApp::UpdateBeforePass( FCE_RenderPass* ){
	// Do nothing.
}

ID3D10DepthStencilView* FCE_D3DApp::DefaultDepthStencilView(){
	if (pDSView){
		pDSView->AddRef();
	}

	return pDSView;
}

void FCE_D3DApp::ResizeBackBuffer( UINT width, UINT height, bool adjustViewport ){
	BeforeResizeBackBuffer( width, height );

	DXGI_SWAP_CHAIN_DESC desc;

	if( pSwapChain ){
		FCE_SafeRelease(pRTView);
		FCE_SafeRelease(pRTTex);
		pSwapChain->GetDesc( &desc );
		HRESULT hr = pSwapChain->ResizeBuffers( desc.BufferCount, width, height, desc.BufferDesc.Format, desc.Flags );
		assert ( SUCCEEDED(hr) );
	} else {
		ZeroMemory( &desc, sizeof( desc ) );
		desc.BufferCount = 1;
		desc.BufferDesc.Width = width;
		desc.BufferDesc.Height = height;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.OutputWindow = hWnd;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Windowed = TRUE;

		HRESULT hr = D3D10CreateDeviceAndSwapChain(
			NULL, D3D10_DRIVER_TYPE_WARP, NULL, 0,
			D3D10_SDK_VERSION, &desc, &pSwapChain, &pDev
			);

		if ( ! SUCCEEDED(hr) ){
			assert( !"Device Created Failed!" );
			Release();
		}
	}

	FCE_SafeRelease( pDSView );
	FCE_SafeRelease( pDSTex );

	D3D10_TEXTURE2D_DESC texDesc;
	texDesc.ArraySize = 1;
	texDesc.BindFlags = D3D10_BIND_DEPTH_STENCIL;
	texDesc.CPUAccessFlags = 0;
	texDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	texDesc.Height = height;
	texDesc.Width = width;
	texDesc.MipLevels = 1;
	texDesc.MiscFlags = 0;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D10_USAGE_DEFAULT;
	pDev->CreateTexture2D( &texDesc, NULL, &pDSTex );
	pDev->CreateDepthStencilView( pDSTex, NULL, &pDSView );

	if( adjustViewport ){
		UINT vpCount = 1;
		D3D10_VIEWPORT vp;
		pDev->RSGetViewports( &vpCount, &vp );

		ResizeViewport( 0, 0, width, height, 0.0f, 1.0f );
	}

	AfterResizeBackBuffer( width, height );
}

void FCE_D3DApp::ResizeViewport( INT top, INT left, INT width, INT height, float minZ /*= 0.0f*/, float maxZ /*= 1.0f */ )
{
	D3D10_VIEWPORT vp;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.Width = width;
	vp.Height = height;
	vp.TopLeftX = left;
	vp.TopLeftY = top;

	pDev->RSSetViewports( 1, &vp );
}

ID3D10RenderTargetView* FCE_D3DApp::BackBuffer()
{
	if( !pRTView ){
		if (pSwapChain){
			assert( SUCCEEDED( pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), reinterpret_cast<void**>(&pRTTex)) ) );
			assert( SUCCEEDED( pDev->CreateRenderTargetView(pRTTex, NULL, &pRTView) ) );
		} else {
			return NULL;
		}
	}
	pRTView->AddRef();
	return pRTView;
}
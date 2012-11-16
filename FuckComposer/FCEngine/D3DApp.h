#ifndef FCENGINE_D3DAPP_H
#define FCENGINE_D3DAPP_H

#include <windows.h>
#include <d3d10.h>
#include <vector>

class FCE_RenderPass;

class FCE_D3DApp{
public:
	FCE_D3DApp();
	virtual ~FCE_D3DApp();

	virtual void Initialize();
	void Reset();

	void ResizeBackBuffer( UINT width, UINT height, bool adjustViewport );
	void ResizeViewport( INT top, INT left, INT width, INT height, float minZ = 0.0f, float maxZ = 1.0f );

	void Draw();

	// ACCESSORS
	ID3D10Device* Device() const;
	IDXGISwapChain* SwapChain() const;

	ID3D10RenderTargetView* BackBuffer();
	ID3D10DepthStencilView* DefaultDepthStencilView();

	void WindowHandle( HWND hWnd );

protected:
	FCE_D3DApp( const FCE_D3DApp& );
	FCE_D3DApp& operator = ( const FCE_D3DApp& );

	// Events
	virtual void PreDraw();
	virtual void UpdateBeforePass( FCE_RenderPass* );

	virtual void BeforeResizeBackBuffer( UINT destWith, UINT destHeight ){}
	virtual void AfterResizeBackBuffer( UINT srcWidth, UINT srcHeight ){}

	virtual void Release();

	HWND hWnd;
	ID3D10Device* pDev;
	IDXGISwapChain* pSwapChain;
	ID3D10Texture2D* pDSTex;
	ID3D10Texture2D* pRTTex;
	ID3D10DepthStencilView* pDSView;
	ID3D10RenderTargetView* pRTView;

	std::vector<FCE_RenderPass*> passes;
};

#endif
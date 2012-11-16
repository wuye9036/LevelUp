#ifndef FCE_EFFECT_H
#define FCE_EFFECT_H

#include <d3d10.h>
#include <d3dx10.h>
#include <string>
#include <vector>

class FCE_D3DApp;

class FCE_Effect{
public:
	FCE_Effect( FCE_D3DApp* pApp );

	static FCE_Effect* Load(
		const std::string& effectFileName,
		FCE_D3DApp* pApp
		);

	//////////////////////////////////////////////////////////////////////////
	// Setters
	bool ActiveTechnique( const std::string& techName );
	bool ActiveTechnique( UINT index );

	bool ActivePass( const std::string& techName, const std::string& passName );
	bool ActivePass( UINT techniqueIdx, UINT passIdx );
	bool ActivePass( const std::string& passName );
	bool ActivePass( UINT passIdx );

	//////////////////////////////////////////////////////////////////////////
	// Bind.
	void BindVariable( const std::string& name, const D3DXVECTOR4* pVec, bool isSemanticName );
	void BindVariable( const std::string& name, const D3DXMATRIX* pMat, bool isSemanticName );

	//////////////////////////////////////////////////////////////////////////
	// Accessor
	ID3D10Effect* D3DEffect() const;

	ID3D10EffectPass* ActivePass() const;
	ID3D10EffectTechnique* ActiveTechnique() const;

	const char* Error() const;
private:
	void Release();

	ID3D10Blob* pErr;
	ID3D10Effect* pD3DEff;
	ID3D10EffectTechnique* pActiveTech;
	ID3D10EffectPass* pActivePass;

	FCE_D3DApp* pApp;
};

#endif
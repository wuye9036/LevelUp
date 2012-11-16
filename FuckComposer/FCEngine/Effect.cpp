#include "Effect.h"

#include "D3DApp.h"
#include "Utility.h"
#include <boost/foreach.hpp>

FCE_Effect* FCE_Effect::Load( const std::string& effectFileName, FCE_D3DApp* pApp )
{
	FCE_Effect* pEffect = new FCE_Effect(pApp);

	HRESULT hr = D3DX10CreateEffectFromFileA(
		effectFileName.c_str(), 
		NULL, NULL, "fx_4_0",
		0, 0, pApp->Device(),
		NULL, NULL,
		&(pEffect->pD3DEff), &(pEffect->pErr), 
		NULL
		);

	return pEffect;
}

FCE_Effect::FCE_Effect( FCE_D3DApp* pApp )
	: pErr(NULL), pApp(pApp),
	pD3DEff(NULL), pActiveTech(NULL), pActivePass(NULL)
{
	Release();
}

void FCE_Effect::Release()
{
	FCE_SafeRelease( pErr );
	FCE_SafeRelease( pD3DEff );
}

ID3D10Effect* FCE_Effect::D3DEffect() const
{
	return pD3DEff;
}

void FCE_Effect::BindVariable( const std::string& name, const D3DXVECTOR4* pVec, bool isSemanticName )
{
	if( !pD3DEff ) return;

	ID3D10EffectVectorVariable* pVar = NULL;
	if( isSemanticName ){
		pVar = pD3DEff->GetVariableBySemantic( name.c_str() )->AsVector();
	} else {
		pVar = pD3DEff->GetVariableByName( name.c_str() )->AsVector();
	}

	if ( pVar ){
		pVar->SetFloatVector( (float*)pVec );
	}
}

void FCE_Effect::BindVariable( const std::string& name, const D3DXMATRIX* pMat, bool isSemanticName )
{
	if( !pD3DEff ) return;

	ID3D10EffectMatrixVariable* pVar = NULL;
	if( isSemanticName ){
		pVar = pD3DEff->GetVariableBySemantic( name.c_str() )->AsMatrix();
	} else {
		pVar = pD3DEff->GetVariableByName( name.c_str() )->AsMatrix();
	}

	if ( pVar ){
		pVar->SetMatrix( (float*)pMat );
	}
}

bool FCE_Effect::ActiveTechnique( const std::string& techName )
{
	if( !pD3DEff ) return false;
	pActiveTech = pD3DEff->GetTechniqueByName( techName.c_str() );
	return pActiveTech != NULL;
}

bool FCE_Effect::ActiveTechnique( UINT index )
{
	if( !pD3DEff ) return false;
	pActiveTech = pD3DEff->GetTechniqueByIndex( index );
	return pActiveTech != NULL;
}

ID3D10EffectTechnique* FCE_Effect::ActiveTechnique() const{
	return pActiveTech;
}

bool FCE_Effect::ActivePass( const std::string& techName, const std::string& passName ){
	return ActiveTechnique( techName ) && ActivePass( passName );
}

bool FCE_Effect::ActivePass( UINT techniqueIdx, UINT passIdx ){
	return ActiveTechnique(techniqueIdx) && ActivePass( passIdx );
}

bool FCE_Effect::ActivePass( const std::string& passName ){
	if( pActiveTech == NULL ){
		return false;
	}
	pActivePass = pActiveTech->GetPassByName( passName.c_str() );
	return pActivePass != NULL;
}

bool FCE_Effect::ActivePass( UINT passIdx ){
	if( pActiveTech == NULL ){
		return false;
	}
	pActivePass = pActiveTech->GetPassByIndex( passIdx );
	return pActivePass != NULL;
}

ID3D10EffectPass* FCE_Effect::ActivePass() const{
	return pActivePass;
}

const char* FCE_Effect::Error() const{
	return pErr ? (const char*)( pErr->GetBufferPointer() ) : "";
}

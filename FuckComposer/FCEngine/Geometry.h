#ifndef FCE_GEOMETRY_H
#define FCE_GEOMETRY_H

#include "D3DApp.h"
#include <d3d10.h>
#include <d3dx10.h>
#include <D3DX10math.h>
#include <vector>
#include "Utility.h"

class FCE_D3DApp;

class FCE_Geometry{
public:
	virtual ID3D10Buffer* VertexBuffer() const = 0;
	virtual ID3D10Buffer* IndexBuffer() const = 0;

	virtual ID3D10InputLayout* InputLayout( const D3D10_PASS_DESC& passDesc ) const = 0;
	virtual UINT Stride() const = 0;

	virtual D3D10_PRIMITIVE_TOPOLOGY Topology() const = 0;

	virtual UINT IndexCount() const = 0;
	virtual UINT VertexCount() const = 0;

	virtual ~FCE_Geometry(){};
};

class FCE_GeometryImpl: public FCE_Geometry{
public:
	FCE_GeometryImpl( FCE_D3DApp* pApp )
		: pApp(pApp), topo(D3D10_PRIMITIVE_TOPOLOGY_UNDEFINED),
		ib(NULL), vb(NULL), inputLayout(NULL), stride(0),
		indexCnt(0), vertexCnt(0)
	{}

	virtual ID3D10Buffer* VertexBuffer() const{ return vb; }
	void VertexBuffer( ID3D10Buffer* buf ){ vb = buf; }
	virtual UINT VertexCount() const { return vertexCnt; }
	void VertexCount( UINT cnt ) { vertexCnt = cnt; }

	virtual ID3D10Buffer* IndexBuffer() const{ return ib; }
	void IndexBuffer( ID3D10Buffer* buf ){ ib = buf; }
	virtual UINT IndexCount() const { return indexCnt; }
	void IndexCount( UINT cnt ) { indexCnt = cnt; }

	virtual UINT Stride() const{ return stride; }
	void Stride( UINT s ) { stride = s; }

	virtual D3D10_PRIMITIVE_TOPOLOGY Topology() const{ return topo; }
	void Topology( D3D10_PRIMITIVE_TOPOLOGY topo ) { this->topo = topo; }

	virtual ID3D10InputLayout* InputLayout( const D3D10_PASS_DESC& passDesc ) const{
		if ( !inputLayout ){
			pApp->Device()->CreateInputLayout(
				&(inputDesc[0]), (UINT)inputDesc.size(),
				passDesc.pIAInputSignature, passDesc.IAInputSignatureSize,
				const_cast<ID3D10InputLayout**>(&inputLayout)
				);
		}

		return inputLayout;
	}

	void AddInputElementDescription( const D3D10_INPUT_ELEMENT_DESC& desc ){ inputDesc.push_back(desc); }

	virtual ~FCE_GeometryImpl(){
		Release();
	}
protected:
	void Release(){
		FCE_SafeRelease( vb );
		FCE_SafeRelease( ib );
		FCE_SafeRelease( inputLayout );
	}

	FCE_D3DApp* pApp;
	UINT indexCnt;
	UINT vertexCnt;
	std::vector< D3D10_INPUT_ELEMENT_DESC > inputDesc;
	ID3D10InputLayout* inputLayout;
	D3D10_PRIMITIVE_TOPOLOGY topo;
	ID3D10Buffer* vb;
	ID3D10Buffer* ib;
	UINT stride;
};

FCE_Geometry* FCE_CreatePlane( FCE_D3DApp* pApp );
FCE_Geometry* FCE_CreateBox( FCE_D3DApp* pApp );

#endif
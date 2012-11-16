#include "Geometry.h"

#include "Utility.h"

#include "D3DApp.h"
#include "D3DX10.h"
#include <boost/foreach.hpp>

FCE_Geometry* FCE_CreateGeometry(
	FCE_D3DApp* pApp,
	void* pVertData, UINT vertSize, UINT vertCnt,
	DWORD* indexes, UINT indexCnt,
	D3D10_PRIMITIVE_TOPOLOGY topo,
	const std::vector<D3D10_INPUT_ELEMENT_DESC>& descs
	)
{
	FCE_GeometryImpl* pGeom = new FCE_GeometryImpl( pApp );

	// Create Vertex Buffer
	D3D10_BUFFER_DESC vbDesc;
	ZeroMemory( &vbDesc, sizeof(vbDesc) );

	vbDesc.ByteWidth = vertSize * vertCnt;
	vbDesc.Usage = D3D10_USAGE_DEFAULT;
	vbDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	vbDesc.CPUAccessFlags = 0;
	vbDesc.MiscFlags = 0;

	D3D10_SUBRESOURCE_DATA rawVBData;
	ZeroMemory( &rawVBData, sizeof(rawVBData) );
	rawVBData.pSysMem = pVertData;

	ID3D10Buffer* pVB = NULL;
	HRESULT hr = pApp->Device()->CreateBuffer( &vbDesc, &rawVBData, &pVB );

	pGeom->VertexBuffer( pVB );
	pGeom->Stride( vertSize );
	pGeom->VertexCount( vertCnt );

	// Create Index Buffer
	D3D10_BUFFER_DESC ibDesc;
	ZeroMemory( &ibDesc, sizeof(vbDesc) );

	ibDesc.ByteWidth = sizeof(DWORD) * indexCnt;
	ibDesc.Usage = D3D10_USAGE_DEFAULT;
	ibDesc.BindFlags = D3D10_BIND_INDEX_BUFFER;
	ibDesc.CPUAccessFlags = 0;
	ibDesc.MiscFlags = 0;

	D3D10_SUBRESOURCE_DATA rawIBData;
	ZeroMemory( &rawIBData, sizeof(rawIBData) );
	rawIBData.pSysMem = indexes;

	ID3D10Buffer* pIB = NULL;
	pApp->Device()->CreateBuffer( &ibDesc, &rawIBData, &pIB );
	pGeom->IndexBuffer( pIB );
	pGeom->IndexCount( indexCnt );

	// Set Other properties
	pGeom->Topology( topo );

	// Add description
	BOOST_FOREACH( const D3D10_INPUT_ELEMENT_DESC& desc, descs ){
		pGeom->AddInputElementDescription(desc);
	}

	return pGeom;
}

FCE_Geometry* FCE_CreatePlane( FCE_D3DApp* pApp )
{
	// !!!HARD CORE!!!
	float vertexes[4][4] = {
		{ -0.5f,  0.0f, -0.5f, 1.0f },
		{ -0.5f,  0.0f,  0.5f, 1.0f },
		{  0.5f,  0.0f,  0.5f, 1.0f },
		{  0.5f,  0.0f, -0.5f, 1.0f }
	};
	DWORD indexes[] = { 0, 1, 2, 2, 3, 0 };

	std::vector<D3D10_INPUT_ELEMENT_DESC> descs;
	descs.resize(1);
	
	D3D10_INPUT_ELEMENT_DESC& desc = descs[0];

	ZeroMemory( &desc, sizeof(desc) );
	desc.SemanticName = "POSITION";
	desc.SemanticIndex = 0;
	desc.InputSlot = 0;
	desc.InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc.InstanceDataStepRate = 0;
	desc.AlignedByteOffset = 0;

	return
		FCE_CreateGeometry(
		pApp,
		&(vertexes[0][0]), sizeof(D3DXVECTOR4), 4, 
		&(indexes[0]), 6,
		D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		descs
		);
}

FCE_Geometry* FCE_CreateBox( FCE_D3DApp* pApp )
{
	float corners[8][4] = 
	{
		// bottom face
		{ -0.5f, -0.5f, -0.5f, 1.0f },
		{ -0.5f, -0.5f,  0.5f, 1.0f },
		{  0.5f, -0.5f,  0.5f, 1.0f },
		{  0.5f, -0.5f, -0.5f, 1.0f },

		// top face
		{ -0.5f,  0.5f, -0.5f, 1.0f },
		{ -0.5f,  0.5f,  0.5f, 1.0f },
		{  0.5f,  0.5f,  0.5f, 1.0f },
		{  0.5f,  0.5f, -0.5f, 1.0f }
	};

	D3DXVECTOR4 faceVerts[24];

	// bottom face
	faceVerts[0] = corners[0];
	faceVerts[1] = corners[3];
	faceVerts[2] = corners[2];
	faceVerts[3] = corners[1];

	// top face
	faceVerts[4] = corners[4];
	faceVerts[5] = corners[5];
	faceVerts[6] = corners[6];
	faceVerts[7] = corners[7];

	// left face
	faceVerts[8] = corners[1];
	faceVerts[9] = corners[2];
	faceVerts[10] = corners[6];
	faceVerts[11] = corners[5];

	// right face
	faceVerts[12] = corners[0];
	faceVerts[13] = corners[4];
	faceVerts[14] = corners[7];
	faceVerts[15] = corners[3];

	// front face
	faceVerts[16] = corners[0];
	faceVerts[17] = corners[1];
	faceVerts[18] = corners[5];
	faceVerts[19] = corners[4];

	// back face
	faceVerts[20] = corners[2];
	faceVerts[21] = corners[3];
	faceVerts[22] = corners[7];
	faceVerts[23] = corners[6];

	DWORD indexes[36];
	for ( UINT faceId = 0; faceId < 6; ++faceId ){
		indexes[faceId*6+0] = faceId*4+0;
		indexes[faceId*6+1] = faceId*4+1;
		indexes[faceId*6+2] = faceId*4+2;
		indexes[faceId*6+3] = faceId*4+2;
		indexes[faceId*6+4] = faceId*4+3;
		indexes[faceId*6+5] = faceId*4+0;
	}

	std::vector<D3D10_INPUT_ELEMENT_DESC> descs;
	descs.resize(1);

	D3D10_INPUT_ELEMENT_DESC& desc = descs[0];

	ZeroMemory( &desc, sizeof(desc) );
	desc.SemanticName = "POSITION";
	desc.SemanticIndex = 0;
	desc.InputSlot = 0;
	desc.InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc.InstanceDataStepRate = 0;
	desc.AlignedByteOffset = 0;

	return FCE_CreateGeometry(
		pApp,
		&faceVerts[0], sizeof(D3DXVECTOR4), 24,
		&(indexes[0]), 36,
		D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST, descs
		);
}

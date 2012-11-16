#include "RenderObject.h"

#include "Effect.h"
#include "Geometry.h"
#include "SceneNode.h"

FCE_RenderObjectImpl::FCE_RenderObjectImpl( FCE_SceneNode* node )
	: sceneNode(NULL), pEffect(NULL), pMaterial(NULL), pGeometry(NULL),
	isSharedEffect(false)
{
	if( node ){
		node->AppendContent( this );
	}
}

FCE_RenderObjectImpl::~FCE_RenderObjectImpl()
{
	Release();
}

FCE_SceneNode* FCE_RenderObjectImpl::SceneNode() const
{
	return sceneNode;
}

void FCE_RenderObjectImpl::SceneNode( FCE_SceneNode* pNode )
{
	sceneNode = pNode;
}

const D3DXMATRIX* FCE_RenderObjectImpl::Transform( FCE_TransformSemantic semantic ) const
{
	return sceneNode->Transform( semantic );
}

FCE_Geometry* FCE_RenderObjectImpl::Geometry() const
{
	return pGeometry;
}

void FCE_RenderObjectImpl::Geometry( FCE_Geometry* pGeom )
{
	pGeometry = pGeom;
}

FCE_Material* FCE_RenderObjectImpl::Material() const
{
	return pMaterial;
}

FCE_Effect* FCE_RenderObjectImpl::Effect() const
{
	return pEffect;
}

void FCE_RenderObjectImpl::Effect( FCE_Effect* pEff, bool isShared )
{
	pEffect = pEff;
	isSharedEffect = isShared;
}

void FCE_RenderObjectImpl::Release()
{
	if( sceneNode ){
		sceneNode->RemoveContent(this);
	}

	FCE_SafeDelete( pGeometry );
	FCE_SafeDelete( pMaterial );

	if( !isSharedEffect ){
		FCE_SafeDelete( pEffect );
	} else {
		isSharedEffect = false;
		pEffect = NULL;
	}
}

bool FCE_RenderObjectImpl::IsAvaliable() const{
	return true;
}

void FCE_RenderObjectImpl::Update(){
}

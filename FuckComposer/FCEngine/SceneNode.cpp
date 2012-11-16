#include "SceneNode.h"

#include "RenderPass.h"

#include <boost/foreach.hpp>
#include <algorithm>
#include <cassert>

const D3DXMATRIX* FCE_SceneNode::Transform( FCE_TransformSemantic semantic )
{
	switch ( semantic )
	{
	case FTS_Local:
		return &local;
	case FTS_World:
		return &world;
	default:
		return NULL;
	}
}

void FCE_SceneNode::Transform( const D3DXMATRIX* mat, FCE_TransformSemantic semantic )
{
	switch( semantic ){
	case FTS_Local:
		local = *mat;
		break;
	case FTS_World:
		world = *mat;
		break;
	}
}

void FCE_SceneNode::Update()
{
	// Update itself.
	if( parent ){
		D3DXMatrixMultiply( &world, &parent->world, &local );
	} else {
		world = local;
	}

	// Update containing objects.
	BOOST_FOREACH( FCE_RenderObject* obj, objs ){
		obj->Update();
	}

	// Update sub nodes.
	BOOST_FOREACH( FCE_SceneNode* node, subNodes ){
		node->Update();
	}
}

FCE_SceneNode::FCE_SceneNode( FCE_SceneNode* parent ): parent(NULL){
	if ( parent ){
		parent->AppendChild( this );
	}
	D3DXMatrixIdentity( &local );
	D3DXMatrixIdentity( &world );
}

void FCE_SceneNode::UpdateToPass( FCE_RenderPass* pPass )
{
	BOOST_FOREACH( FCE_RenderObject* obj, objs ){
		pPass->AddToRenderQueue(obj);
	}
	
	BOOST_FOREACH( FCE_SceneNode* node, subNodes ){
		node->UpdateToPass( pPass );
	}
}

void FCE_SceneNode::AppendChild( FCE_SceneNode* pChild ){
	assert( pChild->Parent() == NULL );

	pChild->parent = this;
	subNodes.push_back(pChild);
}

void FCE_SceneNode::RemoveChild( FCE_SceneNode* pChild ){
	assert( pChild->Parent() == this );

	pChild->parent = NULL;

	std::vector<FCE_SceneNode*>::iterator it = std::find( subNodes.begin(), subNodes.end(), pChild );
	if( it != subNodes.end() ){
		subNodes.erase( it );
	}
}

void FCE_SceneNode::AppendContent( FCE_RenderObject* pObj ){
	assert( pObj->SceneNode() == NULL );

	pObj->SceneNode( this );
	objs.push_back( pObj );
}

void FCE_SceneNode::RemoveContent( FCE_RenderObject* pObj ){
	assert( pObj->SceneNode() == this );

	pObj->SceneNode(NULL);

	std::vector<FCE_RenderObject*>::iterator it = std::find( objs.begin(), objs.end(), pObj );
	if( it != objs.end() ){
		objs.erase( it );
	}
}

FCE_SceneNode::~FCE_SceneNode()
{
	if( parent ){
		parent->RemoveChild( this );
	}

	// copy subNodes and objs
	// because origin iterator may be unavailable while deleting.
	// reversing the copy for efficency, because the last element will be deleted.
	std::vector< FCE_RenderObject* > objsCopy( objs.rbegin(), objs.rend() );
	std::vector< FCE_SceneNode* > subNodesCopy( subNodes.rbegin(), subNodes.rend() );

	BOOST_FOREACH( FCE_RenderObject* pObj, objsCopy ){
		RemoveContent( pObj );
	}

	BOOST_FOREACH( FCE_SceneNode* pNode, subNodesCopy ){
		delete pNode;
	}
}

FCE_SceneNode* FCE_SceneNode::Parent() const
{
	return parent;
}

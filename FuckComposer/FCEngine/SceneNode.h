#ifndef FCE_SCENE_NODE_H
#define FCE_SCENE_NODE_H

#include "RenderObject.h"
#include <D3DX10.h>
#include <vector>

class FCE_RenderPass;

class FCE_SceneNode{
	friend class FCE_RenderObjectImpl;

public:
	FCE_SceneNode( FCE_SceneNode* parent );
	~FCE_SceneNode();

	FCE_SceneNode* Parent() const;

	virtual void AppendChild( FCE_SceneNode* );
	virtual void RemoveChild( FCE_SceneNode* );

	virtual void AppendContent( FCE_RenderObject* );
	virtual void RemoveContent( FCE_RenderObject* );

	virtual const D3DXMATRIX* Transform( FCE_TransformSemantic semantic );
	virtual void Transform( const D3DXMATRIX* mat, FCE_TransformSemantic semantic );

	virtual void Update();
	virtual void UpdateToPass( FCE_RenderPass* );

private:
	D3DXMATRIX world;
	D3DXMATRIX local;

	FCE_SceneNode* parent;
	
	std::vector<FCE_RenderObject*> objs;
	std::vector<FCE_SceneNode*> subNodes;
};

#endif
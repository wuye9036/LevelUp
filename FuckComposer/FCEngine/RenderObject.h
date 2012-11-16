#ifndef FCE_RENDEROBJECT_H
#define FCE_RENDEROBJECT_H

#include <D3DX10math.h>
#include "Utility.h"

class FCE_Geometry;
class FCE_Material;
class FCE_Effect;
class FCE_SceneNode;

enum FCE_TransformSemantic{
	FTS_Local,
	FTS_World,
	FTS_View,
	FTS_WV,
	FTS_WVP,
	FTS_WVPIT,
	FTS_UNDEFINED = 0xFFFFFFFF
};

class FCE_RenderObject{
	friend class FCE_SceneNode;

public:
	virtual bool IsAvaliable() const = 0;

	virtual void Update() = 0;

	virtual FCE_SceneNode* SceneNode() const = 0;

	virtual const D3DXMATRIX* Transform( FCE_TransformSemantic semantic ) const = 0;
	virtual FCE_Geometry* Geometry() const = 0;
	virtual FCE_Material* Material() const = 0;
	virtual FCE_Effect* Effect() const = 0;

	virtual ~FCE_RenderObject(){}

private:
	virtual void SceneNode( FCE_SceneNode* ) = 0;
};

class FCE_RenderObjectImpl: public FCE_RenderObject{
public:
	FCE_RenderObjectImpl( FCE_SceneNode* node );

	~FCE_RenderObjectImpl();

	virtual bool IsAvaliable() const;

	virtual void Update();

	virtual FCE_SceneNode* SceneNode() const;
	virtual void SceneNode( FCE_SceneNode* );

	virtual const D3DXMATRIX* Transform( FCE_TransformSemantic semantic ) const;
	virtual FCE_Geometry* Geometry() const;
	virtual void Geometry( FCE_Geometry* );

	virtual FCE_Material* Material() const;

	virtual FCE_Effect* Effect() const;
	virtual void Effect( FCE_Effect*, bool isShared );
protected:
	void Release();

	FCE_SceneNode* sceneNode;

	FCE_Effect* pEffect;
	bool isSharedEffect;

	FCE_Material* pMaterial;
	FCE_Geometry* pGeometry;
};
#endif
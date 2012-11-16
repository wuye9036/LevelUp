#ifndef FCE_CAMERA_H
#define FCE_CAMERA_H

#include <D3DX10.h>

class FCM_Frustum;

class FCE_Camera{
public:
	FCE_Camera();
	
	void Reset();

	void ViewPLU( const D3DXVECTOR3* pos, const D3DXVECTOR3* lookAt, const D3DXVECTOR3* up );
	void Perspective( float fovy, float aspect, float near_z, float far_z );
	void Ortho( float width, float height, float near_z, float far_z );

	const D3DXMATRIX* ViewTransform() const;
	const D3DXMATRIX* ProjectionTransform() const;
	const D3DXMATRIX* ViewProjectionTransform() const;

	const FCM_Frustum* Frustum() const;
private:
	D3DXMATRIX viewMat;
	D3DXMATRIX projMat;
	D3DXMATRIX viewProjMat;
};

#endif
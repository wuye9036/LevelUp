#include "Camera.h"

void FCE_Camera::ViewPLU( const D3DXVECTOR3* pos, const D3DXVECTOR3* lookAt, const D3DXVECTOR3* up )
{
	D3DXMatrixLookAtLH( &viewMat, pos, lookAt, up );
	D3DXMatrixMultiply( &viewProjMat, &viewMat, &projMat );
}

void FCE_Camera::Perspective( float fovy, float aspect, float near_z, float far_z ){
	D3DXMatrixPerspectiveFovLH( &projMat, fovy, aspect, near_z, far_z );
	D3DXMatrixMultiply( &viewProjMat, &viewMat, &projMat );
}

void FCE_Camera::Ortho( float width, float height, float near_z, float far_z ){
	D3DXMatrixOrthoLH( &projMat, width, height, near_z, far_z );
	D3DXMatrixMultiply( &viewProjMat, &viewMat, &projMat );
}

const D3DXMATRIX* FCE_Camera::ViewTransform() const{
	return &viewMat;
}

const D3DXMATRIX* FCE_Camera::ProjectionTransform() const{
	return &projMat;
}

const D3DXMATRIX* FCE_Camera::ViewProjectionTransform() const{
	return &viewProjMat;
}

FCE_Camera::FCE_Camera(){
	Reset();
}

void FCE_Camera::Reset()
{
	D3DXMatrixIdentity( &viewMat );
	D3DXMatrixIdentity( &projMat );
	D3DXMatrixIdentity( &viewProjMat );
}

const FCM_Frustum* FCE_Camera::Frustum() const
{
	return NULL;
}

#ifndef _FCE_MATH_H
#define _FCE_MATH_H

#include <D3DX10.h>

template <typename ComponentT, typename T>
T* FCE_MinComponents( T* pOut, const T* pIn0, const T* pIn1 ){
	for( int i = 0; i < sizeof(T) / sizeof(ComponentT), ++i ){
		static_cast<ComponentT*>(pOut)[i] = min( static_cast<const ComponentT*>(pIn0)[i], static_cast<const ComponentT*>(pIn1)[i] );
	}
	return pOut;
}

template <typename ComponentT, typename T>
T* FCE_MaxComponents( T* pOut, const T* pIn0, const T* pIn1 ){
	for( int i = 0; i < sizeof(T) / sizeof(ComponentT), ++i ){
		static_cast<ComponentT*>(pOut)[i] = max( static_cast<const ComponentT*>(pIn0)[i], static_cast<const ComponentT*>(pIn1)[i] );
	}
	return pOut;
}


class FCE_AxisAlignedBoundingBox{
public:
	FCE_AxisAlignedBoundingBox();

	void SetNull();

	void AddPoints( UINT count, const D3DXVECTOR3* pPoint );
	void AddBox( const FCE_AxisAlignedBoundingBox* pBox );
	bool IsInBox( const D3DXVECTOR3* pPoint );

	void Corners( D3DXVECTOR3* pOut );

	FCE_AxisAlignedBoundingBox Transform( const D3DXMATRIX* pMat );
private:
	D3DXVECTOR3 minPos;
	D3DXVECTOR3 maxPos;
	bool isNull;
};
#endif


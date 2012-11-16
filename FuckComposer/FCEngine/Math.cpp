#include "Math.h"

FCE_AxisAlignedBoundingBox::FCE_AxisAlignedBoundingBox(): isNull(true){
}

void FCE_AxisAlignedBoundingBox::SetNull()
{
	isNull = true;
}


void FCE_AxisAlignedBoundingBox::AddPoints( UINT count, const D3DXVECTOR3* pPoint )
{
	if ( count == 0) { return; }
	if( isNull ){
		isNull = false;
		minPos = maxPos = pPoint[0];
	}
	for( UINT iPt = 1; iPt < count; ++iPt ){
		D3DXVec3Minimize( &minPos, &(pPoint[iPt]), &minPos );
		D3DXVec3Maximize( &maxPos, &(pPoint[iPt]), &maxPos );
	}
}

void FCE_AxisAlignedBoundingBox::AddBox( const FCE_AxisAlignedBoundingBox* pBox ){
	if ( pBox->isNull ) return;
	AddPoints(1, &minPos);
	AddPoints(1, &maxPos);
}

bool FCE_AxisAlignedBoundingBox::IsInBox( const D3DXVECTOR3* pPoint ){
	if( isNull ) return false;
	return
		pPoint->x >= minPos.x && pPoint->y >= minPos.y && pPoint->z >= minPos.z &&
		pPoint->x <= maxPos.x && pPoint->y <= maxPos.y && pPoint->z <= maxPos.z
		;
}

void FCE_AxisAlignedBoundingBox::Corners( D3DXVECTOR3* pOut ){
	pOut[0] = D3DXVECTOR3(minPos.x, minPos.y, minPos.z);
	pOut[1] = D3DXVECTOR3(maxPos.x, minPos.y, minPos.z);
	pOut[2] = D3DXVECTOR3(minPos.x, minPos.y, maxPos.z);
	pOut[3] = D3DXVECTOR3(minPos.x, minPos.y, maxPos.z);

	pOut[4] = D3DXVECTOR3(minPos.x, maxPos.y, minPos.z);
	pOut[5] = D3DXVECTOR3(maxPos.x, maxPos.y, minPos.z);
	pOut[6] = D3DXVECTOR3(minPos.x, maxPos.y, maxPos.z);
	pOut[7] = D3DXVECTOR3(minPos.x, maxPos.y, maxPos.z);
}

FCE_AxisAlignedBoundingBox FCE_AxisAlignedBoundingBox::Transform( const D3DXMATRIX* pMat ){
	D3DXVECTOR3 pCorners[8];
	Corners(pCorners);
	FCE_AxisAlignedBoundingBox ret;

	for( int iCorner = 0; iCorner < 8; ++iCorner ){
		D3DXVECTOR3 transformed;
		D3DXVec3TransformCoord( &transformed, &(pCorners[iCorner]), pMat );
		ret.AddPoints(1, &transformed );
	}

	return ret;
}

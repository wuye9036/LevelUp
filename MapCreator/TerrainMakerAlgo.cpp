#include "TerrainMakerAlgo.h"
#include "stdafx.h"
/* Copyright (C) Jason Shankel, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Jason Shankel, 2000"
 */
#include <stdlib.h>
#include <math.h>
#include <memory.h>

/*
height field typedef
*/
typedef float *height_field_t;

/*
Function prototypes
*/
void NormalizeTerrain(height_field_t field,int size);
void FilterHeightBand(float *band,int stride,int count,float filter);

/*
Returns a random number between v1 and v2
*/
float Random(float lower,float upper)
{
	return lower + (upper-lower)*((float)rand())/((float)RAND_MAX);
}

/*
Given a height field, normalize it so that the minimum altitude
is 0.0 and the maximum altitude is 1.0
*/
void NormalizeTerrain(height_field_t field,int size)
{
	float maxVal,minVal,dh;
	int i;

	/*
	Find the maximum and minimum values in the height field
	*/ 
	maxVal = field[0];
	minVal = field[0];

	for (i=1;i<size*size;i++)
	{
		if (field[i] > maxVal) 
		{
			maxVal = field[i];
		}
		else if (field[i] < minVal) 
		{
			minVal = field[i];
		}
	}

	/*
	Find the altitude range (dh)
	*/
	if (maxVal <= minVal) return;
	dh = maxVal-minVal;

	/*
	Scale all the values so they are in the range 0-1
	*/
	for (i=0;i<size*size;i++)
	{
		field[i] = (field[i]-minVal)/dh;
	}

}

/*
Erosion filter -
FilterHeightBand applies a FIR filter across a row or column of the height field
*/
void FilterHeightBand(float *band,int stride,int count,float filter)
{
	int i,j=stride;
	float v = band[0];
	for (i=0;i<count-1;i++)
	{
		band[j] = filter*v + (1-filter)*band[j];
		v = band[j];
		j+=stride;
	}
}

/*
Erosion filter -
Erodes a terrain in all 4 directions
*/
void FilterHeightField(float* field,int size,float filter)
{
	int i;

	/*
	Erode rows left to right
	*/
	for (i=0;i<size;i++)
	{
		FilterHeightBand(&field[size*i],1,size,filter);
	}
	
	/*
	Erode rows right to left
	*/
	for (i=0;i<size;i++)
	{
		FilterHeightBand(&field[size*i+size-1],-1,size,filter);
	}

	/*
	Erode columns top to bottom
	*/
	for (i=0;i<size;i++)
	{
		FilterHeightBand(&field[i],size,size,filter);
	}

	/*
	Erode columns bottom to top
	*/
	for (i=0;i<size;i++)
	{
		FilterHeightBand(&field[size*(size-1)+i],-size,size,filter);
	}
}


/*
Genereate terrain using diamond-square (plasma) algorithm
*/
void MakeTerrainPlasma(float* field,int _size,float rough)
{
	int size = _size;
	int i,j,ni,nj,mi,mj,pmi,pmj,rectSize = size;

	float dh = (float)rectSize/2;
	float r = (float)pow(2.0f,-1*rough);

	/*
	Since the terrain wraps, all 4 "corners" are represented by the value at 0,0,
		so seeding the heightfield is very straightforward
	Note that it doesn't matter what we use for a seed value, since we're going to
		renormalize the terrain after we're done
	*/
	field[0] = 1;


	while(rectSize > 0)
	{
		//方形中心取法
		/*
		a   b
		  c
		d   e
		*/
		for (i=0;i<size;i+=rectSize)
		{
			for (j=0;j<size;j+=rectSize)
			{
			
				ni = (i+rectSize)%size;
				nj = (j+rectSize)%size;

				mi = (i+rectSize/2)%size;
				mj = (j+rectSize/2)%size;

				field[mi+mj*_size] = (field[i+j*_size] + field[ni+j*_size] + field[i+nj*_size] + field[ni+nj*_size])/4 + Random(-dh/2,dh/2);
			}
		}

		//菱形中心取法
		for (i=0;i<size;i+=rectSize)
		{
			for (j=0;j<size;j+=rectSize)
			{

				ni = (i+rectSize)%size;
				nj = (j+rectSize)%size;

				mi = (i+rectSize/2)%size;
				mj = (j+rectSize/2)%size;

				pmi = (i-rectSize/2+size)%size;
				pmj = (j-rectSize/2+size)%size;

				field[mi+j*_size] = (field[i+j*_size] + field[ni+j*_size] + field[mi+pmj*_size] + field[mi+mj*_size])/4 + Random(-dh/2,dh/2);

				field[i+mj*_size] = (field[i+j*_size] + field[i+nj*_size] + field[pmi+mj*_size] + field[mi+mj*_size])/4 + Random(-dh/2,dh/2);

			}
		}

		/*
		Setup values for next iteration
		At this point, the height field has valid values at each of the coordinates that fall on a rectSize/2 boundary
		*/
		rectSize  = rectSize >> 1;
		dh *= r;
	}
	/*
	Normalize terrain so minimum value is 0 and maximum value is 1
	*/
	NormalizeTerrain(field,size);
}

void MakeTerrainFault(float* field,int size,int iterations,int maxDelta,int minDelta,int iterationsPerFilter,float filter)
{
	int x1,y1,x2,y2,dx1,dy1,dx2,dy2,i,dHeight;

	/*
	Clear the height field
	*/
	for (i=0;i<size*size;i++)
	{
		field[i] = 0.0f;
	}

	for (i=0;i<iterations;i++)
	{
		/*
		Calculate the dHeight for this iteration
		(linear interpolation from maxDelta to minDelta
		*/
		dHeight = maxDelta - ((maxDelta-minDelta)*i)/iterations;
		
		/*
		Pick two random points on the field for the line
		(make sure they're not identical)
		*/
		x1 = rand()%size;
		y1 = rand()%size;
		
		do
		{
			x2 = rand()%size;
			y2 = rand()%size;
		}while (x2==x1 && y2==y1);

		
		/*
		dx1,dy1 is a vector in the direction of the line
		*/
		dx1 = x2 - x1;
		dy1 = y2 - y1;
		
		for (x2 = 0;x2<size;x2++)
		for (y2 = 0;y2<size;y2++)
		{
			/*
			dx2,dy2 is a vector from x1,y1 to the candidate point
			*/
			dx2 = x2-x1;
			dy2 = y2-y1;
			
			/*
			if z component of the cross product is 'up', then elevate this point
			*/
			if (dx2*dy1 - dx1*dy2 > 0)
			{
				field[x2+size*y2] += (float)(dHeight);
			}

		}

		/*
		Erode terrain
		*/
		if (iterationsPerFilter!=0 && (i%iterationsPerFilter)==0)
			FilterHeightField(field,size,filter);
	}

	/*
	Normalize terrain (height field values in the range 0-1)
	*/
	NormalizeTerrain(field,size);

}

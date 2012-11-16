#include <stdlib.h>
#include <math.h>

float Random(float lower,float upper);
void FilterHeightField(float* field,int size,float filter);
void MakeTerrainPlasma(float* field,int size,float rough);
void MakeTerrainFault(float* field,int size, int iterations,int maxDelta,int minDelta,int iterationsPerFilter,float filter);
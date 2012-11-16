#pragma once
#include <efl/eflib.h>
#include <vector>

using namespace efl;
using namespace std;

void draw_pixel(int x, int y, float z, float t);
void draw_pixel(int x, int y, float z, float u, float v);

//线的光栅化,DDA算法
void rasterize_line(const vec4& start, const vec4& end);

vector<int> draw_line(int sx, int sy, int ex, int ey);
vector<int> draw_tri(int v0x, int v0y, int v1x, int v1y, int v2x, int v2y);

//分割成上下两个三角形，重心坐标系参数方程p = u*v1 + v*v2 + (1-u-v)*v0
void rasterize_triangle(const vec4& v0, const vec4& v1, const vec4& v2);
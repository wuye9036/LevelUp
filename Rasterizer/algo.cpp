#include "stdafx.h"
#include "algo.h"

vector<int> points;

void draw_pixel(int x, int y, float z, float t)
{
	points.push_back(x);
	points.push_back(y);

	points.push_back(0);
	points.push_back(int(t*255));
	points.push_back(0);
}

void draw_pixel(int x, int y, float z, float u, float v)
{
	points.push_back(x);
	points.push_back(y);
	
	clamp(u, 0.0f, 1.0f);
	clamp(v, 0.0f, 1.0f);

	points.push_back(int(u*255));
	points.push_back(int(v*255));
	points.push_back(int((1-u-v)*255));
}

//线的光栅化,DDA算法
void rasterize_line(const vec4& start, const vec4& end)
{
	vec4 dir = end - start;
	
	dir.x = (float)floor(dir.x);
	dir.y = (float)floor(dir.y);
	
	int dx = (int)abs(dir.x);
	int dy = (int)abs(dir.y);

	if( dx > dy)
	{
		int sign = dir.x > 0? 1: -1;
		int sx = int((float)start.x);

		float dydx = dir.y / dx;
		float dzdx = dir.z / dx;
		float dtdx = 1.0f / dx;

		int cx = int(floor(start.x));
		float cy = floor(start.y);
		float cz = start.z;
		float ct = 0.0f;

		//x-axis major
		for(int i = 0; i < dx; ++i)
		{
			draw_pixel(cx + sign*i, int(cy), cz, ct);

			cy += dydx;
			cz += dzdx;
			ct += dtdx;
		}
	}
	else
	{
		int sign = dir.y > 0? 1: -1;
		int sy = int((float)start.y);

		float dxdy = dir.x / dy;
		float dzdy = dir.z / dy;
		float dtdy = 1.0f / dy;

		int cy = int(floor(start.y));

		float cx = floor(start.x);
		float cz = start.z;
		float ct = 0.0f;

		//x-axis major
		for(int i = 0; i < dy; ++i)
		{
			draw_pixel(int(cx), cy+sign*i, cz, ct);

			cx += dxdy;
			cz += dzdy;
			ct += dtdy;
		}
	}
}

//分割成上下两个三角形，重心坐标系参数方程p = u*v1 + v*v2 + (1-u-v)*v0
void rasterize_triangle(const vec4& v0, const vec4& v1, const vec4& v2)
{
	vec4 vert[3] = {v0, v1, v2};
	
	//升序排列
	if(vert[0].y > vert[1].y)
	{
		swap(vert[1], vert[0]);
	}
	if(vert[1].y > vert[2].y)
	{
		swap(vert[2], vert[1]);
		if(vert[0].y > vert[1].y) swap(vert[1], vert[0]);
	}

	vec4 e12 = vert[2] - vert[1];
	vec4 e02 = vert[2] - vert[0];
	vec4 e01 = vert[1] - vert[0];

	float area = cross_prod2(e12.xy(), e02.xy());
	if(equal<float>(area, 0.0f)) return;

	//求出u v的差分
	float dvdx = (vert[1].y - vert[0].y) / area;
	float dvdy = (vert[0].x - vert[1].x) / area;
	float dudx = (vert[0].y - vert[2].y) / area;
	float dudy = (vert[2].x - vert[0].x) / area;

	float dxdy_01 = equal<float>(e01.y, 0.0f) ? 0.0f: e01.x / e01.y;
	float dxdy_02 = equal<float>(e02.y, 0.0f) ? 0.0f: e02.x / e02.y;
	float dxdy_12 = equal<float>(e12.y, 0.0f) ? 0.0f: e12.x / e12.y;

	//绘制下多边形 vert[0] vert[1] v'
	if(!equal<float>(vert[0].y, vert[1].y))
	{
		float fsy = floor(vert[0].y + 0.5f);
		float fey = floor(vert[1].y + 0.5f);
		int isy = int(fsy);
		int iey = int(fey);

		float fcx_01 = vert[0].x + dxdy_01*(fsy +0.5f - vert[0].y);
		float fcx_02 = vert[0].x + dxdy_02*(fsy + 0.5f - vert[0].y);

		float u = dudy*(fsy + 0.5f - vert[0].y);
		float v = dvdy*(fsy +0.5f - vert[0].y);

		for(int iy = isy; iy < iey; ++iy)
		{
			float icx_s = (int)floor(fcx_01 +0.5f);
			float icx_e = (int)floor(fcx_02 +0.5f);

			if(fcx_01 > fcx_02) swap(icx_s, icx_e);

			float scanline_u = u + dudx*(float(icx_s) + 0.5f - vert[0].x);
			float scanline_v = v + dvdx*(float(icx_s) + 0.5f - vert[0].x);

			for(int ix = icx_s; ix < icx_e; ++ix)
			{
				draw_pixel(ix, iy, 0.0f, scanline_u, scanline_v);
				scanline_u += dudx;
				scanline_v += dvdx;
			}

			u += dudy;
			v += dvdy;
			fcx_01 += dxdy_01;
			fcx_02 += dxdy_02;
		}
	}

	//绘制上多边形
	if(!equal<float>(vert[1].y, vert[2].y))
	{
		float fsy = floor(vert[1].y + 0.5f);
		float fey = floor(vert[2].y + 0.5f);
		int isy = int(fsy);
		int iey = int(fey);

		float fcx_12 = vert[1].x + dxdy_12*(fsy +0.5f - vert[1].y);
		float fcx_02 = vert[0].x + dxdy_02*(fsy +0.5f - vert[0].y);

		float u = dudy*(fsy +0.5f - vert[0].y);
		float v = dvdy*(fsy +0.5f - vert[0].y);

		for(int iy = isy; iy < iey; ++iy)
		{
			float icx_s = (int)floor(fcx_12 +0.5f);
			float icx_e = (int)floor(fcx_02 +0.5f);

			if(fcx_12 > fcx_02) swap(icx_s, icx_e);

			float scanline_u = u + dudx*(float(icx_s) +0.5f - vert[0].x);
			float scanline_v = v + dvdx*(float(icx_s) +0.5f - vert[0].x);

			for(int ix = icx_s; ix < icx_e; ++ix)
			{
				draw_pixel(ix, iy, 0.0f, scanline_u, scanline_v);
				scanline_u += dudx;
				scanline_v += dvdx;
			}

			u += dudy;
			v += dvdy;
			fcx_12 += dxdy_12;
			fcx_02 += dxdy_02;
		}
	}
}

vector<int> draw_line(int sx, int sy, int ex, int ey)
{
	points.clear();

	vec4 start(sx, sy, 0.0f, 0.0f);
	vec4 end(ex, ey, 0.0f, 0.0f);

	rasterize_line(start, end);
	return points;
}

vector<int> draw_tri(int v0x, int v0y, int v1x, int v1y, int v2x, int v2y)
{
	points.clear();

	vec4 v0(v0x, v0y, 0.0f, 0.0f);
	vec4 v1(v1x, v1y, 0.0f, 0.0f);
	vec4 v2(v2x, v2y, 0.0f, 0.0f);

	rasterize_triangle(v0, v1, v2);

	return points;
}
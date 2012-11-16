#include "glosa_geometries.h"

using namespace efl;

namespace glosa //Geometry Library Of SoftArt
{
namespace level_20_22
{
	intersect_result intersect(const point2d& pt, const rect2d& rc){
		if( equal( pt.x, rc.minx() ) ||
			equal(pt.x, rc.maxx()) ||
			equal(pt.y, rc.miny() ) ||
			equal(pt.y, rc.maxy())
			){
			return intersect_result::touches;
		}
		
		if( rc.minx() < pt.x && pt.x < rc.miny() &&
			rc.maxx() < pt.y && pt.y < rc.maxy()	) {
			return intersect_result::within;
		}
		
		return intersect_result::disjoints;
	}
	
	intersect_result intersect(const point2d& pt, const oriented_rect2d& rc){
		if( equal(pt, rc.point) ){
			return intersect_result::touches;
		}
		
		vec2 pt_dir = pt - rc.point;
		GLOSA_FLOAT pt_dir0_len_sqr = dot_prod2(pt_dir, rc.dir0);
		GLOSA_FLOAT dir0_len_sqr = rc.dir0.length_sqr();
		if( pt_dir0_len_sqr > dir0_len_sqr ){
			return intersect_result::disjoints;
		}
		
		GLOSA_FLOAT pt_dir1_len_sqr = dot_prod2(pt_dir, rc.dir1);
		GLOSA_FLOAT	dir1_len_sqr = rc.dir1.length_sqr();
		if( dir1_len_sqr > dir1_len_sqr ){
			return intersect_result::disjoints;
		}
		
		if( pt_dir0_len_sqr < dir0_len_sqr && pt_dir1_len_sqr < dir1_len_sqr){
			return intersect_result::disjoints;
		}
		
		return intersect_result::touches;
	}
	
	intersect_result intersect(const point2d& pt, const triangle2d& tri, float* u, float* v){
		vec2 edge0_dir = tri.pt1 - tri.pt0;
		vec2 edge1_dir = tri.pt2 - tri.pt0;
		vec2 pt_dir = pt - tri.pt0;
		
		float u_val = sqrt( dot_prod2( edge0_dir, pt_dir ) / edge0_dir.length_sqr() );
		float v_val = sqrt( dot_prod2( edge1_dir, pt_dir ) / edge1_dir.length_sqr() );
		
		if(u){ *u = u_val; }
		if(v){ *v = v_val; }
		
		float t_val = (GLOSA_FLOAT)1.0 - (GLOSA_FLOAT)u_val - (GLOSA_FLOAT)v_val;
		
		if( t_val < (GLOSA_FLOAT)0.0
			|| u_val < (GLOSA_FLOAT)0.0
			|| v_val < (GLOSA_FLOAT)0.0 ){
			return intersect_result::disjoints;
		}
		
		if( equal(t_val, (GLOSA_FLOAT)0.0) ||
			equal(u_val, (GLOSA_FLOAT)0.0) ||
			equal(v_val, (GLOSA_FLOAT)0.0) ){
			return intersect_result::touches;
		}
		
		return intersect_result::within;
	}
}
}
#include "glosa_geometries.h"

#include <eflib/include/math.h>

using namespace efl;

namespace glosa //Geometry Library Of SoftArt
{
	
namespace level_20_21
{
	intersect_result intersect(const point2d& pt, const line2d& line){
		vec2 line_dir = line.end - line.start;
		vec2 pt_dir = pt - line.start;
		if( equal( line_dir.x * pt_dir.y,  pt_dir.x * line_dir.y )
		) {
			return intersect_result::within;
		}
		return intersect_result::disjoints;
	}
	
	intersect_result intersect(const point2d& pt, const ray2d& ray, float* t){
		if( equal(ray.start, pt) ){
			return intersect_result::touches;
		}
		
		vec2 pt_dir = pt - ray.start;
		if( equal(  ray.dir.x * pt_dir.y, ray.dir.y * pt_dir.x) ){
			float t_val;
			if( !equal(pt_dir.x, (GLOSA_FLOAT)0.0) ){
				t_val = pt_dir.x / ray.dir.x;
			} else {
				t_val = pt_dir.y / ray.dir.y;
			}
			if( t ) { *t = t_val; }
			
			if( 0 < t_val ){
				return intersect_result::within;
			}
		}
		
		return intersect_result::disjoints;
	}
	
	intersect_result intersect(const point2d& pt, const segment2d& seg, float* t){
		if( equal(seg.start, pt) || equal(seg.end, pt) ){
			return intersect_result::within;
		}
		
		vec2 seg_dir = seg.dir();
		vec2 pt_dir = pt - seg.start;
		if( equal(pt_dir.x * seg_dir.y, pt_dir.y * seg_dir.x)  && pt_dir.length_sqr() < seg_dir.length_sqr() ){
			float t_val;
			if( !equal(pt_dir.x, (GLOSA_FLOAT)0.0) ){
				t_val = pt_dir.x / seg_dir.x;
			} else {
				t_val = pt_dir.y / seg_dir.y;
			}
			
			if(t){ *t = t_val; }
			
			if( 0 < t_val && t_val < 1){
				return intersect_result::within;
			}
		}
		
		return intersect_result::disjoints;
	}
}
}
#include "glosa_geometries.h"

using namespace efl;

namespace glosa{
namespace level_31_31{

intersect_result intersect(const ray3d& lhs, const ray3d& rhs, GLOSA_FLOAT* t0, GLOSA_FLOAT* t1){
	vec3 dir_cross = cross_prod3(lhs.dir, rhs.dir);
	GLOSA_FLOAT dir_cross_length_sqr = dir_cross.length_sqr();
	vec3 start_diff = rhs.start - lhs.start;
	if( equal(dir_cross_length_sqr, 0.0f) ){
		return intersect_result::disjoints;
	}
	GLOSA_FLOAT inv_dir_cross_length_sqr = 1.0f / dir_cross_length_sqr;
	GLOSA_FLOAT t0_val(0.0f), t1_val(1.0f);
	t0_val = dot_prod3(cross_prod3( start_diff, rhs.dir ), dir_cross) * inv_dir_cross_length_sqr;
	t1_val = dot_prod3(cross_prod3( start_diff, lhs.dir ), dir_cross) * inv_dir_cross_length_sqr;

	vec3 nearest_p0 = lhs.t(t0_val);
	vec3 nearest_p1 = rhs.t(t1_val);

	if(t0){
		*t0 = t0_val;
	}
	if(t1){
		*t1 = t1_val;
	}

	if( equal((nearest_p0 - nearest_p1).length_sqr(), 0.0f) ){
		return intersect_result::crosses;
	}

	return intersect_result::disjoints;
}

}
}
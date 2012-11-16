#include "glosa_geometries.h"

#include <eflib/include/math.h>

using namespace efl;

namespace glosa //Geometry Library Of SoftArt
{
namespace level_30_33
{

intersect_result intersect(const point3d& pt, const AABB& box){
	if( box.is_in_box(pt) ){
		return intersect_result::within;
	}

	return intersect_result::disjoints;
}

intersect_result intersect(const point3d& pt, const OBB& box){
	vec4 transformed_position;
	transform( transformed_position, box.to_local_mat(), vec4(pt, 1.0f) );
	AABB transformed_box(box.local_AABB() );
	return intersect((point3d&)(transformed_position.xyz()), transformed_box);
}

}
}
#include "glosa_geometries.h"

using namespace efl;

namespace glosa{
namespace level_33_33{

intersect_result intersect(const AABB& lhs, const AABB& rhs){
	efl::vec3 dist = rhs.center() - lhs.center();
	efl::vec3 lr = lhs.r();
	efl::vec3 rr = rhs.r();

	if( abs(dist.x) < lr.x + rr.x ){
		return intersect_result::intersects;
	}

	if ( abs(dist.y) < lr.y + rr.y ){
		return intersect_result::intersects;
	}

	if ( abs(dist.z) < lr.z + rr.z ){
		return intersect_result::intersects;
	}

	return intersect_result::disjoints;
}

}
}

#define GLOSA_FLOAT float

namespace glosa{
	//geometries
	//0d
	struct point2d;
	struct point3d;
	
	//1d
	struct line2d;
	struct ray2d;
	struct segment2d;
	
	struct line3d;
	struct ray3d;
	struct segment3d;
	
	//2d 
	struct rect2d;
	struct oriented_rect2d;
	struct triangle2d;
	//struct sphere;
	
	struct triangle3d;
	struct plane;
	
	//3d
	class AABB;
	class OBB;
	struct BoundingSphere;
	
	//enumerations
	//within, contains, overlap, touch, cross, equal, disjoint, and intersects
	//	within: 
	//		The base geometry is within the comparison geometry if 
	//		the base geometry is the intersection of the geometries and the intersection of their interiors is not empty.  
	//		Within is a Clementini operator. 
	//		Within is the opposite operator of contains.
	//	contains: 
	//		The base geometry contains the comparison geometry (other) 
	//		if the comparison geometry is a subset of the base geometry and 
	//		the intersection of their interiors is not empty.
	//	overlaps: 
	//		the region of their intersection is of the same dimension as the geometries involved and is not equivalent to either of the geometries.
	//	touches:
	//		Two geometries are said to touch when the intersection of the geometries is non-empty, but the intersection of their interiors is empty. 
	//	disjoints:
	//		Two geometries are disjoint if their intersection is empty.  Two geometries intersect if disjoint is "false".  
	//	crosses: 
	//		Two polylines cross if they share only points in common, at least one of which is not an endpoint.  
	//		A polyline and an polygon cross if they share a polyline in common on the interior of the polygon which is not equivalent to the entire polyline. 
	//	intersects:
	//		probability of within, contains, overlaps, touches or crosses
	class intersect_result;

	//intersections
	// intersect method will return a verbose intersection information or briefly result which includes two results "intersects" and "disjoints".
	namespace level_20_21 { //2d points vs 2d lines
		intersect_result intersect(const point2d& pt, const line2d& line);
		intersect_result intersect(const point2d& pt, const ray2d& ray, float* t);
		intersect_result intersect(const point2d& pt, const segment2d& seg, float* t);
	}
	
	namespace level_20_22 { //2d points vs 2d faces
		intersect_result intersect(const point2d& pt, const rect2d& rc);
		intersect_result intersect(const point2d& pt, const oriented_rect2d& rc);
		intersect_result intersect(const point2d& pt, const triangle2d& tri, float* u, float* v);
	}
	
	namespace level_21_21 { //2d lines vs 2d lines
		intersect_result intersect(const line2d& lhs, const line2d& rhs, point2d* intersect_pt);
		intersect_result intersect(const line2d& line, const ray2d& ray, point2d* intersect_pt);
		intersect_result intersect(const line2d& line, const segment2d& seg, point2d* intersect_pt);
		
		intersect_result intersect(const ray2d& lhs, const ray2d& rhs, point2d* intersect_pt);
		intersect_result intersect(const ray2d& ray, const segment2d& seg, point2d* intersect_pt, GLOSA_FLOAT* t1, GLOSA_FLOAT* t2);
		
		intersect_result intersect(const segment2d& lhs, const segment2d& rhs, point2d* intersect_pt, GLOSA_FLOAT* t1, GLOSA_FLOAT* t2);
	}
	
	namespace level_21_22{ //2d lines vs 2d faces
		intersect_result intersect(const line2d& line, const rect2d& rect, point2d* pt1, point2d* pt2);
		intersect_result intersect(const line2d& line, const oriented_rect2d& rect, point2d* pt1, point2d* pt2);
		intersect_result intersect(const line2d& line, const triangle2d& tri, point2d* pt1, point2d* pt2);
		
		intersect_result intersect(const ray2d& ray, const rect2d& rect, point2d* pt1, point2d* pt2, int* n_intersection);
		intersect_result intersect(const ray2d& ray, const oriented_rect2d* rect, point2d* pt1, point2d* pt2, int* n_intersection);
		intersect_result intersect(const ray2d& ray, const triangle2d& tri, point2d* pt1, point2d* pt2, int* n_intersection);
		
		intersect_result intersect(const segment2d& seg, const rect2d& rect, point2d* pt1, point2d* pt2, int* n_intersection);
		intersect_result intersect(const segment2d& seg, const oriented_rect2d* rect, point2d* pt1, point2d* pt2, int* n_intersection);
		intersect_result intersect(const segment2d& seg, const triangle2d& tri, point2d* pt1, point2d* pt2, int* n_intersection);
	}
	
	namespace level_22_22{ // 2d face vs 2d faces
	}
	
	namespace level_30_31{ //3d points vs 3d lines
	}
	
	namespace level_30_32{ //3d points vs 3d faces
	}
	
	namespace level_30_33{ //3d points vs 3d volumes
		intersect_result intersect(const point3d& pt, const AABB& box);
		intersect_result intersect(const point3d& pt, const OBB& box);
	}
	
	namespace level_31_31{ //3d lines vs 3d lines
		intersect_result intersect(const ray3d& lhs, const ray3d& rhs, GLOSA_FLOAT* t0, GLOSA_FLOAT* t1);
	}
	
	namespace level_31_32{ //3d lines vs 3d faces
		intersect_result intersect(const line3d& line, const plane& pl, point3d* intersect_pt);
		intersect_result intersect(const line3d& line, const triangle3d& tri, GLOSA_FLOAT* u, GLOSA_FLOAT* v);
		
		intersect_result intersect(const ray3d& ray, const plane& pl, point3d* intersect_pt, GLOSA_FLOAT* t);
		intersect_result intersect(const ray3d& ray, const triangle3d& tri, GLOSA_FLOAT* u, GLOSA_FLOAT* v, GLOSA_FLOAT* t);
	}
	
	namespace level_31_33{ //3d lines vs 3d volume
		intersect_result intersect(const line2d& line, const AABB& box);
	}
	
	namespace level_32_32{ //3d faces vs 3d faces
	}
	
	namespace level_32_33{ //3d faces vs 3d volumes
	}
	
	namespace level_33_33{ //3d volumes vs 3d volumes
		intersect_result intersect(const AABB& lhs, const AABB& rhs);
		intersect_result intersect(const AABB& lhs, const OBB& rhs);
		intersect_result intersect(const AABB& lhs, const BoundingSphere& rhs);
	}
}
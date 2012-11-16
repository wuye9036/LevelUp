

#include <eflib/include/math.h>

#include "glosa.h"

#include <vector>

namespace glosa{

class intersect_result{
	intersect_result(uint32_t val);
	int32_t val;

	static intersect_result get_within();
	static intersect_result get_contains();
	static intersect_result get_overlaps();
	static intersect_result get_touches();
	static intersect_result get_crosses();
	static intersect_result get_intersects();

	static intersect_result get_disjoints();

public:
	intersect_result(const intersect_result& rhs);
	intersect_result& operator = (const intersect_result& rhs);
	bool operator == (const intersect_result& rhs);
	bool operator != (const intersect_result& rhs);

	static const intersect_result within;
	static const intersect_result contains;
	static const intersect_result overlaps;
	static const intersect_result touches;
	static const intersect_result crosses;

	static const intersect_result disjoints;
	static const intersect_result intersects;
};

//0d
struct point2d : public efl::vec2{
};

struct point3d : public efl::vec3{
};

//1d
struct line2d{
	efl::vec2 start;
	efl::vec2 end;
	
	line2d(const point2d& start, const point2d& end);

	line2d(const point2d& start, const efl::vec2& dir);
	line2d(const segment2d& seg);
	line2d(const ray2d& ray);
	
	//ax + by +c = 0
	line2d(GLOSA_FLOAT a, GLOSA_FLOAT b, GLOSA_FLOAT c);
	
	efl::vec2 dir() const;
	efl::vec2 norm_dir() const;
	
	GLOSA_FLOAT a() const;
	GLOSA_FLOAT	b() const;
	GLOSA_FLOAT c() const;

	efl::vec3 abc() const;
};

struct ray2d{
	efl::vec2 start;
	efl::vec2 dir;
	
	ray2d(const point2d& start, const efl::vec2& dir);
	ray2d(const point2d& start, const point2d& lookat);
	ray2d(const segment2d& seg);
	
	GLOSA_FLOAT	t(const efl::vec2& v) const; // v must on the line of ray.
	efl::vec2 t(GLOSA_FLOAT t_val) const;
};

struct segment2d{
	efl::vec2 start;
	efl::vec2 end;
	
	segment2d(const point2d& start, const point2d& end);
	segment2d(const point2d& start, const efl::vec2& dir);

	efl::vec2 dir() const;
	efl::vec2 norm_dir() const;
	
	GLOSA_FLOAT len_sqr() const;
	GLOSA_FLOAT len() const;
	
	GLOSA_FLOAT	t(const efl::vec2& v) const; // v must on the line of segment
	point2d t(GLOSA_FLOAT t_val) const;
};

struct line3d{
	efl::vec3 start;
	efl::vec3 end;

	line3d(const point3d& start, const point3d& end);
	line3d(const point3d& start, const efl::vec3& dir);
	line3d(const ray3d& ray);
	line3d(const segment3d& seg);

	efl::vec3 dir() const;
	efl::vec3 norm_dir() const;
	
	GLOSA_FLOAT len_sqr() const;
	GLOSA_FLOAT	len() const;
};

struct ray3d{
	efl::vec3 start;
	efl::vec3 dir;

	GLOSA_FLOAT t(const point3d& pt) const;
	efl::vec3 t(GLOSA_FLOAT t_val) const;
};

struct segment3d{
	efl::vec3 start;
	efl::vec3 end;
	
	efl::vec3 dir();
	efl::vec3 norm_dir();
	
	GLOSA_FLOAT len_sqr();
	GLOSA_FLOAT len();
};

//2d
struct rect2d{
	efl::vec2 point;
	efl::vec2 size;
	
	rect2d(GLOSA_FLOAT minx, GLOSA_FLOAT miny, GLOSA_FLOAT maxx, GLOSA_FLOAT maxy);
	rect2d(const point2d& pt, const efl::vec2& size);
	rect2d(const point2d& pt0, const point2d& pt1);

	GLOSA_FLOAT minx() const;
	GLOSA_FLOAT maxx() const;
	GLOSA_FLOAT miny() const;
	GLOSA_FLOAT maxy() const;
	
	GLOSA_FLOAT x() const;
	GLOSA_FLOAT y() const;
	GLOSA_FLOAT width() const;
	GLOSA_FLOAT	height() const;
	
	point2d center() const;
	efl::vec2 r() const;

	std::vector<segment2d> edges() const;
	segment2d edge(int edge_idx) const;

	//union
	rect2d operator + (const rect2d& rhs) const;
	rect2d& operator += (const rect2d& rhs);

	rect2d& union_point(const point2d& pt);

	template<class PointIterator>
	rect2d& union_points(PointIterator begin, PointIterator end){
		for(PointIterator it = begin; it != end; ++it){
			this->union_point(*it);
		}
		return *this;
	}

	template<class PointIterator>
	rect2d& union_points(PointIterator begin, size_t count){
		for(PointIterator it = begin, int n = 0; n < count; ++it, ++n){
			this->union_point(*it);
		}
		return *this;
	}

	//overlap
	rect2d operator & (const rect2d& rhs) const;
	rect2d& operator &= (const rect2d& rhs);
};


struct oriented_rect2d{
	efl::vec2 point;
	efl::vec2 dir0;
	efl::vec2 dir1;
};

struct triangle2d{
	efl::vec2 pt0, pt1, pt2;

	efl::vec2 uv(const point2d& pt);
	point2d uv(GLOSA_FLOAT u, GLOSA_FLOAT v);
};

struct plane{
	efl::vec3 base_point, norm;

	plane(const point3d& pt_on_plane, const efl::vec3& nor);
	plane(const point3d& pt0, const point3d& pt1, const point3d& pt2);
};
//3d
class AABB
{
	point3d min_pt, max_pt;

public:
	AABB(const point3d& minpt, const point3d& maxpt);
	AABB(const point3d& center, const efl::vec3& r);

	point3d center() const;
	efl::vec3 r() const;

	point3d min() const;
	point3d max() const;

	AABB& union_point(const point3d& pt);

	template<class PointIterator>
	AABB& union_points(PointIterator begin, PointIterator end){
		for(PointIterator it = begin; it != end; ++it){
			this->union_point(*it);
		}
		return *this;
	}

	template<class PointIterator>
	AABB& union_points(PointIterator begin, size_t count){
		for(PointIterator it = begin, int n = 0; n < count; ++it, ++n){
			this->union_point(*it);
		}
		return *this;
	}

	
	bool is_in_box(const point3d& pt) const;
};


class OBB{
	efl::vec3 basises_[3];
	efl::vec3 r_;
	efl::vec3 center_;
public:
	OBB(const efl::vec3& c, const efl::vec3& r, const efl::vec3* basises);
	OBB(const efl::vec3& size, const efl::mat44& transform_mat);

	const efl::vec3* basises() const;
	efl::vec3 r() const;
	efl::vec3 center() const;

	//返回将坐标从全局坐标转换为OBB本地坐标的变换矩阵
	efl::mat44 to_local_mat() const;
	AABB local_AABB() const;
};

}
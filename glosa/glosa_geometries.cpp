#include "glosa_geometries.h"

#include <vector>

using namespace std;
using namespace efl;

namespace glosa{

intersect_result::intersect_result(uint32_t val): val(val){
}

intersect_result::intersect_result(const intersect_result& rhs):val(rhs.val){}
intersect_result& intersect_result::operator =(const intersect_result& rhs){
	val = rhs.val;
	return *this;
}

intersect_result intersect_result::get_within(){
	return intersect_result(0x01);
}
intersect_result intersect_result::get_contains(){
	return intersect_result(0x02);
}
intersect_result intersect_result::get_overlaps(){
	return intersect_result(0x04);
}
intersect_result intersect_result::get_touches(){
	return intersect_result(0x08);
}
intersect_result intersect_result::get_crosses(){
	return intersect_result(0x10);
}
intersect_result intersect_result::get_intersects(){
	return intersect_result(0xFFFFFFFF);
}

intersect_result intersect_result::get_disjoints(){
	return intersect_result(0);
}

bool intersect_result::operator==( const intersect_result& rhs )
{
	return val == rhs.val;
}

bool intersect_result::operator!=( const intersect_result& rhs )
{
	return val != rhs.val;
}

const intersect_result intersect_result::within(intersect_result::get_within());
const intersect_result intersect_result::contains(intersect_result::get_contains());
const intersect_result intersect_result::overlaps(intersect_result::get_overlaps());
const intersect_result intersect_result::touches(intersect_result::get_touches());
const intersect_result intersect_result::crosses(intersect_result::get_crosses());

const intersect_result intersect_result::disjoints(intersect_result::get_disjoints());
const intersect_result intersect_result::intersects(intersect_result::get_intersects());

//line2d
line2d::line2d(const point2d& start, const point2d& end):start(start), end(end){
}

line2d::line2d(const point2d& start, const vec2& dir): start(start), end(start+dir){
}

line2d::line2d(const segment2d& seg):start(seg.start), end(seg.end){
}

line2d::line2d(const ray2d& ray):start(ray.start), end(ray.dir + ray.start){
}

line2d::line2d(GLOSA_FLOAT a, GLOSA_FLOAT b, GLOSA_FLOAT c){
	if( equal(a, GLOSA_FLOAT(0)) ){
		GLOSA_FLOAT x_axis = -c / b;
		start = vec2(GLOSA_FLOAT(0), x_axis);
		end = vec2(GLOSA_FLOAT(1), x_axis);
	}

	if( equal(b, GLOSA_FLOAT(0)) ){
		GLOSA_FLOAT y_axis = -c / a;
		start = vec2(y_axis, GLOSA_FLOAT(0));
		end = vec2(y_axis, GLOSA_FLOAT(1));
	}

	GLOSA_FLOAT	x_begin = GLOSA_FLOAT(0);
	GLOSA_FLOAT y_begin = -c / b;
	GLOSA_FLOAT x_end = -c / a;
	GLOSA_FLOAT y_end = GLOSA_FLOAT(1);

	start = vec2(x_begin, y_begin);
	end = vec2(x_end, y_end);
}

vec2 line2d::dir() const{
	return end - start;
}

vec2 line2d::norm_dir() const{
	return normalize2(end - start);
}

GLOSA_FLOAT line2d::a() const{
	if( equal(end.x, start.x) ){
		return GLOSA_FLOAT(1);
	}

	return dir().y / dir().x;
}

GLOSA_FLOAT	line2d::b() const{
	if( equal(end.x, start.x) ){
		return GLOSA_FLOAT(0);
	}

	return GLOSA_FLOAT(-1);
}

GLOSA_FLOAT line2d::c() const{
	return  -b() * start.y - a()*start.x;
}

vec3 line2d::abc() const{
	return vec3(a(), b(), c());
}


//ray2d
ray2d::ray2d( const point2d& start, const vec2& dir ):start(start), dir(dir)
{
}

ray2d::ray2d( const point2d& start, const point2d& lookat ):start(start), dir(lookat-start)
{
}

ray2d::ray2d( const segment2d& seg ):start(start), dir(seg.end - seg.start)
{
}

GLOSA_FLOAT ray2d::t( const vec2& v ) const
{
	if( equal(dir.x, GLOSA_FLOAT(0)) ){
		return v.y / dir.y;
	}
	return v.x / dir.x;
}

vec2 ray2d::t( GLOSA_FLOAT t_val ) const
{
	return start + dir * t_val;
}

//segment2d
segment2d::segment2d( const point2d& start, const point2d& end ):start(start), end(end)
{
}

segment2d::segment2d( const point2d& start, const vec2& dir ): start(start), end(start + dir)
{	
}


vec2 segment2d::dir() const
{
	return end-start;
}

vec2 segment2d::norm_dir() const
{
	return normalize2(dir());
}

GLOSA_FLOAT segment2d::len_sqr() const
{
	return dir().length_sqr();
}

GLOSA_FLOAT segment2d::len() const
{
	return dir().length();
}

GLOSA_FLOAT segment2d::t( const vec2& v ) const
{
	if( equal(dir().x, GLOSA_FLOAT(0)) ){
		return v.y / dir().y;
	}

	return v.x / dir().x;
}

glosa::point2d segment2d::t( GLOSA_FLOAT t_val ) const
{
	return (point2d&)(start + dir() * t_val);
}

//line3d
line3d::line3d( const point3d& start, const point3d& end ):start(start), end(end)
{
}

line3d::line3d( const point3d& start, const vec3& dir ):start(start), end(start+dir)
{

}

line3d::line3d( const ray3d& ray ):start(ray.start), end(ray.dir+ray.start)
{
}

line3d::line3d( const segment3d& seg ): start(seg.start), end(seg.end)
{
}

vec3 line3d::dir() const
{
	return end-start;
}

vec3 line3d::norm_dir() const
{
	return normalize3(dir());
}

GLOSA_FLOAT line3d::len_sqr() const
{
	return dir().length_sqr();
}

GLOSA_FLOAT line3d::len() const
{
	return dir().length();
}

//rect2d
rect2d::rect2d( GLOSA_FLOAT minx, GLOSA_FLOAT miny, GLOSA_FLOAT maxx, GLOSA_FLOAT maxy ):point(minx, miny), size(maxx-minx, maxy-miny)
{
}

rect2d::rect2d(const glosa::point2d &pt, const vec2 &size):point(pt), size(size)
{
}
rect2d::rect2d(const point2d& pt0, const point2d& pt1):point(pt0), size(pt1.x-pt0.x, pt1.y-pt0.y){
}

vector<segment2d> rect2d::edges() const
{
	vector<segment2d> retSegs(4, segment2d(point2d(), vec2()));

	retSegs[0] = segment2d( (point2d&)vec2(minx(), miny()), (point2d&)vec2(minx(), maxy()) );
	retSegs[1] = segment2d( (point2d&)vec2(minx(), maxy()), (point2d&)vec2(maxx(), maxy()) );
	retSegs[2] = segment2d( (point2d&)vec2(maxx(), maxy()), (point2d&)vec2(maxx(), miny()) );
	retSegs[3] = segment2d( (point2d&)vec2(maxx(), miny()), (point2d&)vec2(minx(), miny()) );

	return retSegs;
}

segment2d rect2d::edge(int edge_idx) const{
	return edges()[edge_idx];
}

GLOSA_FLOAT rect2d::minx() const
{
	return point.x;
}

GLOSA_FLOAT rect2d::maxx() const
{
	return point.x + size.x;
}

GLOSA_FLOAT rect2d::miny() const
{
	return point.y;
}

GLOSA_FLOAT rect2d::maxy() const
{
	return point.y + size.y;
}

GLOSA_FLOAT rect2d::x() const
{
	return point.x;
}

GLOSA_FLOAT rect2d::y() const
{
	return point.y;
}

GLOSA_FLOAT rect2d::width() const
{
	return size.x;
}

GLOSA_FLOAT rect2d::height() const
{
	return size.y;
}

rect2d rect2d::operator+( const rect2d& rhs ) const
{
	return rect2d(
			min( minx(), rhs.minx() ),
			min( miny(), rhs.miny() ),
			max( maxx(), rhs.maxy() ),
			max( maxy(), rhs.maxy() )
		);
}

rect2d& rect2d::operator+=( const rect2d& rhs )
{
	return *this = *this + rhs;
}

rect2d rect2d::operator&( const rect2d& rhs ) const
{
	return rect2d(
		max( minx(), rhs.minx() ),
		max( miny(), rhs.miny() ),
		min( maxx(), rhs.maxy() ),
		min( maxy(), rhs.maxy() )
		);
}

rect2d& rect2d::operator&=( const rect2d& rhs )
{
	return *this = *this & rhs;
}

glosa::point2d rect2d::center() const
{
	return (point2d&)(point + r());
}

vec2 rect2d::r() const
{
	return size / GLOSA_FLOAT(2.0);
}

rect2d& rect2d::union_point( const point2d& pt )
{
	return *this += rect2d(pt, vec2());
}

//AABB
AABB::AABB( const point3d& minpt, const point3d& maxpt ): min_pt(minpt), max_pt(maxpt){
}

AABB::AABB( const point3d& center, const vec3& r ): min_pt((point3d&)(center - r / 2.0f)), max_pt((point3d&)(center + r / 2.0f)){
}

glosa::point3d AABB::center() const
{
	return (point3d&)(( min_pt + max_pt ) / GLOSA_FLOAT(2.0));
}

vec3 AABB::r() const
{
	return (point3d&)(( max_pt - min_pt ) / 2);
}

AABB& AABB::union_point( const point3d& pt )
{
	min_pt.x = std::min( min_pt.x, pt.x );
	min_pt.y = std::min( min_pt.y, pt.y );
	min_pt.z = std::min( min_pt.z, pt.z );

	max_pt.x = std::max( max_pt.x, pt.x );
	max_pt.y = std::max( max_pt.y, pt.y );
	max_pt.z = std::max( max_pt.z, pt.z );

	return *this;
}

glosa::point3d AABB::min() const
{
	return min_pt;
}

glosa::point3d AABB::max() const
{
	return max_pt;
}

bool AABB::is_in_box( const point3d& pt ) const
{
	return
		min_pt.x < pt.x && pt.x < max_pt.x &&
		min_pt.y < pt.y && pt.y < max_pt.y &&
		min_pt.z < pt.z && pt.z < max_pt.z;
}

OBB::OBB(const vec3& c, const vec3& r, const vec3* basises):center_(c), r_(r) {
	memcpy( &(this->basises_[0]), basises_, sizeof(vec3)*3 );
}

OBB::OBB( const vec3& size, const mat44& transform_mat ):r_(size)
{
	//top-left 3x3 is rotate components.
	basises_[0] = vec4(transform_mat.f[0], 3).xyz();
	basises_[1] = vec4(transform_mat.f[1], 3).xyz();
	basises_[2] = vec4(transform_mat.f[2], 3).xyz();

	//right column is transfer components.
	center_ = transform_mat.get_column(3).xyz();
}

const vec3* OBB::basises() const{
	return basises_;
}

vec3 OBB::r() const{
	return r_;
}

vec3 OBB::center() const{
	return center_;
}

efl::mat44 OBB::to_local_mat() const
{
	mat44 translate_mat;
	mat_translate(translate_mat, -center_.x, -center_.x, -center_.z);
	mat44 rotate_mat = mat44(
		vec4( basises_[0], 0.0f ),
		vec4( basises_[1], 0.0f ),
		vec4( basises_[2], 0.0f ),
		vec4( 0.0f, 0.0f, 0.0f, 1.0f)
		);
	mat44 ret_mat;
	return mat_mul(ret_mat, rotate_mat, translate_mat);
}

glosa::AABB OBB::local_AABB() const
{
	return glosa::AABB((point3d&)center_, r_);
}


GLOSA_FLOAT ray3d::t( const point3d& pt ) const
{
	return 0.0f;
}

efl::vec3 ray3d::t( GLOSA_FLOAT t_val ) const
{
	return start + dir * t_val;
}

}
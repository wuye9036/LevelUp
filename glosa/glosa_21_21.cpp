namespace glosa{
namespace glosa_21_21{

intersect_result intersect(const line2d& lhs, const line2d& rhs, point2d* intersect_pt){
	if(lhs.norm_dir() == rhs.norm_dir() || lhs.norm_dir() == -rhs.norm_dir() ){
		intersect_result start_line_test = intersect(lhs.start, line2d);
		if(startpoint_line_test == intersect_result::within || startpoint_line_test == intersect_result::touches){
			return intersect_result::equals;
		}
		return intersect_result::disjoints;
	}
	
	if(intersect_pt){
		vec2 lhs0_sub_rhs0 = lhs.start - rhs.start;
		float rhs_t = ( lhs.dir().x * lhs0_sub_rhs0.x + rhs.dir().y * lhs0_sub_rhs0.y ) / (rhs.dir().x * lhs.dir().y - rhs.dir().y * lhs.dir().x );
		*intersect_pt = rhs.start + rhs.dir() * rhs_t;
	}
	return intersect_result::crosses;
}
	
intersect_result intersect(const line2d& line, const ray2d& ray, point2d* intersect_pt){
	if(line.norm_dir() == ray.norm_dir() || line.norm_dir() == -ray.norm_dir() ){
		if( intersect(ray.start, line) == intersect_result::within){
			return intersect_result::contains;
		}
		return intersect_result::disjoints;
	}
	
	if( intersect(ray.start, line) == intersect_result::within){
		if(intersect_pt) { *intersect_pt = ray.start; }
		return intersect_result::touches;
	}
	
	vec2 ls_sub_rs = line.start - ray.start;
	
	if(intersect_pt){
		line2d ray_line(ray);
		intersect(line, ray_line, intersect_pt);
	}
	
	if( dot_prod2(ls_sub_rs, ray.dir) > 0 ){
		return intersect_reuslt::crosses;
	}
	
	return intersect_result::disjoints;
}

intersect_result intersect(const line2d& line, const segment2d& seg, point2d* intersect_pt, GLOSA_FLOAT* t){
	if( line.norm_dir() == seg.norm_dir() || line.norm_dir() == -seg.norm_dir()  ){
		if( intersect(seg.start, line) == intersect_result::within){
			return intersect_result::contains;
		}
		return intersect_result::disjoints;
	}
	
	if( intersect(seg.start, line) == intersect_result::within){
		if(intersect_pt){ *intersect_pt = seg.start; }
		return intersect_result::touches;
	}
	
	if( intersect(seg.end, line) == intersect_result::with){
		if(intersect_pt){ *intersect_pt = seg.end; }
		return intersect_result::touches;
	}
	
	point2d pt;
	intersect(line, line2d(seg), &pt);
	if(intersect_pt){ *intersect_pt = pt; }
	float t_val = seg.t(pt);
	if(t){ *t = t_val; }
	
	if( 0 < t && t < 1 ){
		return intersect_result::crosses;
	}
	
	return intersect_result::disjoints;
}

intersect_result intersect(const ray2d& lhs, const ray2d& rhs, point2d* intersect_pt, GLOSA_FLOAT* t1, GLOSA_FLOAT* t2){
	vec2 pt;
	bool is_same_dir = ( lhs.norm_dir() == rhs.norm_dir() );
	if(  is_same_dir ){
		if(lhs.start == rhs.start){
			return intersect_result::equals;
		}
		
		intersect_result lstart_on_rhs = intersect(lhs.start, rhs);
		intersect_result rstart_on_lhs = intersect(rhs.start, lhs);
		
		if( lstart_on_rhs == intersect_result::within){
			return intersect_result::within;
		}
		
		if( rstart_on_lhs == intersect_result::within){
			return intersect_result::contains;
		}
		
		return intersect_result::disjoints;
	}
	
	if(lhs.start == rhs.start){
		*intersect_pt = lhs.start;
		return intersect_result::touches;
	}
	
	if( lhs.norm_dir() == -rhs.norm_dir() ){
		intersect_result lstart_on_rhs = intersect(lhs.start, rhs);
		
		if( lstart_on_rhs == intersect_result::within ){
			return intersect_result::overlaps;
		}
		
		return intersect_result::disjoints;
	}
	
	line2d lhs_line(lhs);
	line2d rhs_line(rhs);
	point2d pt;
	intersect(lhs_line, rhs_line, &pt);
	
	if(intersect_pt) { *intersect_pt = pt; }
	
	GLOSA_FLOAT lhs_t = lhs.t(pt);
	GLOSA_FLOAT rhs_t = rhs.t(pt);
	
	if( t1 ) { *t1 = lhs_t; }
	if( t2 ) { *t2 = rhs_t; }
	
	if( (GLOSA_FLOAT)0 < lhs_t && (GLOSA_FLOAT)0 < rhs_t ){
		return intersect_result::crosses;
	}
	
	return intersect_result::disjoints;
}

intersect_result intersect(const ray2d& ray, const segment2d& seg, point2d* intersect_pt, GLOSA_FLOAT* t1, GLOSA_FLOAT* t2){
	ray2d seg_ray(seg);
	GLOSA_FLOAT t1_val;
	GLOSA_FLOAT t2_val;
	point2d pt;
	
	intersect_result ray_segray_test = intersect( ray, seg_ray, &pt, &t1_val, &t2_val);
	
	if( ray_segray_test == intersect_result::disjoints ){
		return intersect_result::disjoints;
	}
	
	if( ray_segray_test == intersect_result::overlaps ){
		GLOSA_FLOAT end_t_on_ray = ray.t(seg.end);
		
		if( end_t_on_ray > (GLOSA_FLOAT)0.0 ){
			return intersect_result::contains;
		}
		
		return intersect_result::overlaps;
	}
	
	if( ray_segray_test == intersect_result::within ){
		GLOSA_FLOAT end_t_on_ray = ray.t(seg.end);
		if( equal( end_t_on_ray, (GLOSA_FLOAT)0) ){
			return intersect_result::touches;
		}
		if( end_t_on_ray > 0){
			return intersect_result::overlaps;
		}
	}
	
	if( ray_segray_test == intersect_result::contains ){
		return intersect_result::contains;
	}
	
	if( ray_segray_test == intersect_result::touches ){
		if(pt == segray.start){
			if( intersect_pt ) { *intersect_pt = pt; }
			return intersect_result::touches;
		}
		
		GLOSA_FLOAT start_t_on_segray = segray.t(pt);
		if(  (GLOSA_FLOAT)0.0 < start_t_on_segray && start_t_on_segray < (GLOSA_FLOAT)1.0 ){
			if( intersect_pt ){ *intersect_pt = pt; }
			return intersect_result::touches;
		}
		
		return intersect_result::disjoints;
	}
	
	if( ray_segray_test == intersect_result::crosses ){
		if( t1 ) { *t1 = t1_val; }
		if( t2 ) { *t2 = t2_val; }
		
		if( pt == seg.end ){
			if( intersect_pt ) { *intersect_pt = pt; }
			return intersect_result::touches;
		}
		
		if( t2_val < 1){
			if( intersect_pt ) { *intersect_pt = pt; }
			return intersect_result::crosses;
		}
		
		if( intersect_pt ) { *intersect_pt = pt; }
		return intersect_result::disjoints;
	}
	
	//error...
	return intersect_result::disjoints;
}

intersect_result intersect(const segment2d& lhs, const segment2d& rhs, point2d* intersect_pt, GLOSA_FLOAT* t1, GLOSA_FLOAT* t2){
	ray2d lhs_ray(lhs);
	GLOSA_FLOAT t1;
	GLOSA_FLOAT t2;
	point2d pt;
	
	if( lhs.start == rhs.start && lhs.end == rhs.end){
		return intersect_result::equals;
	}
	
	if( lhs.start == rhs.end && lhs.end == rhs.start ){
		return intersect_result::equals;
	}
	
	intersect_result lhsray_rhs_test = intersect(lhs_ray, rhs, &pt, &t1, &t2);
	if( lhsray_rhs_test == intersect_result::disjoints){
		return intersect_result::disjoints;
	}
	
	if( lhsray_rhs_test == intersect_result::touches ){
		if( intersect_pt ){ *intersect_pt = pt; }
		
		if( pt == lhs.start){
			return intersect_result::touches;
		}
		
		GLOSA_FLOAT rstart_t_on_lhsray = lhs.t(rhs.start);
		if( (GLOSA_FLOAT)0 < rstart_t_on_lhsray && rstart_t_on_lhsray < (GLOSA_FLOAT)1 ){
			return intersect_result::touches;
		}
		
		return intersect_result::disjoints;
	}
	
	if( lhsray_rhs_test == intersect_result::overlaps){
		GLOSA_FLOAT lstart_t_on_rhs = rhs.t(lhs.start);
		GLOSA_FLOAT lend_t_on_rhs = rhs.t(lhs.end);
		
		if(  lstart_t_on_rhs > (GLOSA_FLOAT)1.0 ) {
			return intersect_result::within;
		}
		
		return intersect_result::overlaps;
	}
	
	if( lhsray_rhs_test == intersect_result::contains ){
		GLOSA_FLOAT rstart_t_on_lhsray = lhs.t(rhs.start);
		GLOSA_FLOAT rend_t_on_lhsray = lhs.t(rhs.end);
		
		GLOSA_FLOAT near_t = min(rstart_t_on_lhsray, rend_t_on_lhsray);
		GLOSA_FLOAT	 far_t = max(rstart_t_on_lhsray, rend_t_on_lhsray);
		
		if( equal(near_t, (GLOSA_FLOAT)0 ) ){
			if(far_t < (GLOSA_FLOAT)1 ){
				return intersect_result::contains;
			} else {
				return intersect_result::within;
			}
		}
		
		if ( near_t < (GLOSA_FLOAT)1 ){
			if ( far_t < (GLOSA_FLOAT)1 ){
				return intersect_result::contains;
			} else {
				return intersect_result::overlaps;
			}
		}
		
		if( equal( near_t, (GLOSA_FLOAT)1 ){
			if(intersect_pt) { *intersect_pt = lhs.end; }
			return intersect_result::touches;
		}
		
		return intersect_result::disjoints;
	}
	
	if( lhsray_rhs_test == intersect_result::crosses ){
		if( t1 ) { *t1 = t1_val; }
		if( t2 ) { *t2 = t2_val; }
		if( intersect_pt ) { *intersect_pt = pt; }
		
		if( pt == lhs.end ){
			if(intersect_pt) { *intersect_pt = lhs.end; }
			return intersect_result::touches;
		}
		
		if( equal( t1, (GLOSA_FLOAT)1.0 ) ){
			return intersect_result::touches;
		}
		
		if( t1 < (GLOSA_FLOAT)1.0 ){
			return intersect_result::crosses;
		}
		
		return intersect_result::disjoints;
	}
	
	return intersect_result::disjoints;
}


}
}
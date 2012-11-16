namespace glosa{
namespace level_21_22{

intersect_result intersect(const line2d& line, const rect2d& rect, point2d* pt1, point2d* pt2, int* n_intersection){
	vector<point2d> pts;
	pts.reserve(2);
	
	//计算直线和矩形四边的交点数
	for(int i = 0; i < 4; ++i){
		point2d line_edge_pt;
		intersect_result line_edge_test = intersect( line, rect.edge(i), &line_edge_pt );
		
		//如果直线和某边共线则返回Touches
		if(line_edge_test == intersect_result::contains){
			if( n_intersection ) { *n_intersection = 2; }
			if( *pt1 ) { *pt1 = edge.start; }
			if( *pt2 ) { *pt2 = edge.end; }
			return intersect_result::touches;
		}
		
		//如果直接经过线段的端点，则可能产生一个交点，或者无交点。
		if(line_edge_test == intersect_result::touches){
			pts.push_back(line_edge_pt);
			for(int j = 0; j < pts.size() - 1; ++j){
				if(pts[j] == line_edge_pt){
					pts.pop_back();
					break;
				}
			}
		}
		
		//如果直线穿过某条线段，那么会产生一个交点
		if( line_edge_test == intersection_result::crosses){
			pts.push_back(line_edge_pt);
		}
	}
	
	//根据交点数返回相交信息
	if( n_intersection ) { *n_intersection = 0; }
	
	if( pts.size() == 0){
		return intersect_result::disjoints;
	}
	
	if(pts.size() == 1){
		if( pt1 ) {* pt1 = pts[0];}
		return intersect_result::touches;
	}
	
	if( pt1 ) { *pt1 = pts[0]; }
	if( pt2 ) { *pt2 = pts[1]; }
	return intersect_result::crosses;
}

intersect_result intersect(const line2d& line, const oriented_rect2d& rect, point2d* pt1, point2d* pt2, int* n_intersection){
	vector<point2d> pts;
	pts.reserve(2);
	
	//计算直线和矩形四边的交点数
	for(int i = 0; i < 4; ++i){
		point2d line_edge_pt;
		intersect_result line_edge_test = intersect( line, rect.edge(i), &line_edge_pt );
		
		//如果直线和某边共线则返回Touches
		if(line_edge_test == intersect_result::contains){
			if( n_intersection ) { *n_intersection = 2; }
			if( *pt1 ) { *pt1 = edge.start; }
			if( *pt2 ) { *pt2 = edge.end; }
			return intersect_result::touches;
		}
		
		//如果直接经过线段的端点，则可能产生一个交点，或者无交点。
		if(line_edge_test == intersect_result::touches){
			pts.push_back(line_edge_pt);
			for(int j = 0; j < pts.size() - 1; ++j){
				if(pts[j] == line_edge_pt){
					pts.pop_back();
					break;
				}
			}
		}
		
		//如果直线穿过某条线段，那么会产生一个交点
		if( line_edge_test == intersection_result::crosses){
			pts.push_back(line_edge_pt);
		}
	}
	
	//根据交点数返回相交信息
	if( n_intersection ) { *n_intersection = 0; }
	
	if( pts.size() == 0){
		return intersect_result::disjoints;
	}
	
	if(pts.size() == 1){
		if( pt1 ) {* pt1 = pts[0];}
		return intersect_result::touches;
	}
	
	if( pt1 ) { *pt1 = pts[0]; }
	if( pt2 ) { *pt2 = pts[1]; }
	return intersect_result::crosses;
}

intersect_result intersect(const line2d& line, const triangle2d& tri, point2d* pt1, point2d* pt2, int* n_intersection){
	vector<point2d> pts;
	pts.reserve(2);
	
	//计算直线和边框的交点数
	for(int i = 0; i < 3; ++i){
		point2d line_edge_pt;
		intersect_result line_edge_test = intersect( line, tri.edge(i), &line_edge_pt );
		
		//如果直线和某边共线则返回Touches
		if(line_edge_test == intersect_result::contains){
			if( n_intersection ) { *n_intersection = 2; }
			if( *pt1 ) { *pt1 = edge.start; }
			if( *pt2 ) { *pt2 = edge.end; }
			return intersect_result::touches;
		}
		
		//如果直接经过线段的端点，则可能产生一个交点，或者无交点。
		if(line_edge_test == intersect_result::touches){
			pts.push_back(line_edge_pt);
			for(int j = 0; j < pts.size() - 1; ++j){
				if(pts[j] == line_edge_pt){
					pts.pop_back();
					break;
				}
			}
		}
		
		//如果直线穿过某条线段，那么会产生一个交点
		if( line_edge_test == intersection_result::crosses){
			pts.push_back(line_edge_pt);
		}
	}
	
	//根据交点数返回相交信息
	if( n_intersection ) { *n_intersection = 0; }
	
	if( pts.size() == 0){
		return intersect_result::disjoints;
	}
	
	if(pts.size() == 1){
		if( pt1 ) {* pt1 = pts[0];}
		return intersect_result::touches;
	}
	
	if( pt1 ) { *pt1 = pts[0]; }
	if( pt2 ) { *pt2 = pts[1]; }
	return intersect_result::crosses;
}

intersect_result intersect(const ray2d& ray, const rect2d& rect, point2d* pt1, point2d* pt2, int* n_intersection){
	line2d ray_line(ray);
	point2d pts[2];
	int intersection_count;
	
	//直线-矩形测试
	intersect_result rayline_rect_test = intersect( line, rect, &pts[0], &pts[1], &intersection_count);
	
	//如果直线矩形不相交则射线也不相交。
	if( rayline_rect_test == intersect_result::disjoints ){
		if( n_intersection ) { *n_intersection == 0; }
		return intersect_result::disjoints;
	}
	
	//如果直线与矩形相接
	if( rayline_rect_test == intersect_result::touches ){
		
		//一个交点的时候
		if( intersect_count == 1 ){
			if( ray.t(pts[0]) >= (GLOSA_FLOAT)0 ){
				if( pt1 ) { *pt1 = pts[0]; }
				if( n_intersection ) { *n_intersection = 1; }
				return intersect_result::touches;
			}
			
			if( n_intersection ) { *n_intersection = 0; }
			return intersect_result::disjoints;
		}
		
		//两个交点的时候
		GLOSA_FLOAT	 t_pt0_on_ray = ray.t(pts[0]);
		GLOSA_FLOAT	 t_pt1_on_ray = ray.t(pts[1]);
		GLOSA_FLOAT	min_t = min(t_pt0_on_ray, t_pt1_on_ray);
		GLOSA_FLOAT max_t = max(t_pt0_on_ray, t_pt1_on_ray);
		
		if( equal( max_t , (GLOSA_FLOAT)0.0 ){
			if( n_intersection ) { *n_intersection = 0; }
			if( pt1 ) {*pt1 = ray.start; }
			return intersect_result::touches;
		}
		
		if( max_t < 0 ){
			if( n_intersection ) { *n_intersection = 0; }
			return intersect_result::disjoints;
		}
		
		//max_t > 0
		if( n_intersection ) { *n_intersection = 2; }
		if(min_t > 0){
			if( pt1 ) { *pt1 = pts[0]; }
			if( pt2 ) { *pt2 = pts[1]; }
		} else {
			//max_t > 0 && min_t <= 0
			if( pt1 ) { *pt1 = pts[t_pt0_on_ray > 0 ? 0 : 1]; }
			if( pt2 ) { *pt2 = ray.start; }
		}
		return intersect_result::touches;
	}
	
	if( rayline_rect_test == intersect_result::crosses){
		if( intersect_count == 1 ){
			if( pts[0] == ray.start ){
				if( pt1 ) { *pt1 = pts[0]; }
				if( n_intersection ) { *n_intersection = 1; }
				return intersect_result::touches;
			}
			if( ray.t(pts[0]) = (GLOSA_FLOAT)0 ){
				if( pt1 ) { *pt1 = pts[0]; }
				if( n_intersection ) { *n_intersection = 1; }
				return intersect_result::crosses;
			}
			
			if( n_intersection ) { *n_intersection = 0; }
			return intersect_result::disjoints;
		}
	
		GLOSA_FLOAT	 t_pt0_on_ray = ray.t(pts[0]);
		GLOSA_FLOAT	 t_pt1_on_ray = ray.t(pts[1]);
		GLOSA_FLOAT	min_t = min(t_pt0_on_ray, t_pt1_on_ray);
		GLOSA_FLOAT max_t = max(t_pt0_on_ray, t_pt1_on_ray);
		
		if( equal( max_t , (GLOSA_FLOAT)0.0 ){
			if( n_intersection ) { *n_intersection = 0; }
			if( pt1 ) {*pt1 = ray.start; }
			return intersect_result::touches;
		}
		
		if( max_t < 0 ){
			if( n_intersection ) { *n_intersection = 0; }
			return intersect_result::disjoints;
		}
		
		//max_t > 0
		if( n_intersection ) { *n_intersection = 2; }
		if(min_t > 0){
			if( pt1 ) { *pt1 = pts[0]; }
			if( pt2 ) { *pt2 = pts[1]; }
			return intersect_result::crosses;
		} 
		
		if( equal( min_t, (GLOSA_FLOAT)0 ) ){
			if( pt1 ) { *pt1 = pts[t_pt0_on_ray > 0 ? 0 : 1]; }
			if( pt2 ) { *pt2 = ray.start; }
			if( n_intersection ) { *n_intersection = 2; }
			return intersect_result::crosses;
		}
		
		//max_t > 0 && min_t <= 0
		if( pt1 ) { *pt1 = pts[t_pt0_on_ray > 0 ? 0 : 1]; }
		if( n_intersection ) { *n_intersection = 1; }
		return intersect_result::crosses;
	}
}

intersect_result intersect(const ray2d& ray, const oriented_rect2d* rect, point2d* pt1, point2d* pt2, int* n_intersection){
}

intersect_result intersect(const ray2d& ray, const triangle2d& tri, point2d* pt1, point2d* pt2, int* n_intersection){
}

intersect_result intersect(const segment2d& seg, const rect2d& rect, point2d* pt1, point2d* pt2, int* n_intersection){
}

intersect_result intersect(const segment2d& seg, const oriented_rect2d* rect, point2d* pt1, point2d* pt2, int* n_intersection){
}

intersect_result intersect(const segment2d& seg, const triangle2d& tri, point2d* pt1, point2d* pt2, int* n_intersection){
}

}
}
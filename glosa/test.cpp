#include "glosa.h"
#include "glosa_geometries.h"

#include "SUnitTestConsole.h"

using namespace glosa;
using namespace efl;

using namespace glosa::level_20_21;
using namespace glosa::level_30_33;

BEGIN_METHOD(line2d_members)
	line2d line0((point2d&)vec2(0.0f, 1.0f), (point2d&)vec2(1.0f, 0.0f));
	TEST_TRUE_PASS( equal(line0.start, vec2(0.0f, 1.0f)) );
	TEST_TRUE_PASS( equal(line0.end, vec2(1.0f, 0.0f)) );

	line2d line1((point2d&)vec2(0.0f, 1.0f), vec2(1.0f, 1.0f));
	TEST_TRUE_PASS( equal(line1.end, vec2(1.0f, 2.0f)) );

	TEST_TRUE_PASS( equal(line0.dir(), vec2(1.0f, -1.0f)) );
	TEST_TRUE_PASS( equal(line0.norm_dir().length(), 1.0f) );
	TEST_TRUE_PASS( equal(line0.abc(), vec3(-1.0f, -1.0f, 1.0f)));
END_METHOD()

BEGIN_TESTCASE(_1d_geom_test)
	ADD_METHOD(line2d_members)
END_TESTCASE()

BEGIN_METHOD(pt_line2d_test)
	line2d line0((point2d&)vec2(0.0f, 1.0f), (point2d&)vec2(1.0f, 0.0f));
	point2d pt0 = (point2d&)vec2(2.0f, -1.0f);
	point2d pt3 = (point2d&)vec2(2.0f, -1.01f);
	point2d pt1 = (point2d&)vec2(-1.0f, 2.0f);
	point2d pt2 = (point2d&)vec2(-1.01f, 2.0f);
	TEST_TRUE_PASS( intersect(pt0, line0) == intersect_result::within );
	TEST_TRUE_PASS( intersect(pt1, line0) == intersect_result::within );
	TEST_TRUE_PASS( intersect(pt2, line0) == intersect_result::disjoints );
	TEST_TRUE_PASS( intersect(pt3, line0) == intersect_result::disjoints );
END_METHOD()

BEGIN_METHOD(pt_ray2d_test)
	ray2d ray0((point2d&)vec2(0.0f, 1.0f), (point2d&)vec2(1.0f, 0.0f));
	point2d pt0 = (point2d&)vec2(2.0f, -1.0f);
	point2d pt1 = (point2d&)vec2(0.0f, 1.0f);
	point2d pt2 = (point2d&)vec2(-1.0f, 2.0f);
	GLOSA_FLOAT t(100000.0);
	TEST_TRUE_PASS( intersect(pt0, ray0, &t) == intersect_result::within );
	TEST_TRUE_PASS( equal(t, 2.0f) );
	TEST_TRUE_PASS( intersect(pt1, ray0, &t) == intersect_result::touches );
	TEST_TRUE_PASS( intersect(pt2, ray0, &t) == intersect_result::disjoints );
	TEST_TRUE_PASS( equal( ray0.t(pt2),  -1.0f) );
END_METHOD()

BEGIN_TESTCASE(intersect_20_21_test)
	ADD_METHOD(pt_line2d_test);
	ADD_METHOD(pt_ray2d_test);
END_TESTCASE()

BEGIN_METHOD(pt_aabb_test)
	point3d pt0 = (point3d&)( vec3(1.0f, 1.0f, 1.0f) );
	point3d pt1 = (point3d&)( vec3(0.9f, 0.9f, 0.9f) );
	glosa::AABB abox( (point3d&)vec3(), vec3(2.0f, 2.0f, 2.0f) );
	TEST_TRUE_PASS( intersect(pt0, abox) == intersect_result::disjoints );
	TEST_TRUE_PASS( intersect(pt1, abox) == intersect_result::within );
END_METHOD()

BEGIN_TESTCASE(intersect_30_33_test)
	ADD_METHOD(pt_aabb_test);
	//ADD_METHOD(pt_obb_test);
END_TESTCASE()

BEGIN_TESTSUITE(glosa_geometries)
	ADD_CASE(_1d_geom_test);
	ADD_CASE(intersect_20_21_test);
	ADD_CASE(intersect_30_33_test);
END_TESTSUITE()

void test(){
	EXECUTE_TEST(glosa_geometries);
	_1d_geom_test.PrintReportToConsole();
	cout << "\n";
	intersect_20_21_test.PrintReportToConsole();
	cout << "\n";
	intersect_30_33_test.PrintReportToConsole();
	system("pause");
}
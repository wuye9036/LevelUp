#include "PropertySetHelper.h"

//¡Ω∏ˆ≤‚ ‘¿‡
class TestBase : public IPropertySet
{
public:
	int x;
	float y;
	double z;
	
	BEGIN_PROPERTY(TestBase)
		REG_PROP_VAR(testint, x);
		REG_PROP_VAR(testfloat, y);
		REG_PROP_VAR(testdouble, z);
	END_PROPERTY(TestBase)
};

class TestDerived : public TestBase
{
public:
	int xx;
	BEGIN_PROPERTY_EX(TestDerived, TestBase)
		REG_PROP_VAR(testint3, xx)
	END_PROPERTY(TestDerived)
};

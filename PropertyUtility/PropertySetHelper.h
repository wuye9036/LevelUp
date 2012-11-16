#include "PropertySet.h"
#include <cassert>

//对使用了PropertySet的类提供获取PropertySet的方法，注意该类并没有提供对PropertySet提供透明访问的接口，而是提供了获取PropertySet的方式。
class IPropertySet
{
public:
	virtual PropertySet* GetPropertySet() = 0;

	template <class T> void Set(const wstring& key, const T& t) { GetPropertySet()->Set(this, key, t); }
	template <class T> void Get(const wstring& key, T& t) { GetPropertySet()->Get(this, key, t);}
};

//简化类使用“属性”的复杂度，并提供必需的函数。
#define BEGIN_PROPERTY(className) protected: void InitProperties(PropertySet* pPropset) {
#define BEGIN_PROPERTY_EX(className, baseName)  protected: void InitProperties(PropertySet* pPropset) {baseName::InitProperties(pPropset);
#define REG_PROP_VAR(propName, var) pPropset->RegisterProperty(this, _T(#propName), &var);
#define END_PROPERTY(className) }\
								public:\
								/*template <class T> void Set(const wstring& key, const T& t) { GetPropertySet()->Set(this, key, t); }\
								template <class T> void Get(const wstring& key, T& t) { GetPropertySet()->Get(this, key, t);}*/\
								PropertySet* GetPropertySet() {static PropertySet _prop_set; static bool _is_init = false; if(!_is_init) {InitProperties(&_prop_set); _is_init = true;} return &_prop_set;}\
								private:

/*********************************

Example

class ExampleClass : public IPropertySet
{
	int foo;
	
	BEGIN_PROPERTY(ExampleClass)
		REG_PROP_VAR(fooName, foo)
	END_PROPERTY()
} eg;

eg.Set("fooName") = 5; // is eq to eg.foo = 5;
**********************************/
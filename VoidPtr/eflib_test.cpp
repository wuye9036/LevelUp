// eflib_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <eflib/include/math.h>

#include <boost/smart_ptr.hpp>

#include "functions_tblhelper.h"
#include "type_register.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;
using namespace efl;
using namespace boost;

typedef int result;

namespace shader_constant
{
		//reg types
	#include BEGIN_REGISTER_TYPE()

	#define TYPE_PARAM float
	#include REGTYPE()

	#define TYPE_PARAM int
	#include REGTYPE()

	#define TYPE_PARAM vec4
	#include REGTYPE()

	#include END_REGISTER_TYPE()

	#include "voidptr.h"

	//reg functions
	template<class T>
	bool assign_impl(voidptr lhs, const_voidptr rhs){
		cout << typeid(T).name();
		*(T*)lhs = *(const T*)rhs;
		return true;
	}

	template<>
	bool assign_impl<empty>(voidptr lhs, const_voidptr rhs){
		cout << typeid(empty).name();
		return false;
	}

	FUNCTIONS_INITIALIZE(bool, (voidptr lhs, const_voidptr rhs), assign_impl, _registered_types_count);

	bool assign(voidptr lhs, const_voidptr rhs){
		if(lhs.get_id() == rhs.get_id()){
			return FUNC_TABLE(assign_impl) [lhs.get_id()](lhs, rhs);
		}
		return false;
	}
}

class container
{
public:
	virtual void get(shader_constant::voidptr pval, size_t pos) = 0;
	virtual void set(shader_constant::const_voidptr val, size_t pos) = 0;
};

template<class ContainerImpl, class ElemType>
class container_impl : public container
{
	typedef ContainerImpl container_type;
	typedef ElemType element_type;

	container_type* pcont;

public:
	container_impl(container_type& cont) : pcont(&cont){
	}

	virtual void get(shader_constant::voidptr pval, size_t pos)
	{
		element_type* pelem = shader_constant::voidptr_cast<element_type>(pval);
		if(pelem){
			*pelem = (*pcont)[pos];
		}
	}

	virtual void set(shader_constant::const_voidptr pval, size_t pos)
	{
		const element_type* pelem = shader_constant::voidptr_cast<element_type>(pval);
		if(pelem){
			(*pcont)[pos] = *pelem;
		}
	}
};

class shader
{
public:
	virtual result set_constant(const wstring& varname, shader_constant::const_voidptr pval) = 0;
	virtual result set_constant(const wstring& varname, shader_constant::const_voidptr pval, size_t index)	= 0;
};

class shader_impl : public shader
{
private:
	typedef map<wstring, shader_constant::voidptr> variable_map;
	typedef map<wstring, shared_ptr<container> > container_variable_map;

	variable_map varmap_;
	container_variable_map contmap_;

public:
	result set_constant(const wstring& varname, shader_constant::const_voidptr pval){
		variable_map::iterator var_it = varmap_.find(varname);
		if( var_it == varmap_.end() ){
			return -1;
		}
		if(shader_constant::assign(var_it->second, pval)){
			return 0;
		}
		return -2;
	}

	result set_constant(const wstring& varname, shader_constant::const_voidptr pval, size_t index)
	{
		container_variable_map::iterator cont_it = contmap_.find(varname);
		if( cont_it == contmap_.end() ){
			return -1;
		}
		cont_it->second->set(pval, index);
		return 0;
	}

	template<class T>
	result register_var(const wstring& varname, T& var)
	{
		varmap_[varname] = voidptr(&var);
		return 0;
	}

	template<class T, class ElemType>
	result register_var_as_container(const wstring& varname, T& var, const ElemType&)
	{
		varmap_[varname] = shader_constant::voidptr(&var);
		contmap_[varname] = shared_ptr<container>(new container_impl<T, ElemType>(var));

		return 0;
	}
};

class test_sh : public shader_impl
{
	vec4 v;

public:
	test_sh()
	{
		register_var_as_container(_T("WorldViewProjMat"), v, v[0]);
	}

	void output()
	{
		cout << v.x << " " << v.y << " "<< v.z << " " << v.w << endl;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	using shader_constant::voidptr;

	test_sh sh;
	vec4 v(0.0f, 0.0f, 0.0f, 1.0f);
	float f(2.0f);
	sh.set_constant(_T("WorldViewProjMat"), voidptr(&v));
	sh.set_constant(_T("WorldViewProjMat"), voidptr(&f), 0);

	sh.output();
	float x = 0.0f;
	float y = 1.0f;
	assign(voidptr(&x), voidptr((int*)&y));

	system("pause");
	return 0;
}


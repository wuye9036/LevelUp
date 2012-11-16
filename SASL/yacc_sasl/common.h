#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <boost/smart_ptr.hpp>

/// 用于简化句柄的声明
#define DECL_TYPE(typetype, tname)\
	typetype tname;\
	typedef boost::shared_ptr< tname > h_##tname;\
	typedef boost::shared_ptr< tname > h_##tname##_weak;

#define DECL_STRUCT(tname) DECL_TYPE(struct, tname)
#define DECL_CLASS(tname) DECL_TYPE(class, tname)

DECL_STRUCT	(decl)

DECL_CLASS	(type_base)
DECL_CLASS	(buidin_type)
DECL_CLASS	(struct_type)
DECL_CLASS	(array_type)
DECL_CLASS	(function_type)

DECL_CLASS	(context)

DECL_CLASS	(scope)
DECL_CLASS	(symbol_entry)
DECL_CLASS	(symbol)
DECL_CLASS	(symbol_table)

DECL_CLASS	(expression)
DECL_CLASS	(Statement)
DECL_CLASS	(Label)

DECL_CLASS	(project)
DECL_CLASS	(unit)
DECL_CLASS	(preprocessor)
DECL_CLASS	(error_reporter)
DECL_CLASS	(makefile)
DECL_CLASS	(compile_flag)
DECL_CLASS	(configuration)

#endif // COMMON_H_INCLUDED

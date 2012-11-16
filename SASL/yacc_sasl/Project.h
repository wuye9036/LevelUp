#ifndef PROJECT_H_INCLUDED
#define PROJECT_H_INCLUDED

#include "common.h"

#include <string>
#include <vector>

class preprocessor
{
	/**
	使用被处理的源文件名作为输入，并输出一个预处理后的临时文件。
	预处理后的文件除#line指令外不再携带其他预编译指令。
	该函数必须为线程安全的函数，可以多线程执行。
	**/
	virtual std::string preprocess(const std::string& filename) = 0;
};

class error_reporter_tags{
public:
	static std::string compiler_config_error();
	static std::string syntax_error();
};

/***
提供了Error Reportor的接口，并且提供了标准Error Reportor的格式的辅助字符串信息。
Error Report的实现中通常需要完成以下工作：
	从其他途径或者依赖于调用方获得出错的上下文；
	对上下文进行分析，并将Error Content格式化成可读和规范的形式。
	所有函数均为并行执行函数。
***/
class error_reporter
{
public:
	/**
	报告编译器的内部错误。
	这些错误的发生多数是由编译器本身的BUG或不完善引起。
	**/
	virtual void report_compiler_internal_error(const std::string& error_content) = 0;

	/**
	报告被分析代码的语法错误
	**/
	virtual void report_syntax_error(const std::string& errContent) = 0;

	/**
	复制一个error_reporter，相同类型，但是初始参数为空。
	**/
	virtual error_reporter* clone() = 0;
};

/**
编译的基本单位。
**/
class unit
{
public:
	unit();

	///	获得当前的上下文。
	context* get_current_context();

	///	获得全局符号表。
	scope* get_global_scope();

	/// 分析一个Unit
	bool parse(const std::string& filename);

	/// 返回相应的Error Report
	error_reporter* get_error_reporter();

private:
	h_context			context_;
	h_symbol_table		symtbl_;
	h_error_reporter	error_reporter_;

};

/***
一个工程是一个完整编译过程的最小单位。它包含了一或多个源文件的路径名以及若干组属于不同配置的编译器参数。
每个编译器应用程序实例只能启用一个工程。
编译器架构上支持文件级别的并行语法和语义分析。但是连接阶段仍然只能串行完成。
目前的实现为单线程方式。
***/
class project
{
public:
	static project& instance();

	/**
	设置preprocessor和ErrorReport执行初始化过程。
	该函数在其他方法被调用前至少需要被执行一次。
	**/
	static void initialize(h_preprocessor pp, h_error_reporter err_reporter);
	std::vector<h_unit>& get_units();

	/**
		对框架进行语法分析，获得相应的语法树。
		如果传入configName，则会选择相应的配置进行分析；
		如果传入的configName不存在，或者分析过程出现错误，则分析自动停止。
		如果传入的configName为空，则选取工程的第一个Config。
	**/
	void parse(const std::string& config_name = "");

	///返回Project的preprocessor
	preprocessor* get_pp();

	///返回Project的Error Rporter
	error_reporter* get_error_reporter();

private:
	/**
	获取一个已知ID的编译器配置。如果配置文件不存在则返回空。
	函数由框架调用。配置名称来自于saslc命令行的配置名。
	**/
	configuration* get_config(const std::string& config_name);

	///根据传入的配置进行分析。
	bool parse_units(configuration* pconf);

	///链接，生成目标代码。
	bool link(configuration* pconf);

	project();
	~project();

	static project		prj_;

	h_preprocessor		pp_;
	h_error_reporter	err_reporter_;
	h_makefile			mf_;
	std::vector<h_unit>	units_;
};

//project::Instance的一个简化调用封装。
inline project& proj()
{
	return project::instance();
}

#endif // PROJECT_H_INCLUDED

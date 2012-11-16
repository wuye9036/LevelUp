#pragma once

#include <boost/bind.hpp>
#include <string>
#include <vector>
#include "LogFile.h"
using namespace std;

#define CITY_PARAM 1
#define CONST_DIST 1

enum ENDSTATE
{
	NONE,
	ABORT,
	UNSHORTEQUAL,
	UNLONGEQUAL,
	OK
};

class QuitInfo{
public:
	QuitInfo(bool isNormalQuit, size_t itcount)
		:isNormalQuit_(isNormalQuit), itcount_(itcount)
	{}

	bool isNormalQuit(){
		return isNormalQuit_;
	}

	size_t iterated_count(){
		return itcount_;
	}

	friend ostream& operator <<(ostream& os, const QuitInfo& info);

private:
	size_t itcount_;
	bool isNormalQuit_;
};

ostream& operator <<(ostream& os, const QuitInfo& info){
}

//提供内部线程机制
class UrbanSimulator
{
public:
	UrbanSimulator(void);
	~UrbanSimulator(void);
	
	//控制信息
	vector<string>		m_errs;

	//输入输出信息
	string				m_folder;
	string				m_logName;
	LogFile				m_log;

	//地理参数
	double	m_alpha;
	double	m_beta;
	double	m_delta;
	double	m_gamma;
	int		m_n;
	double	m_L;
	double	m_phi;
	double	m_rho;
	double	m_sigma;
	double	m_sp;
	double	m_tc;
	double	m_w0;
	long	m_grdstep;
	int		m_shortit;
	int		m_longit;

	/////////////////////////////////////
	void Init();
	bool Calc();
	bool CalcImpl();
	ENDSTATE GetEndState();

	void Reset(){}
	bool StopCalc();

private:
	ENDSTATE m_endState;	//程序的退出状态

	//运算过程中所需要的变量
	vector<double> m_G, m_D, m_NW, m_iphi, m_Y, m_I, m_WR, m_RW, m_welf;
	vector<double> m_lambda[9];

	string m_geoAdvFile;
	string m_transDistFile;
	string m_resultFile;

	/***************************
	计算过程
	***************************/
	void LoadInitialData();	//初始化日志文件
	pair<bool, int> ShortEql();	//短期均衡，返回值：是否短期均衡/均衡成立的循环次数
};

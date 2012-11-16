#pragma once

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <string>
#include <vector>
#include "LogFile.h"
using namespace std;

enum ENDSTATE
{
	NONE,
	ABORT,
	UNSHORTEQUAL,
	UNLONGEQUAL,
	OK
};

//提供内部线程机制
class UrbanSimulator
{
public:
	UrbanSimulator(void);
	~UrbanSimulator(void);
	
	//控制信息
	string					m_folder;
	vector<const char *>	m_errs;
	LogFile					m_log;
	//地理参数
	float	m_alpha;
	float	m_beta;
	float	m_delta;
	float	m_gamma;
	int		m_n;
	float	m_L;
	float	m_phi;
	float	m_rho;
	float	m_sigma;
	float	m_sp;
	double	m_tc;
	float	m_w0;
	long	m_grdstep;
	int		m_shortit;
	int		m_longit;

	/////////////////////////////////////
	void Init();
	bool Calc();
	bool CalcImpl();
	bool IsDone();
	float GetPercentage();
	ENDSTATE GetEndState();

	void Reset(){}
	bool StopCalc();
private:
	ENDSTATE m_endState;	//程序的退出状态
	
	float	m_percentage;	//程序已经执行的百分比
	bool	m_isRunning;		//线程是否处于执行状态
	bool	m_isDone;			//线程是否结束
	bool	m_isWaitingExit;	//是否等待退出

	boost::mutex				m_mutex;
	boost::thread*			m_pThread;

	//运算过程中所需要的变量
	vector<double> m_G, m_D, m_NW, m_iphi, m_Y, m_I, m_WR, m_RW;
	vector<double> m_lambda[9];

	/****************************
	运行控制辅助
	****************************/
	void SetPercentage(float v);
	void SetDone(bool v);
	void SetRunning(bool v);

	/***************************
	计算过程
	***************************/
	void LoadInitialData();	//初始化日志文件
	pair<bool, int> ShortEql();	//短期均衡，返回值：是否短期均衡/均衡成立的循环次数
};

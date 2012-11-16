#ifndef NEGSimulator_H
#define NEGSimulator_H

#include <boost/thread.hpp>
#include <boost/python.hpp>

#include <ostream>
#include <vector>

enum RunState{
	RS_Ready = 1,
	RS_Running = 2,
	RS_OK = 4,
	RS_Aborted = 8,
	RS_NotReady = 16,
	RS_Any = 31
};

class QuitInfo{
public:
	QuitInfo(bool isNormalQuit, size_t itcount)
		:isNormalQuit_(isNormalQuit), itcount_(itcount)
	{}

	QuitInfo(const QuitInfo& rhs):isNormalQuit_(rhs.isNormalQuit_), itcount_(rhs.itcount_)
	{}

	QuitInfo& operator = (const QuitInfo& rhs){
		isNormalQuit_ = rhs.isNormalQuit_;
		itcount_ = rhs.itcount_;
		return *this;
	}

	bool isNormalQuit(){
		return isNormalQuit_;
	}

	size_t iterated_count(){
		return itcount_;
	}

	//friend std::ostream& operator <<(std::ostream& os, const QuitInfo& info);

private:
	size_t itcount_;
	bool isNormalQuit_;
};

//std::ostream& operator <<(std::ostream& os, const QuitInfo& info){
//	return os;
//}

class NEGSimulator
{
protected:
	//经济参数
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

	int		m_lcount;

	//运行状态
	QuitInfo	m_sQuitinfo;
	QuitInfo	m_lQuitInfo;

	volatile RunState m_state;
	bool		m_isWillAbort;

	boost::thread m_runImplThread;
	boost::mutex  m_mutex;

	//运算过程中所需要的变量
	std::vector<double> m_G, m_D, m_NW, m_iphi, m_Y, m_I, m_WR, m_RW, m_welf;
	std::vector<double> m_lambda[9];


	bool IsLongEqual();
	QuitInfo ShortEqual();
	void RunImpl();
	bool CheckAndSetState(RunState precondition, RunState rs);

public:
	NEGSimulator();
	~NEGSimulator();

	void LoadEconomicParametersFile(const std::string& file);
	void SetDistanceMatrix(boost::python::object distMat);
	void SetWeights(boost::python::object weights);

	void Reset();
	void Run();
	void Abort();

	float Progress();
	RunState State();

	QuitInfo LongQuitInfo();
	QuitInfo ShortQuitInfo();
};

#endif // NEGSimulator_H
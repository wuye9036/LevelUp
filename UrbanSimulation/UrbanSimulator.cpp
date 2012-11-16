#include "StdAfx.h"
#include ".\urbansimulator.h"
#include "FileWrapper.h"
#include "run_nbr_times.h"
#include <algorithm>
UrbanSimulator::UrbanSimulator(void):	m_isDone(false), 
										m_isRunning(false), 
										m_pThread(NULL), 
										m_isWaitingExit(false),
										m_log("C:\\log.txt")
{
}

UrbanSimulator::~UrbanSimulator(void)
{
	delete m_pThread;
}

void UrbanSimulator::Init()
{
	m_folder = _T("E:\\ZJUrbanSim\\Data\\");
	m_alpha = 0.08f;
	m_beta = 0.8f;
	m_delta = 0.4f;
	m_gamma = 0.4f;
	m_n = 0;
	m_L = 1.0f;
	m_phi = 1.0f;
	m_rho = 0.8f;
	m_sigma = 0.001f;
	m_sp = 0.5f;
	m_tc = 1.3;
	m_w0 = 1.0f;
	m_grdstep = 1;
	m_longit = 200;
	m_shortit = 200;
}

bool UrbanSimulator::Calc()
{
	boost::mutex::scoped_lock lock(m_mutex);
	if(m_isRunning) return false; //如果某一个计算正在运行,则无效
	m_isRunning = true;
	m_isDone = false;
	m_isWaitingExit = false;

	if(m_pThread){
		delete m_pThread;	
	}

	m_pThread = new boost::thread(boost::bind(&UrbanSimulator::CalcImpl,this));
	return true;

}

bool UrbanSimulator::CalcImpl()
{
	int i;

	string rvname;
	char rvStr[1024];
	_stprintf(rvStr, _T("%s_tc%f.txt"), _T(".\\result"), m_tc);

	rvname=rvStr;
	rvname=m_folder+rvname;

	FileWrapper rvFile(rvname.c_str(),"w");
	if(!rvFile){
		m_errs.push_back("结果输出文件打开失败");
		return false;
	}

	//输入初始数据
	LoadInitialData();

	m_NW.resize(m_n);
	m_iphi.resize(m_n);
	m_Y.resize(m_n);
	m_I.resize(m_n);
	m_WR.resize(m_n);
	m_RW.resize(m_n);

	double arw, ltemp;
	double sum_lambda[9];
	double count_lambda[9];

	//设置进度为开始
	SetPercentage(0.0f);

	///////////////////算法开始///////////////////////////////////////////////////////////////////
	bool isLongEquilium = true;
	
	m_NW.assign(m_n, m_w0);
	m_iphi.assign(m_n, m_phi / m_n);

	// start long-run equilibrium
	for(int lcount=0; lcount<m_longit; lcount++)
	{
		//进行一些循环间的操作
		//判断执行百分比；退出判定
		SetPercentage(lcount / float(m_longit));

		{
			boost::mutex::scoped_lock lock(m_mutex);
			if(m_isWaitingExit){
				m_isWaitingExit = false;
				m_endState = ABORT;
				return true;
			}
		}

		//执行短期均衡
		pair<bool, int> rv = ShortEql();
		if(!rv.first) {
			m_log.Write(_T("短期非均衡！"));
			m_log.Writeln(rv.second);
			{
				boost::mutex::scoped_lock lock(m_mutex);
				m_endState = UNSHORTEQUAL;
			}
			return false; //直接返回
		} else {
			m_log.Write(_T("短期均衡！"));
			m_log.Writeln(rv.second);
		}

		//RUN_TIMES_RANGE(1, 3, (m_log.Write(m_NW)));

		arw =0.0;
		
		for (i=0; i<m_n; i++) m_RW[i] = m_WR[i] * pow(m_I[i], double(-m_delta));	// calculate real wage	
		for ( i = 0; i <m_n; i++) arw = arw + m_RW[i] * m_lambda[0][i];				// calculate the average real wage
		
		// calculate m_lambda[1]
		for (i=0; i<m_n; i++)
			m_lambda[1][i] = m_lambda[0][i] + m_sp * (m_RW[i] - arw);
		
		// calculate m_lambda[2]
		for (i=0; i<m_n; i++)
		{
			if (m_lambda[1][i] <= 0.0)
				m_lambda[2][i] = 0;
			else
				m_lambda[2][i] = m_lambda[1][i];
		}
		
		for(int ilamb = 3; ilamb < 8; ++ilamb) {
			// calculate m_lambda[ilamb]
			sum_lambda[ilamb - 1] = 0;
			for (i=0; i<m_n; i++)
				sum_lambda[ilamb - 1] = sum_lambda[ilamb - 1] + m_lambda[ilamb - 1][i];
			count_lambda[ilamb - 1] = 0;
			for (i=0; i<m_n; i++)
			{
				if (m_lambda[ilamb - 1][i] == 0.0)
					count_lambda[ilamb - 1] += 1;
			}
			for (i=0; i<m_n; i++)
			{
				if (sum_lambda[ilamb - 1] <= 1.0)
					m_lambda[ilamb][i]=m_lambda[ilamb - 1][i];
				else if (m_lambda[ilamb - 1][i]<((sum_lambda[ilamb - 1] - 1.0)/(m_n - count_lambda[ilamb - 1])))
					m_lambda[ilamb][i] = 0;
				else
					m_lambda[ilamb][i] = m_lambda[ilamb - 1][i];
			}
		}
					
		// calculate m_lambda[8]
		sum_lambda[7] = 0;

		for (i=0; i<m_n; i++)
			sum_lambda[7] += m_lambda[7][i];
		
		count_lambda[7] = 0;
		for (i=0; i<m_n; i++)
		{
			if (m_lambda[7][i] == 0.0)
				count_lambda[7] += 1;
		}
		for (i=0; i<m_n; i++)
		{
			if (m_lambda[7][i] == 0.0)
				m_lambda[8][i] = 0;
			else
				m_lambda[8][i] = m_lambda[7][i] + (1.0 - sum_lambda[7]) / (m_n - count_lambda[7]);
		}

		// 判断长期均衡是否结束
		isLongEquilium = true;
		for (i=0; i<m_n; i++)
		{
			if (m_lambda[0][i] == 0.0 && m_lambda[8][i] != 0.0)
			{
				isLongEquilium = false;
				break;
			}
			if (m_lambda[0][i] != 0.0 && m_lambda[8][i] == 0.0)
			{
				isLongEquilium = false;
				break;
			}
			if (m_lambda[0][i] != 0.0 && m_lambda[8][i] != 0.0)
			{
				ltemp = fabs((m_lambda[8][i] - m_lambda[0][i]) / m_lambda[0][i]);
				if (ltemp > m_sigma)
				{
					isLongEquilium = false;
					break;
				}
			}
		}

		if (isLongEquilium)
			break;

		m_lambda[0].assign(m_lambda[8].begin(), m_lambda[8].end());

    }// end long-run equilibrium

	///////////////////算法结束///////////////////////////////////////////////////////////////////
	for (i=0; i<m_n; i++)
	{
		//fprintf(rvFile,"%d %.6f %.6f\n", (i+1), m_G[i], m_lambda[8][i]);
		fprintf(rvFile,"%d %.6f\n", (i+1), m_lambda[8][i]);
	}

	SetDone(true);
	SetRunning(false);

	if(!isLongEquilium) {
		m_log.Writeln(_T("长期未均衡！"));
		{
			boost::mutex::scoped_lock lock(m_mutex);
			m_endState = UNLONGEQUAL;
		}
		return false;
	}

	{
		boost::mutex::scoped_lock lock(m_mutex);
		m_endState = OK;
	}
	
	return true;
}

bool UrbanSimulator::IsDone()
{
	boost::mutex::scoped_lock lock(m_mutex);
	return m_isDone;
}

bool UrbanSimulator::StopCalc()
{
	{
		boost::mutex::scoped_lock lock(m_mutex);
		m_isWaitingExit = m_isRunning ? true : false;
	}

	m_pThread->join();
	delete m_pThread;
	m_pThread = NULL;

	{
		boost::mutex::scoped_lock lock(m_mutex);
		m_isDone = false;
		m_isRunning = false;
	}
	return true;
}

float UrbanSimulator::GetPercentage()
{
	boost::mutex::scoped_lock lock(m_mutex);

	float rv = m_percentage;
	if(!m_isRunning) rv = 0.0f;
	if(m_isDone) rv = 1.0f;

	return rv;
}

ENDSTATE UrbanSimulator::GetEndState()
{
	boost::mutex::scoped_lock lock(m_mutex);

	return m_endState;
}

void UrbanSimulator::SetPercentage(float v)
{
	boost::mutex::scoped_lock lock(m_mutex);
	m_percentage = v;
}

void UrbanSimulator::SetDone(bool v)
{
	boost::mutex::scoped_lock lock(m_mutex);
	m_isDone = v;
}

void UrbanSimulator::SetRunning(bool v)
{
	boost::mutex::scoped_lock lock(m_mutex);
	m_isRunning = v;
}

pair<bool, int> UrbanSimulator::ShortEql()
{
	double temp, temp1, temp2, stemp;
	int i, j;
	bool isShortEquilium;
	double hulp0, hulp1, hulp2, epsilon;
	int scount;

	epsilon=1/(1-m_rho);
	hulp0=1/epsilon;hulp1=1-epsilon;hulp2=1/(1-epsilon);

	temp = temp1 = temp2 = 0.0;

	//RUN_TIMES_RANGE(1, 1, (m_log.Write(m_lambda[0])));
	//RUN_TIMES_RANGE(1, 1, (m_log.Write(m_NW)));
	//RUN_TIMES_RANGE(1, 1, (m_log.Write(m_iphi)));

	// start short-run equilibrium
	for (scount = 0; scount < m_shortit; scount++)
	{
		for (i=0;i<m_n;i++)
		{
			// calculate income - m_Y
			m_Y[i] = m_lambda[0][i]*m_NW[i]*m_gamma*m_L+m_iphi[i]*(1-m_gamma)*m_L;
			
			// calculate price index － m_I
			temp =0.0;
			for (j=0; j<m_n; j++)
			{
				temp1 = pow(m_D[i*m_n+j],hulp1);
				temp2 = pow(m_NW[j],hulp1);
				temp = temp+m_lambda[0][j]*temp1*temp2;
			}
			temp1 = m_gamma*m_L/(m_alpha*epsilon);
			temp2 = (m_beta/m_rho) * pow(temp1,hulp2);
			m_I[i] = temp2 * pow(temp,hulp2);
		}

		//RUN_TIMES_RANGE(1, 3, (m_log.Write(m_I)));

		// calculate wage rate - m_WR
		for (i=0; i<m_n; i++)
		{
			temp = 0;
			for (j=0; j<m_n; j++)
				temp = temp + m_Y[j] * pow(m_D[i*m_n+j], hulp1) * pow(m_I[j], -hulp1);
			temp1 = m_delta/(-hulp1*m_alpha);
			m_WR[i]=m_rho * pow(m_beta, -m_rho) * pow(temp1, hulp0) * pow(temp, hulp0);
		}

		// 判断短期均衡是否结束
		isShortEquilium = true;
		for (i=0; i<m_n; i++)
		{
			stemp = fabs((m_WR[i] - m_NW[i]) / m_NW[i]);
			if  (stemp > m_sigma)
			{
				isShortEquilium = false;
				break;
			}
		}

		// 短期均衡结束
		if (isShortEquilium){
			return make_pair(true, scount); //短期均衡结束
		}
		
		// 赋值
		m_NW.assign(m_WR.begin(), m_WR.end());

	}// end short-run equilibrium

	return make_pair(false, scount); //全部迭代结束均未收敛

}

void UrbanSimulator::LoadInitialData()
{
	string advantagename, transdistname;

	//初始化文件名
	advantagename="\\geoadvantage.txt";
	advantagename=m_folder+advantagename;
	transdistname="\\transdist.txt";
	transdistname=m_folder+transdistname;

	char tempstring[260];
	int i,j,inputCnt;

	//////////////////////////////////////////////////
	FileWrapper advtFile(advantagename.c_str(),"r");
	fscanf(advtFile, "%d", &m_n);

	FileWrapper transdistFile(transdistname.c_str(),"r");
	fscanf(transdistFile,"%s",tempstring);

	for(i=0; i<m_n; i++){
		fscanf(transdistFile,"%d",&inputCnt);
	}
	if(inputCnt != m_n){
		m_errs.push_back("输入的n值和文件实际不符!");
		return;// false;
	}

	m_G.resize(m_n);
	m_D.resize(m_n * m_n);

	for(i = 0; i < 9; ++i) m_lambda[i].resize(m_n);

	//读取数据
	for(i=0;i<m_n;i++)
	{
		//将序号滤除
		fscanf(transdistFile,"%d",&inputCnt);
		fscanf(advtFile,"%d",&inputCnt);

		fscanf(advtFile,"%lf", &(m_G[i]));
		for(j=0;j<m_n;j++){
			fscanf(transdistFile,"%lf",&(m_D[i*m_n+j]));
		}
	}

	RUN_TIMES_RANGE(1, 1, (m_log.Write(m_G)));

	//计算并初始化数据
	double m_ave = 0.0;
	double m_sum = 0.0;
	double m_base = m_L / m_n;

	//Add On Base and Get Sum
	for(i=0;i<m_n;i++) {
		m_G[i] = m_base + m_base * m_G[i];
		m_sum += m_G[i];
	}

	//Normalize
	for(i = 0; i < m_n; ++i) {
		m_G[i] /= m_sum;
		m_lambda[0][i] = m_G[i];
	}

	// 计算运输成本
	for(i = 0; i < m_n; i++){
		for(j = 0; j < m_n; j++){
			m_D[i*m_n+j] = pow(m_tc, m_D[i*m_n+j] / m_grdstep); // 指数方法
		}
	}

	m_log.Write(m_G);
}
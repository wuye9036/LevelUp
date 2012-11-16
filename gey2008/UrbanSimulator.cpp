
#include "stdafx.h"
#include ".\urbansimulator.h"
#include "FileWrapper.h"
#include "run_nbr_times.h"
#include <algorithm>
#include <math.h>

UrbanSimulator::UrbanSimulator()
{
}

UrbanSimulator::~UrbanSimulator(void)
{}

void UrbanSimulator::Init()
{
	m_delta = 0.4f;			// share of spending on manufactures
	m_gamma = 0.4f;			// share of labor in manufacturing
	m_rho = 0.8f;			// elasticity of substitution parameter
	m_beta = 0.8f;			// variable cost
	m_alpha = 0.08f;		// fixed cost
	m_tc = 1.1f;			// transport cost
	m_n = 0;				// number of regions
	m_L = 1.0f;				// number of laborers
	m_phi = 1.0f;			// distribution of immobile population
	m_sigma = 0.001f;		// stopping criterion
	m_sp = 0.5f;			// speed of adjustment
	m_w0 = 1.0f;			// initial value
	m_grdstep = 1;
	m_longit = 100;			// number of iteration of long-run equilibrium
	m_shortit = 200;		// number of iteration of short-run equilibrium
}

bool UrbanSimulator::Calc()
{
	return CalcImpl();
}

bool UrbanSimulator::CalcImpl()
{
	int i;

	//修正Directory，去掉最后一个“\\”
	if (*(m_folder.rbegin()) == '\\')
	{
		m_folder = m_folder.substr(0, m_folder.size() - 1);
	}

	m_geoAdvFile = m_folder + string("\\geoadvantage.txt");
	m_transDistFile = m_folder + string("\\transdist.txt");
	m_resultFile = m_folder + string("\\result.txt");

	FileWrapper rvFile(m_resultFile.c_str(),"w");
	if(!rvFile){
		m_errs.push_back("结果输出文件打开失败");
		return false;
	}

	//输入初始数据
	LoadInitialData();

	m_iphi.resize(m_n);			// 各区域－农村劳动力份额 (share of immobile laborer)
	m_Y.resize(m_n);			// 各区域－收入 (income)
	m_I.resize(m_n);			// 各区域－价格指数 (price index)
	m_WR.resize(m_n);			// 各区域－工资率 (wage rate)
	m_NW.resize(m_n);			// 各区域－初始工资率
	m_RW.resize(m_n);			// 各区域－实际工资 (real wage)
	m_welf.resize(m_n);			// 各区域－福利 (welfare)

	double arw, ltemp;
	double sum_lambda[9];
	double count_lambda[9];

	///////////////////算法开始///////////////////////////////////////////////////////////////////
	bool isLongEquilium = true;
	
	// 赋初值
	m_NW.assign(m_n, m_w0);				// 初始工资率赋值为0
	m_iphi.assign(m_n, m_phi / m_n);	// 各区域农村劳动力份额＝1/区域个数

	// 长期均衡
	for(int lcount = 0; lcount < m_longit; lcount++)
	{
		// 执行短期均衡
		pair<bool, int> rv = ShortEql();
		if(!rv.first) {
			m_log.Write(_T("短期未均衡！"));
			m_log.Writeln(rv.second);

			return false; //直接返回
		} else {
			m_log.Write(_T("短期均衡！"));
			m_log.Writeln(rv.second);
		}

		//RUN_TIMES_RANGE(1, 3, (m_log.Write(m_NW)));

		// 继续长期均衡计算
		arw = 0.0;							// average real wage
		
		for (i = 0; i < m_n; i++)
		{				
			m_RW[i] = m_WR[i] * pow(m_I[i], double(-m_delta));	// calculate real wage
			m_welf[i] = m_Y[i] * pow(m_I[i], double(-m_delta));	// calculate welfare
		}

		for ( i = 0; i < m_n; i++)			// calculate average real wage
			arw += m_RW[i] * m_lambda[0][i];

		// calculate m_lambda[1]－第1次调整
		for (i = 0; i < m_n; i++)
			m_lambda[1][i] = m_lambda[0][i] + m_sp * (m_RW[i] - arw);
		
		// calculate m_lambda[2]－第2次调整
		for (i = 0; i < m_n; i++)
		{
			if (m_lambda[1][i] <= 0.0)
				m_lambda[2][i] = 0.0;
			else
				m_lambda[2][i] = m_lambda[1][i];
		}
		
		// 第3次－第7次调整
		for(int ilamb = 3; ilamb < 8; ++ilamb)
		{
			// calculate m_lambda[ilamb]
			sum_lambda[ilamb - 1] = 0.0;
			for (i = 0; i < m_n; i++)			// 计算各区域调整值的和
				sum_lambda[ilamb - 1] += m_lambda[ilamb - 1][i];

			count_lambda[ilamb - 1] = 0.0;		// 计算各区域调整值不等于0的个数
			for (i = 0; i < m_n; i++)
			{
				if (m_lambda[ilamb - 1][i] == 0.0)
					count_lambda[ilamb - 1] += 1.0;
			}

			for (i = 0; i < m_n; i++)			// 计算各区域的调整值
			{
				if (sum_lambda[ilamb - 1] <= 1.0)
					m_lambda[ilamb][i] = m_lambda[ilamb - 1][i];	// 上次赋给本次	
				else if (m_lambda[ilamb - 1][i] < ((sum_lambda[ilamb - 1] - 1.0) / (m_n - count_lambda[ilamb - 1])))
					m_lambda[ilamb][i] = 0.0;
				else
					m_lambda[ilamb][i] = m_lambda[ilamb - 1][i];
			}
		}
					
		// calculate m_lambda[8]－最终调整
		sum_lambda[7] = 0.0;

		for (i = 0; i < m_n; i++)
			sum_lambda[7] += m_lambda[7][i];
		
		count_lambda[7] = 0;
		for (i = 0; i < m_n; i++)
		{
			if (m_lambda[7][i] == 0.0)
				count_lambda[7] += 1;
		}
		for (i = 0; i < m_n; i++)
		{
			if (m_lambda[7][i] <= 0.0)
				m_lambda[8][i] = 0.0;
			else
				m_lambda[8][i] = m_lambda[7][i] + (1.0 - sum_lambda[7]) / (m_n - count_lambda[7]);
		}

		// 判断长期均衡是否结束
		isLongEquilium = true;
		for (i = 0; i < m_n; i++)
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

		if (isLongEquilium)			// 如果长期均衡结束
			break;

		// 输出一些计算结果
		fprintf(rvFile,"%d\t%.6f\t%.6f\n", (lcount + 1), m_lambda[8][0], m_RW[0]);

		// 将lambda8赋给lambda0
		m_lambda[0].assign(m_lambda[8].begin(), m_lambda[8].end());

    }// end long-run equilibrium

	if(!isLongEquilium) {
		m_log.Writeln(_T("长期未均衡！"));
		return false;
	}

	m_endState = OK;
	
	return true;
}

ENDSTATE UrbanSimulator::GetEndState()
{
	return m_endState;
}

// 短期均衡
pair<bool, int> UrbanSimulator::ShortEql()
{
	double temp, temp1, temp2, stemp;
	int i, j;
	bool isShortEquilium;
	double  epsilon, hulp0, hulp1, hulp2;
	int scount;

	epsilon = 1.0 / (1.0 - m_rho);
	hulp0 = 1.0 / epsilon;
	hulp1 = 1.0 - epsilon;
	hulp2 = 1.0 / hulp1;

	temp = temp1 = temp2 = 0.0;

	//RUN_TIMES_RANGE(1, 1, (m_log.Write(m_lambda[0])));
	//RUN_TIMES_RANGE(1, 1, (m_log.Write(m_NW)));
	//RUN_TIMES_RANGE(1, 1, (m_log.Write(m_iphi)));

	// short-run equilibrium
	for (scount = 0; scount < m_shortit; scount++)
	{
		for (i = 0; i < m_n; i++)
		{
			// calculate income Y－收入
			m_Y[i] = m_lambda[0][i] * m_NW[i] * m_gamma * m_L + m_iphi[i] * (1 - m_gamma) * m_L;
			
			// calculate price index I － 价格指数
			temp = 0.0;
			for (j = 0; j < m_n; j++)						// 第3项
			{
				temp1 = pow(m_D[i * m_n + j], hulp1);		// transport cost
				temp2 = pow(m_NW[j], hulp1);				// wage rate
				temp += m_lambda[0][j] * temp1 * temp2;		// matrix product
			}
			temp1 = m_gamma * m_L / m_alpha / epsilon;		// 第2项
			temp2 = (m_beta / m_rho) * pow(temp1, hulp2);	// 第1项 × 第2项
			m_I[i] = temp2 * pow(temp, hulp2);				// 所有项乘积
		}

		//RUN_TIMES_RANGE(1, 3, (m_log.Write(m_I)));

		// calculate wage rate W－工资率
		for (i = 0; i < m_n; i++)
		{
			temp = 0.0;
			for (j = 0; j < m_n; j++)
			{
				temp1 = pow(m_D[i * m_n + j], hulp1);		// transport cost
				temp2 = pow(m_I[j], -hulp1);				// price index
				temp += m_Y[j] * temp1 * temp2;				// 第3项
			}
			temp1 = m_delta / (-hulp1 * m_alpha);			// 第2项
			temp2 = m_rho * pow(m_beta, -m_rho);			// 第1项
			m_WR[i] = temp2 * pow(temp1, hulp0) * pow(temp, hulp0);
		}

		// 判断短期均衡是否结束
		isShortEquilium = true;
		for (i = 0; i < m_n; i++)
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

// 输入初始数据
void UrbanSimulator::LoadInitialData()
{
	m_log.open(m_logName.c_str());
	string advantagename, transdistname;

	advantagename = m_geoAdvFile;
	transdistname = m_transDistFile;

	char tempstring[260];
	int i,j,inputCnt;

	//////////////////////////////////////////////////
	FileWrapper advtFile(advantagename.c_str(),"r");
	FileWrapper transdistFile(transdistname.c_str(),"r");

	fscanf(advtFile, "%d", &m_n);
	m_G.resize(m_n);
	m_D.resize(m_n * m_n);

	for(i = 0; i < 9; ++i)
		m_lambda[i].resize(m_n);

	for(int i = 0; i < m_n; ++i){
		fscanf(advtFile, "%lf", &(m_G[i]));
	}

	//读取数据
	for(i = 0; i < m_n; i++)
	{
		for(j = 0; j < m_n; j++){
			fscanf(transdistFile,"%lf",&(m_D[i * m_n + j]));
		}
	}

	//RUN_TIMES_RANGE(1, 1, (m_log.Write(m_G)));

	// 计算并初始化数据
//	double m_ave = 0.0;
	double m_sum = 0.0;
//	double m_base = m_L / m_n;
//
	// Add On Base and Get Sum
	for(i = 0; i<m_n; i++) 
	{
//#if defined(_EXP_CITY_VER_)
//		m_G[i] = m_base * (1.0 + pow(CITY_PARAM, log(1.0 + m_G[i])));
//#endif
//#if defined(_LINEAR_CITY_VER_)
//		m_G[i] = m_base * (1.0 + m_G[i] * CITY_PARAM);
//#endif
		m_sum += m_G[i];
	}

	for(i = 0; i < m_n; ++i) 
	{
		m_G[i] /= m_sum;					// 归一化				
		m_lambda[0][i] = m_G[i];			// 赋初值
	}
	m_log.Write(m_G);


	// 计算运输成本
	for(i = 0; i < m_n; i++){
		for(j = 0; j < m_n; j++){
#ifdef _EXP_DIST_VER_
			m_D[i * m_n + j] = pow(m_tc, m_D[i * m_n + j] / m_grdstep); // 指数方法
#endif
#ifdef _LN_DIST_VER_
			m_D[i*m_n+j] = pow(m_tc, log(CONST_DIST + m_D[i*m_n+j] / m_grdstep));  // 对数方法
#endif
		}
	}

//	m_log.Write(m_D, m_n);
}
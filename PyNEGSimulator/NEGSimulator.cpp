#include "NEGSimulator.h"
#include "Ecoparameters.h"

#include <boost/thread.hpp>

using namespace boost;
using namespace boost::python;
using namespace std;

NEGSimulator::NEGSimulator()
	:m_state(RS_NotReady), 
	m_sQuitinfo(false, -1),
	m_lQuitInfo(false, -1)
{
}

NEGSimulator::~NEGSimulator()
{

}

void NEGSimulator::LoadEconomicParametersFile( const string& file )
{
	Ecoparameters ecoParam;
	ecoParam.LoadFromXML(file);

	m_alpha = ecoParam.alpha;
	m_beta = ecoParam.beta;
	m_delta = ecoParam.delta;
	m_gamma = ecoParam.gamma;
	m_L = ecoParam.L;
	m_phi = ecoParam.phi;
	m_rho = ecoParam.rho;
	m_sigma = ecoParam.sigma;
	m_sp = ecoParam.sp;
	m_tc = ecoParam.tc;
	m_w0 = ecoParam.w0;
	m_grdstep = ecoParam.grdstep;
	m_shortit = ecoParam.shortit;
	m_longit = ecoParam.longit;
}

void NEGSimulator::SetDistanceMatrix( object distMat )
{
	if(!CheckAndSetState((RunState)~RS_Running, RS_NotReady)){
		return;
	}

	m_n = len(distMat);
	m_D.resize(m_n * m_n);

	for(int i = 0; i < m_n; ++i){
		for(int j = 0; j < m_n; ++j){
			m_D[i*m_n+j] = extract<double>(distMat[i][j]);
		}
	}

	CheckAndSetState(RS_Any, RS_Ready);
}

void NEGSimulator::SetWeights( object weights )
{
	if(CheckAndSetState(RS_Running, RS_NotReady)){
		return;
	}

	m_n = len(weights);

	m_G.resize(m_n);
	m_D.resize(m_n * m_n);

	for(int i = 0; i < m_n; ++i){
		m_G[i] = extract<double>(weights[i]);
	}

	CheckAndSetState(RS_Any, RS_Ready);
}

void NEGSimulator::Reset()
{
	CheckAndSetState(RunState(~RS_Running), RS_Ready);
}

void NEGSimulator::Run()
{
	if((m_state & RS_Running) == 0){
		m_runImplThread = thread(bind(&NEGSimulator::RunImpl, this));
	}
}

void NEGSimulator::Abort()
{
	m_isWillAbort = true;
	if (m_runImplThread.joinable()){
		m_runImplThread.join();
	}
}

// this method will be deprecated.
float NEGSimulator::Progress()
{
	assert(false); 
	return 0.0f;
}

RunState NEGSimulator::State()
{
	return m_state;
}

QuitInfo NEGSimulator::ShortEqual()
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
			return QuitInfo(true, scount); //短期均衡结束
		}

		// 赋值
		m_NW.assign(m_WR.begin(), m_WR.end());

	}// end short-run equilibrium

	return QuitInfo(false, -1); //全部迭代结束均未收敛
}

void NEGSimulator::RunImpl()
{
	if(!CheckAndSetState( RS_Ready, RS_Running )){
		m_lQuitInfo = QuitInfo(false, -1);
		return;
	}

	m_iphi.resize(m_n);			// 各区域－农村劳动力份额 (share of immobile laborer)
	m_Y.resize(m_n);			// 各区域－收入 (income)
	m_I.resize(m_n);			// 各区域－价格指数 (price index)
	m_WR.resize(m_n);			// 各区域－工资率 (wage rate)
	m_NW.resize(m_n);			// 各区域－初始工资率
	m_RW.resize(m_n);			// 各区域－实际工资 (real wage)
	m_welf.resize(m_n);			// 各区域－福利 (welfare)

	double arw;
	double sum_lambda[9];
	double count_lambda[9];

	// 赋初值
	m_NW.assign(m_n, m_w0);				// 初始工资率赋值为0
	m_iphi.assign(m_n, m_phi / m_n);	// 各区域农村劳动力份额＝1/区域个数

	// 长期均衡
	for(int lcount = 0; lcount < m_longit; lcount++)
	{
		// 执行短期均衡
		m_sQuitinfo = ShortEqual();

		if(!m_sQuitinfo.isNormalQuit() || m_isWillAbort) {
			m_lQuitInfo = QuitInfo(false, lcount);
			CheckAndSetState( RS_Running, RS_Aborted );
			return;
		}

		// 长期均衡计算
		arw = 0.0;	// average real wage

		for (int i = 0; i < m_n; i++)
		{				
			m_RW[i] = m_WR[i] * pow(m_I[i], double(-m_delta));	// calculate real wage
			m_welf[i] = m_Y[i] * pow(m_I[i], double(-m_delta));	// calculate welfare
		}

		// calculate average real wage
		for (int i = 0; i < m_n; i++) {arw += m_RW[i] * m_lambda[0][i];}

		// calculate m_lambda[1]－第1次调整
		for (int i = 0; i < m_n; i++)
			m_lambda[1][i] = m_lambda[0][i] + m_sp * (m_RW[i] - arw);

		// calculate m_lambda[2]－第2次调整
		for (int i = 0; i < m_n; i++)
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
			for (int i = 0; i < m_n; i++)			// 计算各区域调整值的和
				sum_lambda[ilamb - 1] += m_lambda[ilamb - 1][i];

			count_lambda[ilamb - 1] = 0.0;		// 计算各区域调整值不等于0的个数
			for (int i = 0; i < m_n; i++)
			{
				if (m_lambda[ilamb - 1][i] == 0.0)
					count_lambda[ilamb - 1] += 1.0;
			}

			for (int i = 0; i < m_n; i++)			// 计算各区域的调整值
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

		for (int i = 0; i < m_n; i++)
			sum_lambda[7] += m_lambda[7][i];

		count_lambda[7] = 0;
		for (int i = 0; i < m_n; i++)
		{
			if (m_lambda[7][i] == 0.0)
				count_lambda[7] += 1;
		}
		for (int i = 0; i < m_n; i++)
		{
			if (m_lambda[7][i] <= 0.0)
				m_lambda[8][i] = 0.0;
			else
				m_lambda[8][i] = m_lambda[7][i] + (1.0 - sum_lambda[7]) / (m_n - count_lambda[7]);
		}

		// 将lambda8赋给lambda0
		m_lambda[0] = m_lambda[8];

		if(IsLongEqual()){
			m_lQuitInfo = QuitInfo(true, lcount);
			CheckAndSetState(RS_Running, RS_OK );
			return;
		}
	}// end long-run equilibrium

	m_lQuitInfo = QuitInfo(false, -1);
	CheckAndSetState( RS_Running, RS_Aborted );
}

bool NEGSimulator::IsLongEqual()
{
	for (int i = 0; i < m_n; i++)
	{
		if (m_lambda[0][i] == 0.0 && m_lambda[8][i] != 0.0){
			return false;
		}
		if (m_lambda[0][i] != 0.0 && m_lambda[8][i] == 0.0){
			return false;
		}
		if (m_lambda[0][i] != 0.0 && m_lambda[8][i] != 0.0){
			double ltemp = fabs((m_lambda[8][i] - m_lambda[0][i]) / m_lambda[0][i]);
			if (ltemp > m_sigma){
				return false;
			}
		}
	}
	return true;
}


//如果测试状态满足条件，则进行设置。该操作为原子操作。
bool NEGSimulator::CheckAndSetState( RunState precondition, RunState rs )
{
	mutex::scoped_lock lock(m_mutex);

	if( (precondition & m_state) != 0 ){
		m_state = rs;
		return true;
	}

	return false;
}


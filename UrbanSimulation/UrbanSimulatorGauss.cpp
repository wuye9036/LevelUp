#include "StdAfx.h"
#include ".\urbansimulatorgauss.h"

#include "StdAfx.h"
#include ".\urbansimulator.h"

double powd(double a, double b)
{
	if(abs(a) < 0.00000000001) return 0.0;
	return pow(a,b);
}

#define pow(a, b) powd(a, b)

UrbanSimulatorGauss::UrbanSimulatorGauss(void):	m_pThread(NULL),
																	m_isDone(false),
																	m_isRunning(false)
{
}

UrbanSimulatorGauss::~UrbanSimulatorGauss(void)
{
	delete m_pThread;
}

void UrbanSimulatorGauss::Init()
{
	m_folder = _T("");
	m_alpha = 0.08f;
	m_beta = 0.8f;
	m_delta = 0.4f;
	m_gamma = 0.4f;
	m_n = 109;
	m_L = 1.0f;
	m_phi = 1.0f;
	m_rho = 0.8f;
	m_sigma = 0.001f;
	m_sp = 0.5f;
	m_tc = 1.5;
	m_w0 = 1.0f;
	m_grdstep = 1;
	m_longit = 200;
	m_shortit = 500;
}

void UrbanSimulatorGauss::Calc()
{
	m_isDone = false;
	m_isRunning = true;
	if(m_pThread)
	{
		delete m_pThread;	
	}
	m_pThread = new boost::thread(boost::bind(&UrbanSimulatorGauss::CalcImpl,this));
}

void UrbanSimulatorGauss::CalcImpl()
{
	m_error.clear();

	FILE *padvantage,*ptransdist,*plog;
	string m_advantagename,m_transdistname;
	m_advantagename="\\geoadvantage.txt";
	m_advantagename=m_folder+m_advantagename;
	m_transdistname="\\transdist.txt";
	m_transdistname=m_folder+m_transdistname;

	string tempresult;
	FILE *presult;
	tempresult="\\result.txt";
	tempresult=m_folder+tempresult;

	char tempstring[260];
	int i,j,tempint;
	float tempfloat;
	double tempdouble;
	double m_ave, m_sum;


	//////////////////////////////////////////////////
	if((padvantage=fopen(m_advantagename.c_str(),"r"))==NULL)
	{
		//AfxMessageBox("打开advantage文件失败!");
		return;
	}
	else
	{
		fscanf(padvantage, "%d", &m_n);
		fclose(padvantage);
	}

	if((ptransdist=fopen(m_transdistname.c_str(),"r"))==NULL)
	{
		//AfxMessageBox("打开transdist文件失败!");
		return;
	}
	if((plog=fopen("i:\\log.txt","w"))==NULL)
	{
		//AfxMessageBox("写文件失败!");
		return;
	}

	fscanf(ptransdist,"%s",tempstring);
	for(i=0;i<m_n-1;i++)
	{
		fscanf(ptransdist,"%d",&tempint);
	}
	fscanf(ptransdist,"%d",&tempint);
	if(tempint!=m_n)
	{
		fclose(ptransdist);
		//AfxMessageBox("输入的n值和文件实际不符!");
		return;
	}
	if((presult=fopen(tempresult.c_str(),"w"))==NULL)
	{
		//AfxMessageBox("写文件失败!");
		return;
	}

	if((padvantage=fopen(m_advantagename.c_str(),"r"))==NULL){
		//AfxMessageBox("打开advantage文件失败!");
		fclose(ptransdist);
		return;
	} else {
		fscanf(padvantage, "%d", &m_n);
	}

	for(i=0;i<m_n;i++){
		fscanf(ptransdist,"%d",&tempint);
		fscanf(padvantage,"%d",&tempint);
		fscanf(padvantage,"%f",&tempfloat);
		m_G[i]=tempfloat;
		for(j=0;j<m_n;j++){
			fscanf(ptransdist,"%lf",&tempdouble);
			m_D(i,j) = pow(m_tc, tempdouble);
		}
	}

	double sum = 0.0;
	for(i = 0; i < m_n; ++i){
		sum += m_G[i];
	}

	m_lambda = m_G / sum;
	m_lambdan = m_lambda;

	SetPercentage(0.0f);
	/*
	** pancake economy program
	** (C) Copyright 2000, Charles van Marrewijk
	**
	** Purpose: computes the short run equilibrium in a 12 city setting of
	** the Geographical Economics model with congestion; geometry = pancake
	economy
	**
	** Solution method: iterative
	**
	** m_alpha = fixed cost
	** m_beta = variable cost
	** m_gamma = share of labor in manufacturing
	** m_rho = elasticity of substitution parameter
	** tau = congestion parameter
	** m_L = number of laborers = 1
	** m_delta = share of spending on manufactures
	** m_n = number of regions (put equal to 12 below)
	** m_tc = number of goods to be shipped 1 step to make sure 1 unit arrives
	** m_phi = distribution of immobile population
	** m_sigma = threshold value for differences in wages (short run =)
	** m_sigma = threshold value for differences in labor adjustment (long run =)
	** m_stap = maximum number of iterations
	** m_n=speed of adjustment
	**
	** (m_epsilon = 1/1-m_rho)
	** (A = parameter constant)
	** (B = parameter constant)
	**
	** we normalize such that m_beta=m_rho, m_alpha=m_gamma/m_epsilon, m_gamma=m_delta and m_L=1
	*/
	/* Initialization*/
	//阻碍参数 tau=0.1;
	//m_tc = 1.5;
	//m_sp = 2;
	/*normalizations and definitions of some parameters*/
	m_beta = m_rho;
	m_gamma = m_delta;
	double m_epsilon = 1 / (1 - m_rho);
	m_alpha = m_gamma / m_epsilon;
	m_L=1;

	ublas::vector<double> m_phi(m_n);
	for(int i = 0; i < m_n; ++i) {
		m_phi[i] = 1.0 / m_n;
	}

	double hulp0=1/m_epsilon;
	double hulp1=1-m_epsilon;
	double hulp2=1/hulp1;
	//double hulp3=1 - 0.1 * m_epsilon;
	/*
		运输成本矩阵为m_n行m_n列
		初始化流动劳动力m_n行矩阵lambdan＝1//m_n，m_lambda是计算过程矩阵
		m_Y、m_I是m_n行矩阵，初始值为1
		m_W=W0;
	*/
	ublas::vector<double> W0(m_n);
	ublas::vector<double> m_W(m_n);
	ublas::vector<double> m_W2(m_n);
	ublas::vector<double> realw(m_n);
	ublas::vector<double> dum(m_n);
	ublas::vector<double> m_Y(m_n);
	ublas::vector<double> m_I(m_n);
	ublas::vector<double> lambdah(m_n);
	numeric::ublas::vector<double> temp(m_n);

	//initial
	for(int i = 0; i < m_n; ++i){
		m_Y[i] = m_I[i] = W0[i] = realw[i] = 1.0;
	}
	/*distance*/

	//初始化不流动劳动力分布矩阵为1/区域个数
	//初始化名义工资W0、真实工资realw是m_n行矩阵，初始值为1
	bool equillong, equalshort, equalshortt;
	equillong = false;

	int ita = 1;
	while(ita <= m_longit)
	{
		m_W = W0;

		//执行短期均衡
		ShortEqual();

		m_W = m_W2;
		equalshortt &= equalshort;

		//printvec(m_I)
		for(int i = 0; i < m_n; ++i){
			temp[i] = pow(double(m_I[i]),  -double(m_delta));
			realw[i] = m_W[i] * temp[i]; 
		}

		printvec(realw)
		double avreal = inner_prod(m_lambda, realw);
		fprintf(plog, "%9.6f\n", avreal);
		double welfare = inner_prod(m_Y, temp);
		
		for(int i = 0; i < m_n; ++i) {
			lambdah[i] = m_sp * (realw[i]-avreal) * m_lambda[i];
			dum[i] = (abs(realw[i] - avreal) / avreal) > m_sigma ? 1 : 0;
		}

		//printvec(lambdah)
		//printvec(m_lambda)

		if(norm_1(dum) == 0) { equillong = true; break; }
		m_lambda = m_lambda + lambdah;
		double lambdas = norm_1(m_lambda);
		m_lambda = m_lambda / lambdas;
		++ita;
		SetPercentage(ita / double(m_longit));
	}

	if(!equillong)
	{
		m_error += "长期均衡不成立！";
	}
	if(!equalshortt)
	{
		m_error += "短期均衡不成立！";
	}
	/*
		存放前次计算的名义工资矩阵
		收入m_Y、价格指数m_I、名义工资率m_W
		（后次工资率－前次工资率）/前次工资率
		前次工资率赋给后次工作率
		真实工资率是m_n行矩阵
		lmabdah是m_n行劳动力流动量矩阵
		m_lambda存放计算的流动劳动力分布
		对流动劳动力分布求和，并且将流动劳动力分布归一
		假如短期均衡超出了迭代次数，则屏幕
		显示"No solution for the short-run
		equilibrium"
	*/

	///////////////////算法开始///////////////////////////////////////////////////////////////////
	for (int i=0; i<m_n; i++)
	{
		//fprintf(presult,"%d %.6f %.6f\n", (i+1), m_G[i], m_lambda[i]);
		fprintf(presult,"%d %.6f\n", (i+1), m_lambda[i]);
	}
	fclose(plog);
	fclose(presult);
	fclose(padvantage);
	fclose(ptransdist);

	//m_myProgress.SetPos(100);
	//SetCursor(LoadCursor(NULL,IDC_ARROW));
	//ReleaseCapture();

	FILE* fcheckg = fopen("m_I:\\check.txt", "w");
	FILE* fcheckd = fopen("i:\\tran.txt", "w");
	fprintf(fcheckd, "%8s", "ID");
	for(int i = 0; i < m_n; ++i)
	{
		fprintf(fcheckd, "%8d", i+1);
	}
	fprintf(fcheckd, "\n");
	for(int i = 0; i < m_n; ++i)
	{
		fprintf(fcheckg, "%d %.6f\n", i + 1, m_G[i]);
		fprintf(fcheckd, "%8d", i+1);
		for(int j = 0; j < m_n; ++j)
		{
			fprintf(fcheckd, "%8.5f", m_D(i, j));
		}
		fprintf(fcheckd, "\n");
	}
	fclose(fcheckg);
	fclose(fcheckd);


	SetDone(true);
	SetRunning(false);
}

pair<bool, int> UrbanSimulatorGauss::ShortEqual()
{
	int it = 1;
	bool equalshort = false;

	while (it <= m_shortit)
	{
		for(int i = 0; i < m_n; ++i){
			m_W2[i] = m_Y[i] = m_I[i] = 0.0;
		}

		m_Y = (element_prod(m_lambda, m_W) * m_gamma * m_L) + m_phi * ((1-m_gamma)*m_L);
		//printvec(m_Y)

		for(int r = 0; r < m_n; ++r){
			for(int s = 0; s < m_n; ++s){
				m_I[r] += m_lambda[s] * pow(m_D(r, s), hulp1)*pow(m_W[s], hulp1);
			}
			m_I[r] = pow(/*pow(m_lambda[r], hulp3)*/m_I[r], hulp2);
		}
		//printvec(m_I)

		for(int s = 0; s < m_n; ++s){
			for(int r = 0 ; r < m_n; ++r) {
				m_W2[s] += m_Y[r] * pow(m_D(r, s), hulp1) * pow(m_I[r], -hulp1);
			}
			m_W2[s] = /*pow(m_lambda[s], -0.1) */ pow(m_W2[s], hulp0);
		}
		//printvec(m_W2)
		//temp = element_div(m_W2 - m_W, m_W);
		for(int i = 0; i < temp.size(); ++i){
			dum[i] = abs((m_W2[i] - m_W[i])/m_W[i]) > m_sigma ? 1 : 0;
		}

		if(norm_1(dum) == 0) { equalshort = true; break; }
		m_W = m_W2;
		++it;
	}
}

bool UrbanSimulatorGauss::IsDone()
{
	//m_lock.lock();
	bool tmp = m_isDone;
	//m_lock.unlock();
	return tmp;
}

bool UrbanSimulatorGauss::StopCalc()
{
	//m_lock.lock();
	if (m_isRunning)
	{
		delete m_pThread;
		m_pThread = NULL;
	}
	m_isDone = false;
	m_isRunning = false;
	//m_lock.unlock();

	return true;
}

float UrbanSimulatorGauss::GetPercentage()
{
	//m_lock.lock();
	float tmp = m_percentage;
	if(!m_isRunning) tmp = 0.0f;
	if(m_isDone) tmp = 1.0f;
	//m_lock.unlock();
	return tmp;
}

void UrbanSimulatorGauss::SetPercentage(float v)
{
	//m_lock.lock();
	m_percentage = v;
	//m_lock.unlock();
}

void UrbanSimulatorGauss::SetDone(bool v)
{
	//m_lock.lock();
	m_isDone = v;
	//m_lock.unlock();
}

void UrbanSimulatorGauss::SetRunning(bool v)
{
	//m_lock.lock();
	m_isRunning = v;
	//m_lock.unlock();
}
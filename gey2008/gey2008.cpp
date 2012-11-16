// gey2008.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "UrbanSimulator.h"
#include <iostream>

using namespace boost;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	//desc.add_options()
	//	("help,h", "get help messages")
	//	("io-directory", value<string>(), "The Directory of Input Data.")
	//	("log-file", value<string>(), "Log File.")
	//	("alpha,a", value<double>(), "fixed cost")
	//	("beta,b", value<double>(), "variable cost")
	//	("delta,d", value<double>(), "share of spending on manufactures")
	//	("gamma,g", value<double>(), "share of labor in manufacturing")
	//	("L,L", value<double>(), "number of laborers")
	//	("phi,p", value<double>(), "distribution of immobile population")
	//	("rho,r", value<double>(), "elasticity of substitution parameter")
	//	("sigma,s", value<double>(), "stopping criterion")
	//	("speed", value<double>(), "speed of adjustment")
	//	("w0,w", value<double>(), "initial value")
	//	("longitercnt", value<double>(), "Long Iteration Count.")
	//	("shortitercnt", value<double>(), "Short Iteration Count.")
	//	("wscale", value<string>(), "Choose an initial wage scale function. Exp, Linear or None. Unsupported recently.")
	//	("distscale", value<string>(), "Choose and distance scale function. Exp, Linear or None. Unsupported recently.")
	//	;

	UrbanSimulator us;
	us.Init();

	system("pause");
	return 0;
}


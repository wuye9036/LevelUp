#pragma once

#include <string>

class Ecoparameters
{
public:
	void LoadFromXML(const std::string& xmlFileName);

	double	alpha;
	double	beta;
	double	delta;
	double	gamma;
	int		n;
	double	L;
	double	phi;
	double	rho;
	double	sigma;
	double	sp;
	double	tc;
	double	w0;
	long	grdstep;
	int		shortit;
	int		longit;
};
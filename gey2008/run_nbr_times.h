#pragma once

//#include <boost/functional.hpp>

class run_nbr_times
{
public:
	run_nbr_times(void);
	~run_nbr_times(void);
};

#define RUN_TIMES(run_nbr, func) {\
	static i = 1; if(i++ <= run_nbr) func;\
}

#define RUN_TIMES_RANGE(run_nbr1, run_nbr2, func){\
	static int i = 1; if(i <= run_nbr2 && i >= run_nbr1) {++i;func;}\
}
// PyNEGSimulator.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"

#include "NEGSimulator.h"

#include <boost/python.hpp>

typedef boost::python::list pylist;

class PyNEGSimulator: public NEGSimulator
{
public:
	PyNEGSimulator(){}
	PyNEGSimulator(const PyNEGSimulator&){}
	pylist Results(){
		pylist lst;
		for(int i = 0; i < m_lambda[0].size(); ++i){
			lst.append(m_lambda[0][i]);
		}
		return lst;
	}
};

BOOST_PYTHON_MODULE(PyNEGSimulator)
{
	boost::python::enum_<RunState>("RunState")
		.value("NotReady", RS_NotReady)
		.value("Ready", RS_Ready)
		.value("Aborted", RS_Aborted)
		.value("Runnning", RS_Running)
		.value("OK", RS_OK)
		.value("Any", RS_Any)
		;

	boost::python::class_<PyNEGSimulator>("Simulator", boost::python::init<>())
		.def("Run", &PyNEGSimulator::Run)
		.def("Abort", &PyNEGSimulator::Abort)

		.def("Progress", &PyNEGSimulator::Progress)
		.def("State", &PyNEGSimulator::State)
		.def("Results", &PyNEGSimulator::Results)
		
		.def("LoadEconomicParametersFile", &PyNEGSimulator::LoadEconomicParametersFile)
		.def("SetWeights", &PyNEGSimulator::LoadEconomicParametersFile)
		.def("SetDistanceMatrix", &PyNEGSimulator::SetDistanceMatrix)
		;
}
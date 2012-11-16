#pragma once

#include <fstream>
#include <vector>

using namespace std;

class LogFile
{
	fstream f;
public:
	LogFile(){
	}

	void open(const char* fname)
	{
		f.open(fname, ios::out);
	}

	~LogFile(void) {
		f.close();
	}

	template<class T> void Write(const T& rhs) {
		f << rhs;
	}

	template<class T> void Writeln(const T& rhs) {
		f << rhs << endl;
	}

	template <class T> void Write(const vector<T>& rhs) {
		for(size_t i = 0; i < rhs.size(); ++i) {
			f << rhs[i] << " ";
		}
		f << endl;
	}

	template <class T> void Write(const vector<T>& rhs, int m_n) {
		for(size_t i = 0; i < rhs.size() / m_n; ++i) {
			for(int j = 0; j < m_n; ++j) f << rhs[i*m_n+j] << " ";
			f << endl;
		}
	}

	template <class T> void Write(const T* p, int nbr_i, int nbr_j)
	{
		for(int i = 0; i < nbr_i; ++i)
		{
			for(int j = 0; j < nbr_j; ++j)
			{
				f << p[i * nbr_j + j] << " ";
			}
			f << endl;
		}
	}
};

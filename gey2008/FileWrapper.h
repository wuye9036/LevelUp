#pragma once

class FileWrapper
{
public:
	FileWrapper(const char* fname, const char* fm):f(NULL)
	{
		f = fopen(fname, fm);
		if(NULL == f) {
		}
	}

	~FileWrapper(void)
	{
		if(f){
			fclose(f);
		}
	}

	operator FILE*()
	{
		return f;
	}

private:
	FILE* f;
};

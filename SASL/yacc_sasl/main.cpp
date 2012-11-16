#include <iostream>

#include "ErrorReporters.h"
#include "Project.h"
#include "Makefile.h"

using namespace std;

int main(int argc, char** argv)
{
	project::initialize(h_preprocessor(), h_error_reporter(new stdout_error_reporter()));
	project::instance().parse();
    return 0;
}

#include "Context.h"

std::string& context::CurrentLine(){
	return currentLineString_;
}

int context::CurrentLineNo(){
	return 0;
}

void context::CurrentLineNo(int lineIdx){
}

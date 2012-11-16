#include <iostream>
#include <cstdio>

using namespace std;

int main(){
	float f;
	float total = 0.0f;
	while ( cin >> f ){
		total += f;
	}

	printf("$%.2f\n", total / 12);
	system("pause");
	return 0;
}
#include <iostream>

using namespace std;

int const physical_cycle = 23;
int const emotional_cycle = 28;
int const intellectual_cycle = 33;

int main(){
	int physical, emotional, intellectual, beginning;
	int case_idx = 0;

	while ( cin >> physical >> emotional >> intellectual >> beginning ){
		++case_idx;
		if ( physical == -1 ){
			break;
		}

		int day = intellectual % intellectual_cycle;
		while( day <= beginning ){
			day += intellectual_cycle;
		}

		while( true ){
			if( ( (day - physical) % physical_cycle == 0 ) && ( (day - emotional) % emotional_cycle == 0 ) ){
				printf("Case %d: the next triple peak occurs in %d days.\n", case_idx, day - beginning);
				break;
			}
			day += intellectual_cycle;
		}
	}
	return 0;
}
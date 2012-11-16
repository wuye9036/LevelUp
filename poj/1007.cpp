#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int measure( const string& str ){
	int ret = 0;
	for ( string::const_iterator cur_it = str.begin(); cur_it != str.end(); ++cur_it ){
		for( string::const_iterator follow_it = cur_it; follow_it != str.end(); ++ follow_it ){
			if ( *cur_it > *follow_it ){
				++ret;
			}
		}
	}
	return ret;
}

int main(){
	int length, count;
	cin >> length >> count;
	string dna;
	vector< pair<int, string> > dna_list;
	while ( cin >> dna ){
		int m = measure( dna );
		dna_list.push_back( make_pair(m, dna) );
	}
	stable_sort( dna_list.begin(), dna_list.end() );
	for ( int i = 0; i < dna_list.size(); ++i ){
		cout << dna_list[i].second << endl;
	}

	return 0;
}
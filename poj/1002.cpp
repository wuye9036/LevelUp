#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

struct CharNumberMap{
	CharNumberMap(){
		char char_seq[] = "ABCDEFGHIJKLMNOPRSTUVWXY";
		for( char i_ch = 0; i_ch < 24; ++i_ch ){
			char num_key = (i_ch / 3) + 2 + '0';
			cnMap.insert(  make_pair(char_seq[i_ch], num_key) );
		}
	}

	char translate( char ch ){
		return cnMap[ch];
	}

private:
	map<char, char> cnMap;
};

CharNumberMap char_num_map;

string normalize_tel_string( const string& tel ){
	string tel_string;
	for( string::const_iterator it_ch = tel.begin(); it_ch != tel.end(); ++it_ch ){
		if( *it_ch == '-' ){
			continue;
		}
		if ( '0' <= *it_ch && *it_ch <= '9' ){
			tel_string.push_back( *it_ch );
		} else {
			tel_string.push_back( char_num_map.translate( *it_ch ) );
		}
	}
	return tel_string;
}

void incremental_count( map<string, int>& count_map, const string& tel ){
	if ( count_map.find( tel ) == count_map.end() ){
		count_map.insert( make_pair(tel, 1) );
	} else {
		++count_map[tel];
	}
}

vector< pair<string, int> > get_sorted_tels( const map<string, int>& count_map ){
	vector<string> tels;
	for( map<string, int>::const_iterator it = count_map.begin(); it != count_map.end(); ++it ){
		if (it -> second > 1){
			tels.push_back( it->first);
		}
	}
	stable_sort( tels.begin(), tels.end() );

	vector< pair<string, int> > ret;
	for( vector<string>::iterator it = tels.begin(); it != tels.end(); ++it ){
		ret.push_back( make_pair( *it, count_map.find(*it)->second ) );
	}

	return ret;
}

void print_result( const vector< pair<string, int> >& result ){
	if( result.size() == 0 ){
		cout << "No duplicates.";
		return;
	}

	for( int i = 0; i < result.size(); ++i ){
		cout << result[i].first.substr(0, 3) << "-" << result[i].first.substr(3, 4) << " " << result[i].second << endl;
	}
}

int main(){
	int line_count = 0;
	cin >> line_count;
	string s;
	map<string, int> count_map;
	while ( cin >> s ){
		incremental_count( count_map, normalize_tel_string( s ) );
	}
	print_result( get_sorted_tels( count_map ) );
	return 0;
}
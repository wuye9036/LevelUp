#pragma once

#include <ostream>
#include <string>
#include <vector>

using namespace std;

class FixedPointFloat{
	friend ostream& operator << ( ostream& o, const LargeInt& v);
	std::vector<char> value;
	int dotPosition;

public:
	LargeInt( const string& lit ){
		for( string::const_reverse_iterator ch_it = lit.rbegin(); ch_lit != lit.rend(); ++ch_lit ){
			if ( *ch_lit == '.' ){
				dotPosition = distance ( ch_lit, lit.begin() );
			} else {
				value.push_back( *ch_it - '0' );
			}
		}
	}

	void normalize(){
		for( int i=0; i < value.size() - 1; ++i ){
			value[i+1] += ( value[i] / 10 );
			value[i] %= 10;
		}
		if ( !value.empty() && value.back() > 10 ){
			char new_value = value.back() / 10;
			value.back() /= 10;
			value.push_back( new_value );
		}
	}

	FixedPointFloat& operator *= ( int n ){
		for ( int i = 0; i < value.size(); ++i ){
			value[i] *= n;
		}
		normalize();
	}

	FixedPointFloat operator * ( const FixedPointFloat& rhs ){
		FixedPointFloat ret;
		ret.value.resize( value.size() + rhs.value.size() )
		for ( int i = 0; i < value.size(); ++i ){
			for ( int j = 0; j < rhs.value.size(); ++j ){
				ret.value[i+j] += ( value[i] * rhs.value[j] );
			}
			normalize();
		}
		ret.dotPosition = dotPosition + rhs.dotPosition;
	}
};



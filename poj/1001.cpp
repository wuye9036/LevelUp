#include <iostream>
#include <string>
#include <vector>

using namespace std;

class FixedPointFloat{
public:
	std::vector<char> value;
	int dotPosition;

	FixedPointFloat( const string& lit ){
		dotPosition = 0;
		for( string::const_reverse_iterator ch_it = lit.rbegin(); ch_it != lit.rend(); ++ch_it ){
			if ( *ch_it == '.' ){
				dotPosition = distance ( lit.rbegin(), ch_it );
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
		if ( !value.empty() && value.back() >= 10 ){
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
		FixedPointFloat ret("0");
		ret.value.resize( value.size() + rhs.value.size() );
		for ( int i = 0; i < value.size(); ++i ){
			for ( int j = 0; j < rhs.value.size(); ++j ){
				ret.value[i+j] += ( value[i] * rhs.value[j] );
			}
			ret.normalize();
		}
		ret.dotPosition = dotPosition + rhs.dotPosition;
		return ret;
	}

	FixedPointFloat exp( int n ){
		if ( n == 0 ){
			return FixedPointFloat("1");
		}

		if ( n == 1 ){
			return *this;
		}

		if ( n % 2 == 0 ){
			return exp( n / 2 ) * exp( n / 2 );
		} else {
			return exp ( n / 2 ) * exp ( n / 2 ) * (*this);
		}
	}
};

ostream& operator << ( ostream& o, const FixedPointFloat& v){
	bool do_not_print_0 = true;
	for ( int i = int( v.value.size() ) - 1; i >= v.dotPosition; --i ){
		if ( int(v.value[i]) != 0 ){
			do_not_print_0 = false;
		}
		if( int(v.value[i]) != 0 || !do_not_print_0 ){
			o << (int)v.value[i];
		}
	}

	int tail_zero_count = 0;
	for( int i = 0; i < v.dotPosition; ++i ){
		if( int(v.value[i]) != 0 ){
			break;
		} else {
			++tail_zero_count;
		}
	}

	if(v.dotPosition - tail_zero_count == 0){
		return o;
	}

	o << ".";

	for( int i = v.dotPosition - 1; i >= tail_zero_count; --i ){
		o << (int)v.value[i];
	}

	return o;
}
int main()
{
	string s;
	int n;
	while ( cin >> s >> n ){
		cout << FixedPointFloat(s).exp( n ) << endl;
	}
	return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

vector<int> possibility_stick_length( int total_length ){
	vector<int> ret;
	for( int i = 1; i <= total_length / 2; ++i ){
		if ( total_length % i == 0 ){
			ret.push_back ( i );
		}
	}
	return ret;
	random_shuffle( ret.begin(), ret.end() );
}


struct stick_usage_state{
	match_state(
		const vector<int> segments
		int length,
		int count
		): segments( segments ), length( length ), count( count )
	{}

	int alloc_free_segment(int start){
		for (int i = start; i < usage.size(); ++i){
			if ( !usage[i] ){
				usage[i] = true;
				return i;
			}
		}
		return -1;
	}

	int alloc_shorter_free_segment(int start){
		if (start == 0){
			return 0;
		}
		for ( int i = start; i < usage.size(); ++i ){
			if ( !usage[i] && segments[i] < segments[i-1] ){
				usage[i] = true;
				return i;
			}
		}
		return -1;
	}

	void free_segment( int id ){
		if ( id == -1 ){
			return;
		}
		usage[id] = false;
	}

	int stick_length(){
		return length;
	}
	int stick_count(){
		return count;
	}

	int segment_length( int i ){
		return segments[i];
	}

private:
	int length;
	int count;
	vector<bool> usage;
	vector<int> segments;
};

class segment_match_state{
public:
	segment_match_state( stick_usage_state* state ): stick_state(state) {
	}

	void initialize(){
		used_segment_ids.push_back( stick_state->alloc_free_segment( used_segment_ids.back() ) );
		after_push();
	}

	void next(){
		if( used_segment_ids.size() == 1 ){
			before_pop();
			used_segment_ids.back() == -1;
		} else {
			before_pop();
			used_segment_ids.back() = stick_state->alloc_shorter_free_segment( used_segment_ids.back() );
			after_push();
		}
	}

	bool can_search_deep(){
		return total_length < stick_state->length;
	}

	void deep_first(){
		used_segment_ids.push_back( stick_state->next_free_segment( used_segment_ids.back() ) );
		after_push();
	}

	void pop(){
		before_pop();
		used_segment_ids.pop();
	}

	bool can_termiate(){
		return total_length == state->stick_length();
	}

	bool is_end(){
		return used_segment_ids.back() == -1;
	}

	bool is_matched(){
		return total_length == state->stick_length();
	}

private:
	void before_pop(){
		total_length -= stick_state->segment_length( used_segment_ids.back() );
		stick_state->free_segment( used_segment_ids.back() );
	}

	void after_push(){
		total_length += stick_state->segment_length( used_segment_ids.back() );
	}

	int total_length;
	vector<int> used_segment_ids;
	stick_usage_state* stick_state;
};

class stick_matched_state{

};

int main(){
	while ( true ){
		int stick_count;
		
		cin >> stick_count;
		if ( stick_count == 0 ){
			return 0;
		}

		vector< int > sticks( stick_count );
		vector< char > usage;
		usage.resize( stick_count, 0 );
		int stick_length;
		int total_length = 0;
		for ( int i = 0; i < stick_count; ++i ){
			cin >> stick_length;
			sticks[i] = stick_length;
			total_length += stick_length;
		}

		
		stable_sort( sticks.begin(), sticks.end() );
		reverse( sticks.begin(), sticks.end() );

		if ( stick_count == 1 ){
			cout << total_length << endl;
			continue;
		}

		vector<int> possible_length = possibility_stick_length( total_length );
		for( int i = 0; i < possible_length.size(); ++i ){
			if ( possible_length[i] < sticks[0] ){
				continue;
			}
			if ( package( sticks, usage, possible_length[i] ) ){
				cout << possible_length[i] << endl;
				break;
			}
		}
	}
}


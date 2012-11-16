#pragma once

#include <cassert>

// shareable_state
//	void next();
//	bool can_search_deep();
//	
//
//

template <typename StateT>
class shared_state_iterator{
public:
	shared_state_iterator( StateT* owner ): owner( owner ){}
	shared_state_iterator( const shared_state_iterator& rhs ): owner( rhs.owner ){}
	shared_state_iterator& operator = (const shared_state_iterator& rhs ){
		assert( rhs.owner == this->owner );
		return *this;
	}

	shared_state_iterator next(){
		owner->next();
		return *this;
	}

	bool can_search_deep(){
		return owner->can_search_deep();
	}

	shared_state_iterator deep_first(){
		owner->deep_first();
		return *this;
	}

	void pop(){
		owner->pop();
	}

	bool can_termiate(){
		return owner->can_terminate();
	}

	bool is_end(){
		owner->is_end();
	}

private:
	StateT* owner;
};

template < typename StateIteratorT > 
struct deep_first_search{
	DeepFirstSearch();
	vector< StateIteratorT > state_stack;

public:
	void reset( StateIteratorT& start ){
		state_stack.clear();
		state_stack.push_back( start );
	}

	void search( ){
		while(true){
			StateIteratorT& current_state = state_stack.back();

			if ( current_state.is_end() ){
				current_state.pop();
				state_stack.pop();
				if ( state_stack.empty() ){
					return;
				} else {
					current_state = state_stack.back();
					state_stack.back() = current_state.next();
					continue;
				}
			} else if ( current_state.can_termiate() ){
				return;
			} else if ( current_state.can_search_deep() ){
				state_stack.push_back( current_state.deep_first() );
			} else {
				state_stack.back() = current_state.next();
			}
		}
	}

	const vector<StateIteratorT>& current_states(){
		return state_stack;
	}
};
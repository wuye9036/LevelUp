#include "LayerInfo.h"
#include <algorithm>

using namespace std;

void LayerInfo::reset()
{
	legal_sibdir_positions_.clear();
	pardir_min_dists_.clear();
}

float LayerInfo::legal_sibdir_pos( int level ) const
{
	if (legal_sibdir_positions_.size() <= level){
		return 0.0f;
	}

	return legal_sibdir_positions_[level];
}

void LayerInfo::legal_sibdir_pos( int level, float pos )
{
	if (legal_sibdir_positions_.size() <= level){
		legal_sibdir_positions_.resize(level+1, 0.0f);
	}

	legal_sibdir_positions_[level] = max(pos, legal_sibdir_positions_[level]);
}

float LayerInfo::pardir_min_distance( int level ) const
{
	if (pardir_min_dists_.size() <= level){
		return 0.0f;
	}
	return pardir_min_dists_[level];
}

void LayerInfo::pardir_min_distance( int level, float distance )
{
	if (pardir_min_dists_.size() <= level){
		pardir_min_dists_.resize(level+1, 0.0f);
		pardir_min_dists_[level] = distance;
	} else {
		pardir_min_dists_[level] = max(pardir_min_dists_[level], distance);
	}
}
#pragma once

#include <vector>

class LayerInfo
{
	std::vector<float>	legal_sibdir_positions_;
	std::vector<float>	pardir_min_dists_;
public:
	void reset();

	float legal_sibdir_pos(int level) const;
	void legal_sibdir_pos(int level, float pos);

	float pardir_min_distance(int level) const;
	void pardir_min_distance(int level, float distance);

	size_t count(){
		return legal_sibdir_positions_.size();
	}
};
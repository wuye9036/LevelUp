#include <iostream>
#include <vector>
#include <limits>
#include <list>
#include <fstream>

using namespace std;

class path_finder
{
	vector<vector<int> > adj_matrix_;
	vector<int>	prenodes_;
	vector<int> costs_;
	vector<bool> is_accessed_;
	int			n_verts_;

	int find_min_cost_id()
	{
		int min_cost = numeric_limits<int>::max();
		int min_cost_id = -1;

		for(int i_vert = 0; i_vert < n_verts_; ++i_vert)
		{
			if (is_accessed_[i_vert]){
				continue;
			}
			if (costs_[i_vert] < min_cost){
				min_cost_id = i_vert;
				min_cost = costs_[i_vert];
			}
		}

		return min_cost_id;
	}

	void relax(int src, int dest)
	{
		if (adj_matrix_[src][dest] == -1){
			return;
		}

		int evaluated_cost = adj_matrix_[src][dest] + costs_[src];

		if (evaluated_cost < costs_[dest]){
			costs_[dest] = evaluated_cost;
			prenodes_[dest] = src;
			is_accessed_[dest] = false;
		}
	}

	void input_data(istream& is, int n_edges){
		for (int i_edge = 0; i_edge < n_edges; ++i_edge)
		{
			int edge_id, src_vert_id, dest_vert_id;
			is >> edge_id >> src_vert_id >> dest_vert_id;
			is >> adj_matrix_[src_vert_id][dest_vert_id];
			adj_matrix_[dest_vert_id][src_vert_id] = adj_matrix_[src_vert_id][dest_vert_id];
		}
	}

public:
	static path_finder* create_path_finder(const string& input_data_file_name)
	{
		fstream f(input_data_file_name.c_str(), ios::in);
		int n_verts, n_edges;
		f >> n_verts >> n_edges;
		path_finder* ret_path_finder = new path_finder(n_verts);
		ret_path_finder->input_data(f, n_edges);
		return ret_path_finder;
	}

	path_finder(int nverts):
		adj_matrix_(nverts, vector<int>(nverts, -1)),
		prenodes_(nverts, -1),
		costs_(nverts, numeric_limits<int>::max()),
		is_accessed_(nverts, false),
		n_verts_(nverts)
	{
		costs_[0] = 0;
		prenodes_[0] = 0;
	}

	void find()
	{
		//dijkstra algorithm's body
		int min_cost_id;
		while ((min_cost_id = find_min_cost_id()) != -1)
		{
			is_accessed_[min_cost_id] = true;
			for (int i_dest = 0; i_dest < n_verts_; ++i_dest){
				relax(min_cost_id, i_dest);
			}
		}
	}

	void print(ostream& os)
	{
		//bfs output
		list<int> access_seq;
		vector<bool> is_output(n_verts_, false);

		access_seq.push_front(0);
		int cur_id = 0;
		is_output[0] = true;

		while(!access_seq.empty())
		{
			cur_id = access_seq.back();
			access_seq.pop_back();

			os << cur_id << "(" << prenodes_[cur_id] << ")" << " ";

			for (int i_dest = 0; i_dest < n_verts_; ++i_dest){
				if ((!is_output[i_dest]) && (adj_matrix_[cur_id][i_dest] > 0) )
				{
					is_output[i_dest] = true;
					access_seq.push_front(i_dest);
				}
			}
		}
	}
};

int main()
{
	auto_ptr<path_finder> pf(path_finder::create_path_finder("input.txt"));
	pf->find();
	pf->print(cout);
    return 0;
}

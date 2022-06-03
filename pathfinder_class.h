#ifndef PATHFINDER_CLASS_H
#define PATHFINDER_CLASS_H

#include "base_class.h"

class PathfinderClass : public BaseClass
{
public:

	PathfinderClass(string obj_name, BaseClass* parent_ptr);

	void TrySignal(string path, string message) override;

	void TryHandler(string path, string message) override;
private:

	vector<string> towers_list_ = {};

	string phones_info = "";

	struct edge_struct
	{
		size_t a_point = 0, b_point = 0, edge_weight = 1;
	};

	vector<edge_struct> edges_list_ = {};

	struct graph_info
	{
		vector<size_t> curr_road = {}, shortest_road = {};

		vector<bool> included_points = {};

		size_t start_point = 0, finish_point = 0, 
			shortest_road_lengh = 0, curr_road_length = 0;

		size_t points_number = 0;
	};

	graph_info graph_info_;

	bool SetupPathfinder();
	bool SetupGraph();

	void FindPointsNumber();
	size_t FindPathExistance(size_t a_point, size_t b_point);

	void DoNextSearchStep(size_t start_point, size_t finish_point, 
		size_t next_point_index, bool& way_is_found);
	bool BreadthFirstSearch();

	string get_graph_path();

	void Clear();
};

#endif // !PATHFINDER_CLASS_H
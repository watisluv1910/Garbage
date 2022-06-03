#include "pathfinder_class.h"
#include "tower_struct.h"

#include <sstream>

PathfinderClass::PathfinderClass(string obj_name, BaseClass* parent_ptr)
	: BaseClass(obj_name, parent_ptr)
{
	set_class_number(4);
}

void PathfinderClass::TrySignal(string path, string message)
{
	return;
}

void PathfinderClass::TryHandler(string path, string message)
{
	if (message.find("Tower info: ") != string::npos)
	{
		EraseSubstring(message, "Tower info: ");

		this->towers_list_.push_back(message);
	}
	else if (message.find("Phones info: ") != string::npos) // From
	{
		EraseSubstring(message, "Phones info: ");

		this->phones_info = message;
	}
	else if (message.find("SYSTEM_START_SEARCH") != string::npos)
	{
		if (!SetupPathfinder())
		{
			Clear();

			this->SetEmittion("SYSTEM_OUTPUT The mobile network is overloaded"); // For Controller (for Screen)
			return;
		}
		else if (!BreadthFirstSearch())
		{
			Clear();

			this->SetEmittion("SYSTEM_OUTPUT The mobile network is overloaded"); // For Controller (for Screen)
			return;
		}
		string graph_path = get_graph_path();

		Clear();

		this->SetEmittion("SYSTEM_UPDATE_TOWERS " + graph_path); // For Controller (for tower)
	}

	return;
}

bool PathfinderClass::SetupPathfinder()
{
	// Setting up starting and finishing points:
	std::stringstream stream(phones_info);
	size_t temp_var = 0;

	for (size_t i = 0; i < std::count(phones_info.begin(), phones_info.end(), ' ') + 1; i++)
	{
		stream >> temp_var;

		switch (i)
		{
		case 1:
			graph_info_.start_point = temp_var;
			break;
		case 3:
			graph_info_.finish_point = temp_var;
			break;
		}
	}

	if (!SetupGraph())
	{
		return false;
	}
	
	return true;
}

bool PathfinderClass::SetupGraph()
{
	// Setting up graph edges:
	for (auto& tower : towers_list_)
	{
		std::stringstream stream(tower);
		tower_struct temp_tower;

		stream >> temp_tower.tower_number;
		stream >> temp_tower.curr_calls_number;
		stream >> temp_tower.max_calls_number;

		if (temp_tower.curr_calls_number >= temp_tower.max_calls_number)
		{
			continue;
		}
		else
		{
			size_t current_neighboring_tower = 0;

			while (stream >> current_neighboring_tower)
			{
				if (current_neighboring_tower >= temp_tower.tower_number)
				{
					edge_struct curr_edge;
					curr_edge.a_point = temp_tower.tower_number;
					curr_edge.b_point = current_neighboring_tower;
					edges_list_.push_back(curr_edge);
				}
				else
				{
					continue;
				}
			}
		}
	}

	if (edges_list_.empty())
	{
		return false;
	}
	
	return true;
}

void PathfinderClass::FindPointsNumber()
{
	size_t points_number = 0;

	for (auto& edge : edges_list_)
	{
		if (std::max(edge.a_point, edge.b_point) > points_number)
		{
			points_number = std::max(edge.a_point, edge.b_point);
		}
	}

	graph_info_.points_number = points_number;
}

size_t PathfinderClass::FindPathExistance(size_t a_point, size_t b_point)
{
	for (size_t i = 0; i < edges_list_.size(); i++)
	{
		if (edges_list_.at(i).a_point == a_point && edges_list_.at(i).b_point == b_point
			|| edges_list_.at(i).a_point == b_point && edges_list_.at(i).b_point == a_point)
		{
			return edges_list_.at(i).edge_weight;
		}
	}

	return 0;
}

void PathfinderClass::DoNextSearchStep(size_t start_point, 
	size_t finish_point, size_t next_point_index, bool& way_is_found)
{
	if (start_point == finish_point)
	{
		graph_info_.shortest_road_lengh = graph_info_.curr_road_length;

		graph_info_.shortest_road.resize(next_point_index - 1);

		for (size_t i = 0; i < graph_info_.shortest_road.size(); i++)
		{
			graph_info_.shortest_road.at(i) = graph_info_.curr_road.at(i);
		}

		way_is_found = true;
	}
	else
	{
		for (size_t next_point = 1; next_point <= graph_info_.points_number; next_point++)
		{
			size_t temp_path_length = FindPathExistance(start_point, next_point);

			if (temp_path_length && !graph_info_.included_points.at(next_point - 1) && 
				(!graph_info_.shortest_road_lengh || graph_info_.curr_road_length + 
					temp_path_length < graph_info_.shortest_road_lengh))
			{
				graph_info_.curr_road.push_back(next_point);
				graph_info_.included_points.at(next_point - 1) = true;
				graph_info_.curr_road_length += temp_path_length;

				DoNextSearchStep(next_point, finish_point, next_point_index + 1, way_is_found);

				graph_info_.curr_road.erase(graph_info_.curr_road.begin() + next_point_index - 1);
				graph_info_.included_points.at(next_point - 1) = false;
				graph_info_.curr_road_length -= temp_path_length;
			}
		}
	}
}

bool PathfinderClass::BreadthFirstSearch()
{
	FindPointsNumber();

	graph_info_.curr_road.push_back(graph_info_.start_point);

	graph_info_.included_points.resize(graph_info_.points_number);

	graph_info_.included_points.at(graph_info_.start_point - 1) = true;

	bool way_is_found = false;

	DoNextSearchStep(graph_info_.start_point, graph_info_.finish_point, 2, way_is_found);

	return way_is_found;
}

string PathfinderClass::get_graph_path()
{
	string path = "";

	for (auto& point : graph_info_.shortest_road)
	{
		path += std::to_string(point) + " ";
	}

	path.resize(path.length() - 1);

	return path;
}

void PathfinderClass::Clear()
{
	towers_list_.clear();
	edges_list_.clear();
	phones_info.clear();
	graph_info_ = graph_info();
}

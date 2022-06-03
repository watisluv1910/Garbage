#include "tower_class.h"

#include <sstream>

TowerClass::TowerClass(string obj_name, BaseClass* parent_ptr)
	: BaseClass(obj_name, parent_ptr)
{
	set_class_number(5);
}

void TowerClass::TrySignal(string path, string message)
{
	if (message.find("TOWER:PHONE") != string::npos)
	{
		if (message.find("Communication request") != string::npos) // TODO
		{
			ClearTowerStats();

			for (size_t i = 0; i < towers_list_.size(); i++)
			{
				this->SetEmittion("Tower info: " +
					towers_list_.at(i).tower_stats.insert(towers_list_.at(i).tower_stats.find_first_of(" "),
						" " + std::to_string(towers_list_.at(i).curr_calls_number))); // For Pathfinder
			}
		}
	}
	return;
}

void TowerClass::TryHandler(string path, string message)
{
	if (isdigit(message.front()) && std::count(message.begin(), message.end(), ' ') > 1)
	{
		SetupTower(message);
	}
	else if (message == "End of the communication tower system")
	{
		this->is_ready_to_work_ = true;
	}
	else if (message == "Phones are ready to work" && this->is_ready_to_work_)
	{
		this->SetEmittion("SYSTEM_OUTPUT Ready to work"); // For Screen
	}
	else if (message.find("CONTROLLER:TOWER") != string::npos)
	{
		EraseSubstring(message, "CONTROLLER:TOWER ");

		if (message.find("Communication request") != string::npos)
		{
			this->SetEmittion("TOWER:PHONE " + message); // For Phone
		}
		else if (message.find("Display the system status") != string::npos)
		{
			for (size_t i = 0; i < towers_list_.size(); i++)
			{
				this->SetEmittion("SYSTEM_OUTPUT Communication tower system " + get_tower_stats(i));
			}
		}
	}
	else if (message.find("CONSOLE:TOWER") != string::npos)
	{
		EraseSubstring(message, "CONSOLE:TOWER ");

		if (message.find("Display initial tower data") != string::npos)
		{
			EraseSubstring(message, "Display initial tower data at level ");

			string tree_level_space; // Defines the identation for the tree level

			tree_level_space.append(4U * std::stoull(message), ' ');

			for (auto& tower : towers_list_)
			{
				this->SetEmittion("SYSTEM_OUTPUT TREE_DATA " + 
					tree_level_space + tower.tower_stats); // For Screen
			}
		}
	}
	else if (message.find("Phones info") != string::npos)
	{
		this->SetEmittion(message); // For Pathfinder
	}
	else if (message.find("TREE_DATA") != string::npos)
	{
		this->SetEmittion(message);
	}
	else if (message.find("SYSTEM_UPDATE_TOWERS") != string::npos)
	{
		UpdateTowers(message);
	}
	else if (message.find("SYSTEM_ROLLBACK_TOWERS") != string::npos)
	{
		UpdateTowers(message, "ROLLBACK");
	}

	return;
}

void TowerClass::SetupTower(string message)
{
	std::stringstream stream(message);
	towers_list_.resize(towers_list_.size() + 1);

	stream >> towers_list_.back().tower_number;
	stream >> towers_list_.back().max_calls_number;

	towers_list_.back().tower_stats = message.insert(message.find_first_of(" ") + 1, "0 ");

	size_t neighboring_tower_number = 0;

	while (stream >> neighboring_tower_number)
	{
		towers_list_.back().neighboring_towers_list.push_back(neighboring_tower_number);
	}
}

void TowerClass::ClearTowerStats()
{
	for (size_t index = 0; index < towers_list_.size(); index++)
	{
		vector<string> temp_vec = ParseString(towers_list_.at(index).tower_stats, " ");

		towers_list_.at(index).tower_stats.clear();

		for (size_t j = 0; j < temp_vec.size(); j++)
		{
			if (j != 1)
			{
				towers_list_.at(index).tower_stats += temp_vec.at(j) + " ";
			}
		}

		towers_list_.at(index).tower_stats.resize(towers_list_.at(index).tower_stats.length() - 1);
	}
}

void TowerClass::UpdateTowers(string message, const string direction)
{
	if (direction == "UPDATE")
	{
		EraseSubstring(message, "SYSTEM_UPDATE_TOWERS ");
	}
	else
	{
		EraseSubstring(message, "SYSTEM_ROLLBACK_TOWERS ");
	}

	std::stringstream stream(message);
	size_t curr_tower = 0;

	while (stream >> curr_tower)
	{
		for (size_t i = 0; i < towers_list_.size(); i++)
		{
			if (towers_list_.at(i).tower_number == curr_tower)
			{
				if (direction == "UPDATE")
				{
					towers_list_.at(i).curr_calls_number++;
				}
				else
				{
					towers_list_.at(i).curr_calls_number--;
				}
			}
		}
	}
}

string TowerClass::get_tower_stats(size_t index)
{
	string temp_string = "";

	temp_string += std::to_string(towers_list_.at(index).tower_number) + " ";
	temp_string += std::to_string(towers_list_.at(index).max_calls_number) + " ";
	temp_string += std::to_string(towers_list_.at(index).curr_calls_number);

	return temp_string;
}

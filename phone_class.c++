#include "phone_class.h"

#include <sstream>

PhoneClass::PhoneClass(string obj_name, BaseClass* parent_ptr)
	: BaseClass(obj_name, parent_ptr)
{
	set_class_number(6);
}

void PhoneClass::TrySignal(string path, string message)
{
	return;
}

void PhoneClass::TryHandler(string path, string message)
{
	if (isdigit(message.front()) && std::count(message.begin(), message.end(), ' ') == 1)
	{
		SetupPhone(message);
	}
	else if (message == "End of information about phones")
	{
		this->SetEmittion("Phones are ready to work"); // For Tower
	}
	else if (message.find("TOWER:PHONE") != string::npos)
	{
		EraseSubstring(message, "TOWER:PHONE ");

		if (message.find("Communication request") != string::npos)
		{
			this->SetEmittion("Phones info: " + get_phones_info(message)); // For Tower -> For Pathfinder
		}
	}
	else if (message.find("CONSOLE:PHONE") != string::npos)
	{
		EraseSubstring(message, "CONSOLE:PHONE ");

		if (message.find("Display initial phone data") != string::npos)
		{
			EraseSubstring(message, "Display initial phone data at level ");

			string tree_level_space; // Defines the identation for the tree level

			tree_level_space.append(4U * std::stoull(message), ' ');

			for (auto& phone : phones_list_)
			{
				this->SetEmittion("SYSTEM_OUTPUT TREE_DATA " + 
					tree_level_space + phone.phone_stats); // For Screen
			}
		}
	}

	return;
}

void PhoneClass::SetupPhone(string message)
{
	phones_list_.resize(phones_list_.size() + 1);

	phones_list_.back().phone_number = message.substr(0, message.find_first_of(' '));

	phones_list_.back().connected_tower_number = message.back() - '0';

	phones_list_.back().phone_stats = message;
}

string PhoneClass::get_phones_info(string message)
{
	string phones_info = "";

	EraseSubstring(message, "Communication request ");

	for (size_t i = 0; i < 2; i++)
	{
		string temp_number = message.substr(0, message.find_first_of(" "));

		for (size_t j = 0; j < phones_list_.size(); j++)
		{
			if (phones_list_.at(j).phone_number == temp_number)
			{
				phones_info += phones_list_.at(j).phone_stats + " ";
				break;
			}
		}

		EraseSubstring(message, temp_number + " ");
	}

	return phones_info + message;
}

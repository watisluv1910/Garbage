#include "controller_class.h"

#include <sstream>
#include <chrono>
#include <thread>

ControllerClass::ControllerClass(string obj_name, BaseClass* parent_ptr)
	: BaseClass(obj_name, parent_ptr)
{
	set_class_number(3);
}

void ControllerClass::TrySignal(string path, string message)
{
	return;
}

void ControllerClass::TryHandler(string path, string message)
{
	if (message.find("Communication request") != string::npos) // Message from Console
	{
		std::this_thread::sleep_for(std::chrono::seconds(10));

		UpdateConversations();

		bool caller_is_busy = false;

		if (IsBusy(message, caller_is_busy))
		{
			if (!caller_is_busy)
			{
				this->SetEmittion("SYSTEM_OUTPUT The subscriber is busy"); // For Screen
			}
			return;
		}

		set_temp_connection(message);

		this->SetEmittion("CONTROLLER:TOWER " + message); // For Tower
		this->SetEmittion("SYSTEM_START_SEARCH"); // For Pathfinder
	}
	else if (message.find("SYSTEM_UPDATE_TOWERS") != string::npos) // Message from Pathfinder
	{
		temp_connection.occupied_towers = get_occupied_towers(message);

		conversations_list_.push_back(temp_connection);

		this->SetEmittion(message); // For Tower
	}
	else if (message.find("Display the system status") != string::npos)
	{
		std::this_thread::sleep_for(std::chrono::seconds(10));

		UpdateConversations();

		this->SetEmittion("CONTROLLER:TOWER " + message);

		if (conversations_list_.size() > 1)
		{
			SortConversations();
		}
		
		for (size_t i = 0; i < conversations_list_.size(); i++)
		{
			this->SetEmittion("SYSTEM_OUTPUT " + get_conversation_stats(i));
		}
	}
	else if (message.find("SHOWTREE") != string::npos)
	{
		this->get_head_obj()->ShowTree("with_readiness");
		exit(0);
	}
	else if (message.find("SYSTEM_OUTPUT") != string::npos) // Error message from Pathfinder
	{
		UpdateConversations();

		this->SetEmittion(message); // For Sreen
	}
	return;
}

bool ControllerClass::IsBusy(string message, bool& respondent_is_busy)
{
	EraseSubstring(message, "Communication request ");

	bool conversation_isnot_possible = false;

	for (size_t i = 0; i < conversations_list_.size(); i++)
	{
		if (message.find(conversations_list_.at(i).caller_phone) != string::npos)
		{
			conversation_isnot_possible = true;

			respondent_is_busy = true;
		}
		if (message.find(conversations_list_.at(i).respondent_phone) != string::npos)
		{
			conversation_isnot_possible = true;
		}
	}
	return conversation_isnot_possible;
}

void ControllerClass::set_temp_connection(string message)
{
	EraseSubstring(message, "Communication request ");

	vector<string> parsed_message = ParseString(message);

	temp_connection.caller_phone = parsed_message.front();
	temp_connection.respondent_phone = parsed_message.at(1);

	temp_connection.remaining_cycles_number = 
		static_cast<long long>(stoi(parsed_message.back()));
}

void ControllerClass::UpdateConversations()
{
	for (size_t i = 0; i < conversations_list_.size(); i++)
	{
		conversations_list_.at(i).remaining_cycles_number -= 10;

		if (!conversations_list_.at(i).remaining_cycles_number)
		{
			this->SetEmittion("SYSTEM_ROLLBACK_TOWERS " + conversations_list_.at(i).occupied_towers); // For Tower

			conversations_list_.erase(conversations_list_.begin() + i);
		}
	}

	current_system_cycle_++;
}

string ControllerClass::get_occupied_towers(string message)
{
	EraseSubstring(message, "SYSTEM_UPDATE_TOWERS ");

	return message;
}

void ControllerClass::SortConversations()
{
	// ShellSort:

	// Start with a big gap, then reduce the gap:
	for (size_t gap = conversations_list_.size() / 2; gap > 0; gap /= 2)
	{
		// Do a gapped insertion sort for this gap size.
		// The first gap elements a[0..gap-1] are already in gapped order
		// keep adding one more element until the entire array is gap sorted:
		for (size_t i = gap; i < conversations_list_.size(); i ++)
		{
			// Add a[i] to the elements that have been gap sorted and
			// save a[i] in temp and make a hole at position i:
			temp_connection = conversations_list_.at(i);

			size_t j = 0;

			// Shift earlier gap-sorted elements up until the correct
			// location for a[i] is found:
			for (j = i; j >= gap && 
				(std::stoull(conversations_list_.at(j - gap).caller_phone) > 
					std::stoull(temp_connection.caller_phone)); j -= gap)
			{
				conversations_list_.at(j) = conversations_list_.at(j - gap);
			}

			// Put temp (the original a[i]) in its correct location:
			conversations_list_.at(j) = temp_connection;
		}
	}
}

string ControllerClass::get_conversation_stats(size_t index)
{
	return "Phone " + conversations_list_.at(index).caller_phone 
		+ " <===> " + conversations_list_.at(index).respondent_phone;
}

#include "network_class.h"
#include "console_class.h"
#include "controller_class.h"
#include "pathfinder_class.h"
#include "tower_class.h"
#include "phone_class.h"
#include "screen_class.h"

using std::cin;
using std::cout;

NetworkClass::NetworkClass(string obj_name, BaseClass* parent_ptr) : BaseClass(obj_name, parent_ptr) {};

void NetworkClass::FormTree() 
{
	// Initialization of the components of the network:

	BaseClass* console_obj_ptr = new ConsoleClass("Console", this);

	BaseClass* controller_obj_ptr = new ControllerClass("Controller", this);

	BaseClass* pathfinder_obj_ptr = new PathfinderClass("Pathfinder", this);

	BaseClass* tower_obj_ptr = new TowerClass("Tower", this);

	BaseClass* phone_obj_ptr = new PhoneClass("Phone", this);

	BaseClass* screen_obj_ptr = new ScreenClass("Screen", this);

	// Setting connections (according to the scheme):
	this->SetDetectedConnection(this, console_obj_ptr);

	// REWORK CONNECTIONS

	for (size_t i = 1; i < children_list_.size(); i++)
	{
		if (i == 1 || i == 3 || i == 4) // Controller/Tower/Phone
		{
			console_obj_ptr->SetDetectedConnection(console_obj_ptr, children_list_.at(i));
		}
		if (i == 2 || i == 3 || i == 5) // Pathfinder/Tower/Screen
		{
			controller_obj_ptr->SetDetectedConnection(controller_obj_ptr, children_list_.at(i));
		}
		if (i == 2 || i == 4 || i == 5) // Pathfinder/Phone/Screen
		{
			tower_obj_ptr->SetDetectedConnection(tower_obj_ptr, children_list_.at(i));
		}
	}

	pathfinder_obj_ptr->SetDetectedConnection(pathfinder_obj_ptr, controller_obj_ptr);

	phone_obj_ptr->SetDetectedConnection(phone_obj_ptr, tower_obj_ptr);

	return;
}

void NetworkClass::SetStates()
{
	string obj_name = "";

	long long i_state = 0; // Readiness(state) field

	// While cin loop will run until the end of data:
	while (cin >> obj_name >> i_state)
	{
		// Search for the element in the tree and if it was found - update its state:
		this->get_obj_by_name(obj_name)->set_obj_state(bool(i_state));
	}
}

void NetworkClass::HandleConnections()
{
	BaseClass* emitter_ptr = nullptr; // Signal emitter (signaling object)
	BaseClass* handler_ptr = nullptr; // Signal handler (executor object)

	string emitter_path; // Path to the signal emitter
	string handler_path; // Path to the signal handler

	cin >> emitter_path;
	
	// Continue until the "end_of_connections":
	while (emitter_path != "end_of_connections")
	{
		cin >> handler_path;

		// Initializing objects pointers:
		emitter_ptr = this->get_obj_by_path(emitter_path);
		handler_ptr = this->get_obj_by_path(handler_path);

		// Setting connection between the pair of objects:
		emitter_ptr->SetDetectedConnection(emitter_ptr, handler_ptr);

		cin >> emitter_path;
	}
}

void NetworkClass::HandleInstructions()
{
	// Object that is set as the current chosen 
	// (head by default) *Not used in KL_3_3
	BaseClass* stated_obj = this;

	// Pointer at the object from path with current level
	BaseClass* path_stage_obj = nullptr;

	string instruction = "", path = "";

	// Entering the next instruction:
	cin >> instruction;

	while (instruction != "END")
	{
		// Entering the path:
		cin >> path;

		// Handling the path:

		// If the path is absolute:
		if (path.front() == '/')
		{
			// Selecting an object from a path beginning with the head object:
			path_stage_obj 
				= this->get_obj_by_path(path);
		}
		else
		{
			// Selecting an object from a path beginning with the stated object:
			path_stage_obj = stated_obj->get_obj_by_path(path);
		}
		
		if (instruction == "SET") // Not used in KL_3_3
		{	
			// If object from the path was found:
			if (path_stage_obj)
			{
				// Setting new stated object:
				stated_obj = path_stage_obj;
				cout << "Object is set: " << stated_obj->get_obj_name();
			}
			else
			{
				cout << "Object is not found: " 
					<< stated_obj->get_obj_name() << " " << path; // Error
			}
		}
		else if (instruction == "FIND") // Not used in KL_3_3
		{
			string tree_space = ""; // Defines the identation for the tree level

			tree_space.append(5U, ' '); // Setting the new identation

			// If object from the path was found:
			if (path_stage_obj)
			{
				// Outputing the object as the tree member:
				cout << path << tree_space << "Object name: " << path_stage_obj->get_obj_name();
			}
			else
			{
				cout << path << tree_space << "Object is not found"; // Error
			}
		}
		else if (instruction == "EMIT")
		{
			string message;

			// Using getline for getting the message because of the
			// possibility of using message consisting with more than one word:
			std::getline(cin, message);

			// If object from the path was found:
			if (path_stage_obj)
			{
				// Setting emittion:
				path_stage_obj->SetEmittion(message);
			}
			else
			{
				cout << "\nObject " << path << " not found"; // Error
			}
		}
		else if (instruction == "SET_CONDITION")
		{
			int object_state = 0; // New state of the object
			cin >> object_state;

			// If object from the path was found:
			if (path_stage_obj)
			{
				// Setting new state:
				path_stage_obj->set_obj_state(object_state);
			}
			else
			{
				cout << "\nObject " << path << " not found"; // Error
			}
		}
		else if (instruction == "SET_CONNECT" || instruction == "DELETE_CONNECT")
		{
			string handler_obj_path; // The path to the handler object
			cin >> handler_obj_path;

			BaseClass* handler_obj_ptr
				= this->get_obj_by_path(handler_obj_path);

			// If object from the path or handler object were not found:
			if (!path_stage_obj || !handler_obj_ptr)
			{
				if (!path_stage_obj)
				{
					cout << "\nObject " << path << " not found"; // Error
				}
				else
				{
					cout << "\nHandler object " << handler_obj_path << " not found"; // Error
				}
			}
			else
			{
				if (instruction == "SET_CONNECT")
				{
					// Setting connection:
					path_stage_obj->SetDetectedConnection(path_stage_obj, handler_obj_ptr);
				}
				else
				{
					// Deleting connection:
					path_stage_obj->DeleteDetectedConnection(path_stage_obj, handler_obj_ptr);
				}
			}
		}

		cin >> instruction;
	}
}

int NetworkClass::ExecuteApp()
{
	// Bringing all objects to a ready state:
	this->set_obj_state(true);

	// Starting initial data processing:
	this->SetEmittion("SYSTEM_ON");

	return 0;
};

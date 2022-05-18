#include "application_class.h"
#include "branch_class_2.h"
#include "branch_class_3.h"
#include "branch_class_4.h"
#include "branch_class_5.h"
#include "branch_class_6.h"

using std::cin;
using std::cout;

ApplicationClass::ApplicationClass(BaseClass* parent_ptr) 
{
	// Initialization of the progenitor object:
	BaseClass::progenitor->set_obj_parent(parent_ptr);
	BaseClass::progenitor->set_obj_name("progenitor");
	BaseClass::progenitor->set_obj_state(true);
};

void ApplicationClass::FormTree() 
{
	string head_name = "", child_name = "", path = "";
	int branch_class_number = 0;

	cin >> head_name;

	BaseClass* head = new BaseClass(head_name); // Head object creation

	BaseClass* child = nullptr;

	cin >> path;

	while (path != "endtree") // Exit condition
	{ 
		cin >> child_name >> branch_class_number;

		// The pointer at the current child's parent object
		BaseClass* parent_ptr = progenitor->children_list_.front()->get_obj_by_path(path);

		// If parent object wasn't found:
		if (!parent_ptr)
		{
			// Showing the existing part of the tree:
			progenitor->children_list_.front()->ShowTree();
			cout << "\nThe head object " << path << " is not found"; // Error

			exit(1); // Exit from the programm with error code 1
		}

		switch (branch_class_number)
		{
		case 2:
		{
			// Initializing new child object
			child = new BranchClass_2(child_name, parent_ptr);
			break;
		}
		case 3:
		{
			// Initializing new child object
			child = new BranchClass_3(child_name, parent_ptr);
			break;
		}
		case 4:
		{
			// Initializing new child object
			child = new BranchClass_4(child_name, parent_ptr);
			break;
		}
		case 5:
		{
			// Initializing new child object
			child = new BranchClass_5(child_name, parent_ptr);
			break;
		}
		case 6:
		{
			// Initializing new child object
			child = new BranchClass_6(child_name, parent_ptr);
			break;
		}
		}

		cin >> path; // Entering path to the new object
	}

	return;
}

void ApplicationClass::SetStates()
{
	string obj_name = "";

	long long i_state = 0; // Readiness(state) field

	// While cin loop will run until the end of data:
	while (cin >> obj_name >> i_state)
	{
		// Search for the element in the tree and if it was found - update its state:
		progenitor->get_obj_by_name(obj_name)->set_obj_state(bool(i_state));
	}
}

void ApplicationClass::HandleConnections()
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
		emitter_ptr = progenitor->children_list_.front()->get_obj_by_path(emitter_path);
		handler_ptr = progenitor->children_list_.front()->get_obj_by_path(handler_path);

		// Setting connection between the pair of objects:
		emitter_ptr->SetDetectedConnection(emitter_ptr, handler_ptr);

		cin >> emitter_path;
	}
}

void ApplicationClass::HandleInstructions()
{
	// Object that is set as the current chosen 
	// (head by default) *Not used in KL_3_3
	BaseClass* stated_obj = progenitor->children_list_.front();

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
				= progenitor->children_list_.front()->get_obj_by_path(path);
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
				path_stage_obj->DetectEmittion(message);
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
				= progenitor->children_list_.front()->get_obj_by_path(handler_obj_path);

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

int ApplicationClass::ExecuteApp()
{
	// Head object ShowTree (without_parameters) method call:
	progenitor->children_list_.front()->ShowTree();

	// Start processing connections
	HandleConnections();

	// Start processing instructions
	HandleInstructions();

	return 0;
};

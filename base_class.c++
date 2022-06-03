#include "base_class.h"
#include "network_class.h"
#include "console_class.h"
#include "controller_class.h"
#include "pathfinder_class.h"
#include "tower_class.h"
#include "phone_class.h"
#include "screen_class.h"

using std::cout;

BaseClass::BaseClass(string obj_name, BaseClass* parent_ptr) 
{
	this->obj_name_ = obj_name;
	if (parent_ptr) // Object isn't a head
	{ 
		set_obj_parent(parent_ptr);
	}
}

void BaseClass::set_obj_name(string obj_name) 
{
	this->obj_name_ = obj_name;
}

string BaseClass::get_obj_name() 
{
	return this->obj_name_;
}

void BaseClass::set_obj_parent(BaseClass* parent_ptr) 
{
	// Explanation:
	// This method overrides the current 
	// object's parent and includes few steps:
	// 1)Current object is written out from the children_list_ of its old parent.
	// 2)Current object is written down to the children_list_ of its new parent.
	// 3)Updating a pointer to the parent object.
	// Steps 1 and 2 are necessary only if current object already have a parent.

	if (parent_ptr_) // If current object already have a parent
	{
		// Iteration over all "brothers" of current objects
		for (size_t i = 0; i < parent_ptr_->children_list_.size(); i++)
		{
			if (parent_ptr_->children_list_.at(i) == this)
			{
				// Writing out from the children_list_ of the old parent
				parent_ptr_->children_list_.erase(parent_ptr_->children_list_.begin() + i);
				break;
			}
		}
	}

	if (parent_ptr) // If current object already have a parent
	{
		// Writing down to the children_list_ of the new parent
		parent_ptr->children_list_.push_back(this);
	}

	// Updating a pointer to the parent object
	parent_ptr_ = parent_ptr;
}

BaseClass* BaseClass::get_obj_parent()
{
	return this->parent_ptr_;
}

BaseClass* BaseClass::get_obj_by_name(string obj_name) 
{
	// Explanation:
	// This method returns the pointer at the object with needed name.
	// It goes through all the elements of the tree using recursion and,
	// if the names match, returns a pointer to the found object.
	
	BaseClass* temp_variable = nullptr; // Temporary BaseClass object

	// Iteration over children of current object with recursion
	for (size_t i = 0; i < children_list_.size(); i++) 
	{
		temp_variable = children_list_.at(i)->get_obj_by_name(obj_name);

		// If match is found, returns a pointer to the found object
		if (temp_variable->get_obj_name() == obj_name) 
		{
			return temp_variable;
		}
	}

	return this; // Returns the pointer at itself if no matches were found
}

BaseClass* BaseClass::get_head_obj()
{
	BaseClass* temp_obj = this;

	while (temp_obj->get_obj_parent() != nullptr)
	{
		temp_obj = temp_obj->get_obj_parent();
	}

	return temp_obj;
}

void BaseClass::set_obj_state(bool state)
{
	if (state) // Checks readiness of current object
	{
		BaseClass* parent_ptr = this->parent_ptr_; // Parent pointer

		// Checks readiness of all previous parent objects in current branch:
		while (parent_ptr) 
		{
			// Exit even if one parent in branch is not ready:
			if (!parent_ptr->get_obj_state())
			{
				return;
			}
			// Moving to the previous branch level:
			parent_ptr = parent_ptr->get_obj_parent();
		}
		// If all previous parents in branch are ready:
		this->state_ = true;
	}
	else
	{
		this->state_ = false;
	}

	for (size_t i = 0; i < children_list_.size(); i++)
	{
		this->children_list_.at(i)->set_obj_state(state);
	}

	return;
}

bool BaseClass::get_obj_state()
{
	return this->state_;
}

bool BaseClass::AreEqualConnections(connection_data*& a_connection,
	connection_data*& b_connection)
{
	// Explanation:
	// This method compares two objects of connection_data struct
	// by the equality of all their parameters

	if (a_connection->handler_ptr == b_connection->handler_ptr &&
		a_connection->signal_ptr == b_connection->signal_ptr &&
		a_connection->object_ptr == b_connection->object_ptr)
	{
		return true;
	}

	return false;
}

void BaseClass::SetConnection(TYPE_SIGNAL signal_ptr,
	TYPE_HANDLER handler_ptr, BaseClass* object_ptr)
{
	// Creating temporary connection_data struct object:
	connection_data* temp_connection 
		= new connection_data(signal_ptr, handler_ptr, object_ptr);

	// Iteration over all current object's connections:
	for (size_t i = 0; i < connections_list_.size(); i++)
	{
		// If there already is the same connection, as we want to set - exit:
		if (AreEqualConnections(connections_list_.at(i), temp_connection))
		{
			return;
		}
	}

	// Adding connection to the current object's connections list:
	connections_list_.push_back(temp_connection);
}

void BaseClass::DeleteConnection(TYPE_SIGNAL signal_ptr,
	TYPE_HANDLER handler_ptr, BaseClass* object_ptr)
{
	// Creating temporary connection_data struct object:
	connection_data* temp_connection
		= new connection_data(signal_ptr, handler_ptr, object_ptr);

	// Iteration over all current object's connections:
	for (size_t i = 0; i < connections_list_.size(); i++)
	{
		// If there is the same connection in the list, as we want to delete:
		if (AreEqualConnections(connections_list_.at(i), temp_connection))
		{
			// Deleting connection from the vector:
			connections_list_.erase(connections_list_.begin() + i);
			return;
		}
	}
}

void BaseClass::set_class_number(size_t class_number)
{
	this->branch_class_num_ = class_number;
}

size_t BaseClass::get_class_number()
{
	return this->branch_class_num_;
}

string BaseClass::get_absolute_path()
{
	if (this->parent_ptr_ == nullptr)
	{
		// If current object is head:
		return "/";
	}
	else
	{
		string path; // Absolute path to current object

		BaseClass* current_obj_ptr = this;

		// Iteration over all branch from bottom to top,
		// until the head object won't be reached:
		while (current_obj_ptr != get_head_obj())
		{
			path = "/" + current_obj_ptr->get_obj_name() + path;

			// Transition to the higher branch level:
			current_obj_ptr = current_obj_ptr->get_obj_parent();
		}

		// Returning absolute path:
		return path;
	}
}

void BaseClass::EraseSubstring(string& message, const string substring)
{
	int iterator = 0;

	while ((iterator = message.find(substring)) != string::npos)
	{
		message.erase(iterator, substring.length());
	}
}

void BaseClass::EmitSignal(TYPE_SIGNAL signal_ptr, string& message)
{
	// Explanation:
	// This method "initializes" signal

	// If the there are no connections with 
	// current object or object is disabled:
	if (connections_list_.empty() || !get_obj_state())
	{
		return;
	}

	string current_path = get_absolute_path();

	bool is_first_signal = true;

	// Iteration over all current object's connections:
	for (size_t i = 0; i < connections_list_.size(); i++)
	{
		if (is_first_signal)
		{
			TrySignal(current_path, message);
			is_first_signal = false;
		}

		// Is the object is ready:
		if (connections_list_.at(i)->object_ptr->get_obj_state())
		{
			connections_list_.at(i)->object_ptr->TryHandler(
				connections_list_.at(i)->object_ptr->get_absolute_path(), message);
		}
	}
}

void BaseClass::TrySignal(string path, string message)
{
	return;
}

void BaseClass::TryHandler(string path, string message)
{
	return;
}

string BaseClass::get_path_stage(const string &obj_path, const int path_level)
{
	// ps stands for path stage
	// first_ps_token is the index of the first symbol of the potential path stage
	int first_ps_token = (obj_path.front() == '/') ? 1 : -1;

	// ps stands for path stage
	// last_ps_token is the index of the last symbol of the potential path stage
	int last_ps_token = obj_path.size() - 1;

	int curr_ps_level = (obj_path.front() == '/') ? 1 : 0;

	// Explanation:
	// For example if the whole path is /object_2/object_3 with path_level == 1
	// first_ps_token will be 1 and last_ps_token will be 8

	while (first_ps_token)
	{
		if (first_ps_token < 0)
		{
			// Searches for the first '/' symbol 
			last_ps_token = obj_path.find('/');

			first_ps_token = 0; // For correct substring selection
		}
		else
		{
			// Searches for the first '/' symbol beggining 
			// with first_ps_token index
			last_ps_token = obj_path.find('/', first_ps_token);
		}

		if (curr_ps_level == path_level)
		{
			return obj_path.substr(first_ps_token, last_ps_token - first_ps_token);
		}

		// Explanation:
		// Expression (last_ps_token - first_ps_token) value can be below zero, but due to
		// the cast to size_t type it will be convetred to (max(size_t) - value) result,
		// and the rest part of the string will be returned

		curr_ps_level++; // Turning to the next path level

		first_ps_token = last_ps_token + 1;

		// Explanation:
		// If there is no more '/' int the path, last_ps_token value will be -1
		// and due to this fact, first_ps_token value will be 0 (exit condition),
		// else searching of '/' will begin from the next token (in next iteration)
	}

	return ""; // returns void string for further processing
}

BaseClass* BaseClass::get_obj_by_path(const string& obj_path)
{
	// Explanation:
	// This method returns the pointer at the last object in path.

	// Handling of special cases:
	if (obj_path == ".")
	{
		// Point is a sygn of current object
		return this;
	}
	else if (obj_path == "/")
	{
		// Single slash is a sygn of head object
		return get_head_obj();
	}
	else if (obj_path.substr(0, 2) == "//")
	{
		// Double slash before the object name 
		// is a sygn of absolute path from head object
		BaseClass* path_stage_obj = get_head_obj()->get_obj_by_name(obj_path.substr(2));

		return path_stage_obj;
	}

	// The rest cases are:
	// 1)Direct path from head object
	// 2)Indirect path from current object

	// ps stands for path stage
	
	// The name of current path stage object
	string current_ps = "";
	// The pointer at current path stage object parent (head by default)
	BaseClass* current_ps_parent_obj = this;

	size_t start_path_level = 0; // The current depth of the path

	// Determination of an absolute path:
	if (obj_path.front() == '/')
	{
		start_path_level = 1; // For ignoring first '/' symbol
	}

	// Describes connection between parent and child at some level of branch
	bool is_related_to_next = false;

	size_t slaches_number = std::count(obj_path.begin() + start_path_level, obj_path.end(), '/');

	if (obj_path.front() == '/')
	{
		slaches_number++; // For preventing unnecessary iteration
	}

	// Iteration by path_level variable over (the number of '/' symbols + 1) 
	// counted beggining with start_path_level index
	for (size_t path_level = start_path_level; path_level <= slaches_number; path_level++)
	{
		// Reset of variable:
		is_related_to_next = false;

		// Initializing current path stage object
		current_ps = get_path_stage(obj_path, path_level);

		// Iteration over all children of current path stage object
		for (size_t j = 0; j < current_ps_parent_obj->children_list_.size(); j++)
		{
			// If current path stage object is connected with the next  
			if (current_ps_parent_obj->children_list_.at(j)->get_obj_name() == current_ps)
			{
				// Moving to the next level of branch:
				current_ps_parent_obj = current_ps_parent_obj->children_list_.at(j);
				// Confirmation of the connection between parent and child at the path_level:
				is_related_to_next = true;
				break;
			}
		}

		// If the connection between objects in path is broken:
		if (!is_related_to_next)
		{
			return nullptr;
		}
	}

	return current_ps_parent_obj;
}

vector<string> BaseClass::ParseString(string message, string delimiter)
{
	size_t curr_pos = 0;
	string token;
	vector<string> parsed_message = {};

	while ((curr_pos = message.find(delimiter)) != string::npos) 
	{
		token = message.substr(0, curr_pos);
		parsed_message.push_back(token);
		message.erase(0, curr_pos + delimiter.length());
	}

	parsed_message.push_back(message);

	return parsed_message;
}

void BaseClass::SetDetectedConnection(BaseClass* emitter_ptr, BaseClass* handler_ptr)
{
	switch (handler_ptr->get_class_number())
	{
	case 1:
		emitter_ptr->SetConnection(SIGNAL(NetworkClass::TrySignal),
			HANDLER(NetworkClass::TryHandler), (NetworkClass*)handler_ptr);
		break;
	case 2:
		emitter_ptr->SetConnection(SIGNAL(ConsoleClass::TrySignal), 
			HANDLER(ConsoleClass::TryHandler), (ConsoleClass*)handler_ptr);
		break;
	case 3:
		emitter_ptr->SetConnection(SIGNAL(ControllerClass::TrySignal),
			HANDLER(ControllerClass::TryHandler), (ControllerClass*)handler_ptr);
		break;
	case 4:
		emitter_ptr->SetConnection(SIGNAL(PathfinderClass::TrySignal),
			HANDLER(PathfinderClass::TryHandler), (PathfinderClass*)handler_ptr);
		break;
	case 5:
		emitter_ptr->SetConnection(SIGNAL(TowerClass::TrySignal),
			HANDLER(TowerClass::TryHandler), (TowerClass*)handler_ptr);
		break;
	case 6:
		emitter_ptr->SetConnection(SIGNAL(PhoneClass::TrySignal),
			HANDLER(PhoneClass::TryHandler), (PhoneClass*)handler_ptr);
		break;
	case 7:
		emitter_ptr->SetConnection(SIGNAL(ScreenClass::TrySignal),
			HANDLER(ScreenClass::TryHandler), (ScreenClass*)handler_ptr);
		break;
	}
}

void BaseClass::DeleteDetectedConnection(BaseClass* emitter_ptr, BaseClass* handler_ptr)
{
	switch (handler_ptr->get_class_number())
	{
	case 1:
		emitter_ptr->DeleteConnection(SIGNAL(NetworkClass::TrySignal),
			HANDLER(NetworkClass::TryHandler), (NetworkClass*)handler_ptr);
		break;
	case 2:
		emitter_ptr->DeleteConnection(SIGNAL(ConsoleClass::TrySignal),
			HANDLER(ConsoleClass::TryHandler), (ConsoleClass*)handler_ptr);
		break;
	case 3:
		emitter_ptr->DeleteConnection(SIGNAL(ControllerClass::TrySignal),
			HANDLER(ControllerClass::TryHandler), (ControllerClass*)handler_ptr);
		break;
	case 4:
		emitter_ptr->DeleteConnection(SIGNAL(PathfinderClass::TrySignal),
			HANDLER(PathfinderClass::TryHandler), (PathfinderClass*)handler_ptr);
		break;
	case 5:
		emitter_ptr->DeleteConnection(SIGNAL(TowerClass::TrySignal),
			HANDLER(TowerClass::TryHandler), (TowerClass*)handler_ptr);
		break;
	case 6:
		emitter_ptr->DeleteConnection(SIGNAL(PhoneClass::TrySignal),
			HANDLER(PhoneClass::TryHandler), (PhoneClass*)handler_ptr);
		break;
	case 7:
		emitter_ptr->DeleteConnection(SIGNAL(ScreenClass::TrySignal),
			HANDLER(ScreenClass::TryHandler), (ScreenClass*)handler_ptr);
		break;
	}
}

void BaseClass::SetEmittion(string message)
{
	// This method is intermediary between signal 
	// initialization and its implementation

	BaseClass* temp_obj_ptr = this;

	// Checking readiness of all parents and current object
	while (temp_obj_ptr != get_head_obj())
	{
		if (temp_obj_ptr->get_obj_state())
		{
			temp_obj_ptr = temp_obj_ptr->get_obj_parent();
		}
		else
		{
			return;
		}
	}

	switch (branch_class_num_)
	{
	case 1:

		this->EmitSignal(SIGNAL(NetworkClass::TrySignal), message);
		break;
	case 2:

		this->EmitSignal(SIGNAL(ConsoleClass::TrySignal), message);
		break;
	case 3:

		this->EmitSignal(SIGNAL(ControllerClass::TrySignal), message);
		break;
	case 4:

		this->EmitSignal(SIGNAL(PathfinderClass::TrySignal), message);
		break;
	case 5:

		this->EmitSignal(SIGNAL(TowerClass::TrySignal), message);
		break;
	case 6:

		this->EmitSignal(SIGNAL(PhoneClass::TrySignal), message);
		break;
	case 7:

		this->EmitSignal(SIGNAL(ScreenClass::TrySignal), message);
		break;
	}
}

void BaseClass::ShowNextTreeObj(BaseClass* current_obj_ptr, 
	const string& tree_parameter, unsigned tree_level)
{
	// Explanation:
	// This method is a service method for ShowTree method, 
	// which output each elment of tree with recursion.
	// 
	// tree_parameter defines the way of tree output - with or without readiness

	string tree_level_space; // defines the identation for the tree level

	tree_level_space.append(4U * tree_level, ' ');

	if (tree_parameter == "with_readiness")
	{
		if (current_obj_ptr->get_obj_state())
		{
			cout << '\n' << tree_level_space
				<< current_obj_ptr->get_obj_name() << " is ready";
		}
		else
		{
			cout << '\n' << tree_level_space
				<< current_obj_ptr->get_obj_name() << " is not ready";
		}
	}
	else
	{
		cout << '\n' << tree_level_space << current_obj_ptr->get_obj_name();
	}

	if (current_obj_ptr == get_head_obj()->children_list_.at(3)) // Tower
	{
		get_head_obj()->children_list_.front()->
			SetEmittion("CONSOLE:TOWER Display initial tower data at level " + 
				std::to_string(tree_level + 1));
	}
	else if (current_obj_ptr == get_head_obj()->children_list_.at(4)) // Phone
	{
		get_head_obj()->children_list_.front()->
			SetEmittion("CONSOLE:PHONE Display initial phone data at level " +
				std::to_string(tree_level + 1));
	}

	// Returning to the previous element of the recursion 
	// due to the emptiness of children list:
	if (current_obj_ptr->children_list_.empty()) return;

	// Iteration over all children_list_ elements
	for (size_t i = 0; i < current_obj_ptr->children_list_.size(); i++)
	{
		// Recursion
		ShowNextTreeObj(current_obj_ptr->children_list_.at(i), 
			tree_parameter, tree_level + 1);
	}
}

void BaseClass::ShowTree(const string& tree_parameter)
{
	// tree_parameter defines the way of tree output:
	cout << ((tree_parameter == "with_readiness") ?
		"The tree of objects and their readiness:" : "The tree of objects:");

	// The tree is printed with the help of recursion.
	// The exit condition is the lack of children objects.
	ShowNextTreeObj(this, tree_parameter);
}

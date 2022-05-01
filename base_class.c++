#include "base_class.h"

using std::cout;

// progenitor (root) object (positioned above the head object)
BaseClass* BaseClass::progenitor = new BaseClass(); 

BaseClass::BaseClass(string obj_name, BaseClass* parent_ptr) 
{
	this->obj_name_ = obj_name;
	if (parent_ptr) // Object isn't a head
	{ 
		set_obj_parent(parent_ptr);
	}
	else // Object is head
	{ 
		// Making progenitor a parent of the head object
		set_obj_parent(progenitor); 
	}
}

void BaseClass::set_obj_name(string obj_name) 
{
	this->obj_name_ = obj_name;
}

string BaseClass::get_obj_name() 
{
	return obj_name_;
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
	return parent_ptr_;
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
	return;
}

bool BaseClass::get_obj_state()
{
	return this->state_;
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
		return progenitor->children_list_.front();
	}
	else if (obj_path.substr(0, 2) == "//")
	{
		// Double slash before the object name 
		// is a sygn of absolute path from head object
		BaseClass* path_stage_obj = progenitor->get_obj_by_name(obj_path.substr(2));

		if (path_stage_obj == progenitor)
		{
			return nullptr;
		}

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
		"\nThe tree of objects and their readiness" : "Object tree");

	// The tree is printed with the help of recursion.
	// The exit condition is the lack of children objects.
	ShowNextTreeObj(this, tree_parameter);
}

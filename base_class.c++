#include "base_class.h"

using std::cout;

// progenitor (root) object (positioned above the head object)
BaseClass* BaseClass::progenitor = new BaseClass(); 

BaseClass::BaseClass(string obj_name, BaseClass* parent_ptr) 
{
	this->obj_name_ = obj_name;
	if (parent_ptr) // if object isn't a head
	{ 
		set_obj_parent(parent_ptr);
	}
	else // if object is head
	{ 
		// making progenitor a parent of the head object
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
	if (parent_ptr) // if object isn't a head
	{
		for (size_t i = 0; i < parent_ptr->children_list_.size(); i++) 
		{
			if (parent_ptr->children_list_.at(i) == this) 
			{
				parent_ptr->children_list_.erase(parent_ptr->children_list_.begin() + i);
				break;
			}
		}
		parent_ptr->children_list_.push_back(this);
	}
	this->parent_ptr_ = parent_ptr;
}

BaseClass* BaseClass::get_obj_parent()
{
	return parent_ptr_;
}

BaseClass* BaseClass::get_obj_ptr(string obj_name) 
{
	// is used in formTree ClassApplication method

	// temporary pointer at BaseClass object
	BaseClass* temp_variable = nullptr;

	// iteration over children of current object with recursion
	for (size_t i = 0; i < children_list_.size(); i++) 
	{
		temp_variable = children_list_.at(i)->get_obj_ptr(obj_name);
		if (temp_variable->get_obj_name() == obj_name) 
		{
			return temp_variable;
		}
	}

	return this; // returns the pointer at itself if no matches were found
}

void BaseClass::set_obj_state(bool state)
{
	if (state) // checks readiness of current object
	{
		BaseClass* parent_ptr = this->parent_ptr_;
		while (parent_ptr) // checks readiness of all parent objects
		{
			if (!parent_ptr->get_obj_state())
			{
				return;
			}
			parent_ptr = parent_ptr->get_obj_parent();
		}
		this->state_ = true;
	}
	return;
}

bool BaseClass::get_obj_state()
{
	return this->state_;
}

void BaseClass::ShowNextTreeObj(BaseClass* current_obj_ptr, 
	const string& tree_parameter, unsigned tree_level)
{
	// tree_parameter defines the way of tree output

	string tree_level_space; // defines the identation for the level
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

	// returning to the previous element of the recursion 
	// due to empty children list
	if (current_obj_ptr->children_list_.empty()) return;

	// iteration over all children_list_ elements
	for (size_t i = 0; i < current_obj_ptr->children_list_.size(); i++)
	{
		// recursion
		ShowNextTreeObj(current_obj_ptr->children_list_.at(i), 
			tree_parameter, tree_level + 1);
	}
}

void BaseClass::ShowTree(const string& tree_parameter)
{
	// tree_parameter defines the way of tree output
	cout << ((tree_parameter == "with_readiness") ? 
		"\nThe tree of objects and their readiness" : "Object tree");

	// The tree is printed with the help of recursion
	// The exit condition is the lack of children objects
	ShowNextTreeObj(this, tree_parameter);
}

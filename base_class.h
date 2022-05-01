#ifndef BASE_CLASS_H
#define BASE_CLASS_H

#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;

class BaseClass {
public:
	
	// Default contructor
	BaseClass() { parent_ptr_ = nullptr; };

	// Parametrized constructor
	BaseClass(string obj_name, BaseClass* parent_ptr = nullptr);

	// Setter for obj_name_ field
	void set_obj_name(string obj_name);

	// Getter for obj_name_ field
	string get_obj_name();

	// Method that solves the problem of access to the private field 
	// of BaseClass object from ApplicationClass (without using protected)
	void set_obj_parent(BaseClass* parent_ptr);

	// Getter for parent_ptr_ field
	BaseClass* get_obj_parent();

	// Getter for object pointer by name of the object
	BaseClass* get_obj_by_name(string obj_name);

	// Setter for state_ field
	void set_obj_state(bool state);

	// Getter for is_set_ field
	bool get_obj_state();

	// Getter for parent object pointer by the path
	BaseClass* get_obj_by_path(const string& obj_path);

	// Method that outputs object tree in two different variations
	void ShowTree(const string& tree_parameter = "without_readiness");

	vector<BaseClass*> children_list_;

	// progenitor (root) object (positioned above the head object)
	static BaseClass* progenitor;
private:

	string obj_name_ = ""; // Object name
	BaseClass* parent_ptr_ = nullptr; // Pointer at parent object
	bool state_ = false; // Object state definition

	// Service method for get_obj_by_path that extracts an element from an object path
	string get_path_stage(const string& obj_path, const int path_level = 1);
	
	// Service recursive method for ShowTree
	void ShowNextTreeObj(BaseClass* current_obj_ptr, const string& tree_parameter, unsigned tree_level = 0);
};

#endif // !BASE_CLASS_H

#ifndef BASE_CLASS_H
#define BASE_CLASS_H

#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;

class BaseClass {
public:
	
	// default contructor
	BaseClass() { parent_ptr_ = nullptr; };

	// parametrized constructor
	BaseClass(string obj_name, BaseClass* parent_ptr = nullptr);

	// setter for obj_name_ field
	void set_obj_name(string obj_name);

	// getter for obj_name_ field
	string get_obj_name();

	// method that solves the problem of access to the private field 
	// of BaseClass object from ApplicationClass (without using protected)
	void set_obj_parent(BaseClass* parent_ptr);

	// getter for parent_ptr_ field
	BaseClass* get_obj_parent();

	// getter for object pointer by name of the object
	BaseClass* get_obj_ptr(string obj_name);

	// setter for state_ field
	void set_obj_state(bool state);

	// getter for state_ field
	bool get_obj_state();

	// method that outputs object tree in two different variations
	void ShowTree(const string& tree_parameter);

	vector<BaseClass*> children_list_;

	// progenitor (root) object (positioned above the head object)
	static BaseClass* progenitor;
private:

	string obj_name_ = ""; // object name
	BaseClass* parent_ptr_ = nullptr; // pointer at parent object
	bool state_ = false; // object readiness

	// service method for ShowTree
	void ShowNextTreeObj(BaseClass* parent_ptr, 
		const string& tree_parameter, unsigned tree_level = 0);
};

#endif // !BASE_CLASS_H

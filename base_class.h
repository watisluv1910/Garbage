#ifndef BASE_CLASS_H
#define BASE_CLASS_H

#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;

#define SIGNAL(signal_f) (TYPE_SIGNAL) (& signal_f)
#define HANDLER(handler_f) (TYPE_HANDLER) (& handler_f)

class BaseClass;

typedef void (BaseClass::* TYPE_SIGNAL) (string&);
typedef void (BaseClass::* TYPE_HANDLER) (string);

class BaseClass 
{
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

	// 
	BaseClass* get_head_obj();

	// Setter for state_ field
	void set_obj_state(bool state);

	// Getter for is_set_ field
	bool get_obj_state();

	// Setter for branch_class_num_ field
	void set_class_number(size_t class_number);

	// Getter for branch_class_num_ field
	size_t get_class_number();

	// Method that return the path from head to current object
	string get_absolute_path();

	// 
	void EraseSubstring(string& message, const string substring);

	//
	vector<string> ParseString(string message, string delimiter = " ");

	// Signal method for each branch class
	virtual void TrySignal(string path, string message);
	
	// Handler method for each branch class
	virtual void TryHandler(string path, string message);

	// Getter for parent object pointer by the path
	BaseClass* get_obj_by_path(const string& obj_path);

	// Main setting connectiom method
	void SetDetectedConnection(BaseClass* emitter_ptr, BaseClass* handler_ptr);

	// Main deleting connection method
	void DeleteDetectedConnection(BaseClass* emitter_ptr, BaseClass* handler_ptr);

	// Main emittion method
	void SetEmittion(string message);

	// Method that outputs object tree in two different variations
	void ShowTree(const string& tree_parameter = "without_readiness");

	vector<BaseClass*> children_list_;
protected:

	// The number of the branch class
	size_t branch_class_num_ = 1;
private:

	string obj_name_ = ""; // Object name
	BaseClass* parent_ptr_ = nullptr; // Pointer at parent object
	bool state_ = false; // Object state definition

	// Structure of the connection
	struct connection_data
	{
		connection_data() {};

		// Parametrized constructor for initializing structure's fields
		connection_data(TYPE_SIGNAL signal_ptr,
			TYPE_HANDLER handler_ptr, BaseClass* object_ptr) : 
			signal_ptr(signal_ptr), handler_ptr(handler_ptr), 
			object_ptr(object_ptr) {};

		TYPE_SIGNAL signal_ptr = nullptr; // Pointer at signal function
		TYPE_HANDLER handler_ptr = nullptr; // Pointer at handler function
		BaseClass* object_ptr = nullptr; // Pointer at receiving object
	};

	// The list of connections with current object
	vector<connection_data*> connections_list_;

	// Service method for get_obj_by_path that extracts an element from an object path
	string get_path_stage(const string& obj_path, const int path_level = 1);

	// Comparator for two pointers at the objects of the connection_data struct
	bool AreEqualConnections(connection_data*& a_connection,
		connection_data*& b_connection);

	// Service method for SetDetecetedConnection
	void SetConnection(TYPE_SIGNAL signal_ptr,
		TYPE_HANDLER handler_ptr, BaseClass* object_ptr);

	// Service method for DeleteDetecetedConnection
	void DeleteConnection(TYPE_SIGNAL signal_ptr,
		TYPE_HANDLER handler_ptr, BaseClass* object_ptr);

	// Service method for SetEmittion
	void EmitSignal(TYPE_SIGNAL signal_ptr, string& message);
	
	// Service recursive method for ShowTree
	void ShowNextTreeObj(BaseClass* current_obj_ptr, 
		const string& tree_parameter, unsigned tree_level = 0);
};

#endif // !BASE_CLASS_H

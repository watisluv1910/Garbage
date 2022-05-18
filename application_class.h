#ifndef APPLICATION_CLASS_H
#define APPLICATION_CLASS_H

#include "base_class.h"

class ApplicationClass : public BaseClass {
public:

	// Parametrized constructor
	ApplicationClass(BaseClass* parent_ptr = nullptr);
	
	// Main tree building method
	void FormTree();

	// Main states setter method
	void SetStates();

	// Main connection setter method
	void HandleConnections();

	// Main instruction handling method
	void HandleInstructions();

	// Main application method
	int ExecuteApp();
};

#endif // !APPLICATION_CLASS_H

#ifndef APPLICATION_CLASS_H
#define APPLICATION_CLASS_H

#include "base_class.h"

class ApplicationClass : public BaseClass {
public:

	// parametrized constructor
	ApplicationClass(BaseClass* parent_ptr = nullptr);
	
	// main tree building method
	void FormTree();

	// main states setter method
	void SetStates();

	// main application method
	int ExecuteApp();
};

#endif // !APPLICATION_CLASS_H

#ifndef BRANCH_CLASS_5_H
#define BRANCH_CLASS_5_H

#include "base_class.h"

class BranchClass_5 : public BaseClass
{
public:

	BranchClass_5(string obj_name, BaseClass* parent_ptr)
		: BaseClass(obj_name, parent_ptr) {};
};

#endif // !BRANCH_CLASS_5_H
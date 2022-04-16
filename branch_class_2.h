#ifndef BRANCH_CLASS_2_H
#define BRANCH_CLASS_2_H

#include "base_class.h"

class BranchClass_2 : public BaseClass
{
public:

	BranchClass_2(string obj_name, BaseClass* parent_ptr)
		: BaseClass(obj_name, parent_ptr) {};
};

#endif // !BRANCH_CLASS_2_H
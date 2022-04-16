#ifndef BRANCH_CLASS_3_H
#define BRANCH_CLASS_3_H

#include "base_class.h"

class BranchClass_3 : public BaseClass
{
public:

	BranchClass_3(string obj_name, BaseClass* parent_ptr)
		: BaseClass(obj_name, parent_ptr) {};
};

#endif // !BRANCH_CLASS_3_H
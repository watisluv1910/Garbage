#ifndef BRANCH_CLASS_6_H
#define BRANCH_CLASS_6_H

#include "base_class.h"

class BranchClass_6 : public BaseClass
{
public:

	BranchClass_6(string obj_name, BaseClass* parent_ptr);

	void ShowSignal(string path) override;

	void ShowHandler(string path, string message) override;
};

#endif // !BRANCH_CLASS_6_H
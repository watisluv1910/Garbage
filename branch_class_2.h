#ifndef BRANCH_CLASS_2_H
#define BRANCH_CLASS_2_H

#include "base_class.h"

class BranchClass_2 : public BaseClass
{
public:

	BranchClass_2(string obj_name, BaseClass* parent_ptr);

	void ShowSignal(string path) override;

	void ShowHandler(string path, string message) override;
};

#endif // !BRANCH_CLASS_2_H
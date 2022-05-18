#ifndef BRANCH_CLASS_5_H
#define BRANCH_CLASS_5_H

#include "base_class.h"

class BranchClass_5 : public BaseClass
{
public:

	BranchClass_5(string obj_name, BaseClass* parent_ptr);

	void ShowSignal(string path) override;

	void ShowHandler(string path, string message) override;
};

#endif // !BRANCH_CLASS_5_H
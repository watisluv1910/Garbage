#ifndef BRANCH_CLASS_4_H
#define BRANCH_CLASS_4_H

#include "base_class.h"

class BranchClass_4 : public BaseClass
{
public:

	BranchClass_4(string obj_name, BaseClass* parent_ptr);

	void ShowSignal(string path) override;

	void ShowHandler(string path, string message) override;
};

#endif // !BRANCH_CLASS_4_H
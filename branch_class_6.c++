#include "branch_class_6.h"

// some code'll be here later

BranchClass_6::BranchClass_6(string obj_name, BaseClass* parent_ptr)
	: BaseClass(obj_name, parent_ptr)
{
	set_class_number(6);
}

void BranchClass_6::ShowSignal(string path)
{
	std::cout << "\nSignal from " << path;
}

void BranchClass_6::ShowHandler(string path, string message)
{
	std::cout << "\nSignal to " << path
		<< " Text: " << message << " (class: " << branch_class_num_ << ")";
}

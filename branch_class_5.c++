#include "branch_class_5.h"

// some code'll be here later

BranchClass_5::BranchClass_5(string obj_name, BaseClass* parent_ptr)
	: BaseClass(obj_name, parent_ptr)
{
	set_class_number(5);
}

void BranchClass_5::ShowSignal(string path)
{
	std::cout << "\nSignal from " << path;
}

void BranchClass_5::ShowHandler(string path, string message)
{
	std::cout << "\nSignal to " << path
		<< " Text: " << message << " (class: " << branch_class_num_ << ")";
}

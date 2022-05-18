#include "branch_class_2.h"

// some code'll be here later

BranchClass_2::BranchClass_2(string obj_name, BaseClass* parent_ptr)
	: BaseClass(obj_name, parent_ptr)
{
	set_class_number(2);
}

void BranchClass_2::ShowSignal(string path)
{
	std::cout << "\nSignal from " << path;
}

void BranchClass_2::ShowHandler(string path, string message)
{
	std::cout << "\nSignal to " << path
		<< " Text: " << message << " (class: " << branch_class_num_ << ")";
}

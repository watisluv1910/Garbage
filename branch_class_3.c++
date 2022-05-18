#include "branch_class_3.h"

// some code'll be here later

BranchClass_3::BranchClass_3(string obj_name, BaseClass* parent_ptr)
	: BaseClass(obj_name, parent_ptr)
{
	set_class_number(3);
}

void BranchClass_3::ShowSignal(string path)
{
	std::cout << "\nSignal from " << path;
}

void BranchClass_3::ShowHandler(string path, string message)
{
	std::cout << "\nSignal to " << path
		<< " Text: " << message << " (class: " << branch_class_num_ << ")";
}
#include "branch_class_4.h"

// some code'll be here later

BranchClass_4::BranchClass_4(string obj_name, BaseClass* parent_ptr)
	: BaseClass(obj_name, parent_ptr)
{
	set_class_number(4);
}

void BranchClass_4::ShowSignal(string path)
{
	std::cout << "\nSignal from " << path;
}

void BranchClass_4::ShowHandler(string path, string message)
{
	std::cout << "\nSignal to " << path
		<< " Text: " << message << " (class: " << branch_class_num_ << ")";
}

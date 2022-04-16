#include "application_class.h"
#include "branch_class_2.h"
#include "branch_class_3.h"
#include "branch_class_4.h"
#include "branch_class_5.h"
#include "branch_class_6.h"

using std::cin;
using std::numeric_limits;
using std::streamsize;

ApplicationClass::ApplicationClass(BaseClass* parent_ptr) 
{
	// initialization of the progenitor object
	BaseClass::progenitor->set_obj_parent(parent_ptr);
	BaseClass::progenitor->set_obj_name("progenitor");
	BaseClass::progenitor->set_obj_state(true);
};

void ApplicationClass::FormTree() 
{
	string parent_name = "", child_name = "";
	int branch_class_number = 0;

	cin >> parent_name;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	BaseClass* head = new BaseClass(parent_name); // head object

	BaseClass* child = nullptr;

	cin >> parent_name;

	while (parent_name != "endtree") { // exit condition

		cin >> child_name >> branch_class_number;

		switch (branch_class_number)
		{
		case 2:
		{
			// new child object
			child = new BranchClass_2(child_name, 
				progenitor->get_obj_ptr(parent_name));
			break;
		}
		case 3:
		{
			// new child object
			child = new BranchClass_3(child_name, 
				progenitor->get_obj_ptr(parent_name));
			break;
		}
		case 4:
		{
			// new child object
			child = new BranchClass_4(child_name, 
				progenitor->get_obj_ptr(parent_name));
			break;
		}
		case 5:
		{
			// new child object
			child = new BranchClass_5(child_name, 
				progenitor->get_obj_ptr(parent_name));
			break;
		}
		case 6:
		{
			// new child object
			child = new BranchClass_6(child_name, 
				progenitor->get_obj_ptr(parent_name));
			break;
		}
		default:
			break;
		}

		cin >> parent_name;
	}
}

void ApplicationClass::SetStates()
{
	string obj_name = "";
	long long i_state = 0;

	while (cin >> obj_name >> i_state)
	{
		progenitor->get_obj_ptr(obj_name)->set_obj_state(bool(i_state));
	}
}

int ApplicationClass::ExecuteApp()
{
	// head object ShowTree (without parameters) method call:
	progenitor->children_list_.at(0)->ShowTree("without_readiness");

	// head object ShowTree (with parameters) method call:
	progenitor->children_list_.at(0)->ShowTree("with_readiness");

	return 0;
};

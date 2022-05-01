#include "application_class.h"
#include "branch_class_2.h"
#include "branch_class_3.h"
#include "branch_class_4.h"
#include "branch_class_5.h"
#include "branch_class_6.h"

using std::cin;
using std::cout;
using std::numeric_limits;
using std::streamsize;

ApplicationClass::ApplicationClass(BaseClass* parent_ptr) 
{
	// Initialization of the progenitor object
	BaseClass::progenitor->set_obj_parent(parent_ptr);
	BaseClass::progenitor->set_obj_name("progenitor");
	BaseClass::progenitor->set_obj_state(true);
};

void ApplicationClass::FormTree() 
{
	string head_name = "", child_name = "", path = "";
	int branch_class_number = 0;

	cin >> head_name;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	BaseClass* head = new BaseClass(head_name); // Head object

	BaseClass* child = nullptr;

	cin >> path;

	while (path != "endtree") // Exit condition
	{ 
		cin >> child_name >> branch_class_number;

		BaseClass* parent_ptr = progenitor->children_list_.front()->get_obj_by_path(path);

		if (!parent_ptr)
		{
			progenitor->children_list_.front()->ShowTree();
			cout << "\nThe head object " << path << " is not found";

			exit(1);
		}

		switch (branch_class_number)
		{
		case 2:
		{
			// new child object
			child = new BranchClass_2(child_name, parent_ptr);
			break;
		}
		case 3:
		{
			// new child object
			child = new BranchClass_3(child_name, parent_ptr);
			break;
		}
		case 4:
		{
			// new child object
			child = new BranchClass_4(child_name, parent_ptr);
			break;
		}
		case 5:
		{
			// new child object
			child = new BranchClass_5(child_name, parent_ptr);
			break;
		}
		case 6:
		{
			// new child object
			child = new BranchClass_6(child_name, parent_ptr);
			break;
		}
		default:
			break;
		}

		cin >> path;
	}

	return;
}

void ApplicationClass::SetStates()
{
	// Main setter for all state_ fields

	string obj_name = "";

	long long i_state = 0;

	while (cin >> obj_name >> i_state)
	{
		progenitor->get_obj_by_name(obj_name)->set_obj_state(bool(i_state));
	}
}

void ApplicationClass::StartTreeNavigation()
{
	BaseClass* stated_obj = progenitor->children_list_.front();
	BaseClass* path_stage_obj = nullptr; // ps stands for path stage

	string directive = "", path = "";

	cin >> directive;

	while (directive != "END")
	{
		cout << '\n';

		cin >> path;

		if (path.front() == '/')
		{
			path_stage_obj = progenitor->children_list_.front()->get_obj_by_path(path);
		}
		else
		{
			path_stage_obj = stated_obj->get_obj_by_path(path);
		}

		if (directive == "SET")
		{
			if (path_stage_obj)
			{
				stated_obj = path_stage_obj;
				cout << "Object is set: " 
					<< stated_obj->get_obj_name();
			}
			else
			{
				cout << "Object is not found: " 
					<< stated_obj->get_obj_name() << " " << path;
			}
		}
		else if (directive == "FIND")
		{
			string tree_space = ""; // Defines the identation for the level

			tree_space.append(5U, ' ');

			if (path_stage_obj)
			{
				cout << path << tree_space << "Object name: " << path_stage_obj->get_obj_name();
			}
			else
			{
				cout << path << tree_space << "Object is not found";
			}
		}

		cin >> directive;
	}
}

int ApplicationClass::ExecuteApp()
{
	// Head object ShowTree (without_parameters) method call:
	progenitor->children_list_.front()->ShowTree();

	this->StartTreeNavigation();

	return 0;
};

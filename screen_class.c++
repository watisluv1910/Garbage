#include "screen_class.h"

using std::cout;

ScreenClass::ScreenClass(string obj_name, BaseClass* parent_ptr)
	: BaseClass(obj_name, parent_ptr)
{
	set_class_number(7);
}

void ScreenClass::TrySignal(string path, string message)
{
	return;
}

void ScreenClass::TryHandler(string path, string message)
{
	string label = "SYSTEM_OUTPUT ";

	if (message.find(label) != string::npos)
	{
		string additional_label = "";

		if (message.find("TREE_DATA") != string::npos)
		{
			additional_label = "TREE_DATA ";
			cout << '\n';
		}
		
		cout << message.substr(label.length() + additional_label.length());

		if (message.find("Turn off the ATM") == string::npos &&
			message.find("TREE_DATA") == string::npos)
		{
			cout << '\n';
		}
	}
	return;
}

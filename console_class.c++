#include "console_class.h"

#include <sstream>

ConsoleClass::ConsoleClass(string obj_name, BaseClass* parent_ptr)
	: BaseClass(obj_name, parent_ptr)
{
	set_class_number(2);
}

void ConsoleClass::TrySignal(string path, string message)
{
	return;
}

void ConsoleClass::TryHandler(string path, string message)
{
	string instruction;

	if (message == "SYSTEM_ON")
	{
		do
		{
			std::getline(std::cin, instruction);
			this->SetEmittion(instruction);

		} while (instruction != "Turn off the system");

		this->SetEmittion("SYSTEM_OUTPUT Turn off the ATM");
	}

	return;
}

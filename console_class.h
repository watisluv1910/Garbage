#ifndef CONSOLE_CLASS_H
#define CONSOLE_CLASS_H

#include "base_class.h"
#include "tower_class.h"

class ConsoleClass : public BaseClass
{
public:

	ConsoleClass(string obj_name, BaseClass* parent_ptr);

	void TrySignal(string path, string message) override;

	void TryHandler(string path, string message) override;
};

#endif // !CONSOLE_CLASS_H
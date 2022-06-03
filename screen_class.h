#ifndef SCREEN_CLASS_H
#define SCREEN_CLASS_H

#include "base_class.h"

class ScreenClass : public BaseClass
{
public:

	ScreenClass(string obj_name, BaseClass* parent_ptr);

	void TrySignal(string path, string message) override;

	void TryHandler(string path, string message) override;
};

#endif // !SCREEN_CLASS_H

#pragma once
#include "ClassBase.h"

class ClassApplication : public ClassBase {
private:

	//void showNextObject(ClassBase* p_Parent, int i_level);
public:

	ClassApplication(ClassBase* p_Parent = nullptr);

	void formTree();

	int executeApp();
};
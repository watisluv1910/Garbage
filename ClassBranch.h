#pragma once

#include "ClassBase.h"

class ClassBranch : public ClassBase {
public:

	ClassBranch(string objName, ClassBase* root) : ClassBase(objName, root) {};
};
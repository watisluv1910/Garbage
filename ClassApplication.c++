#include "ClassApplication.h"

ClassApplication::ClassApplication(ClassBase* p_Parent) {

	ClassBase::progenitor->setParent(p_Parent);
	ClassBase::progenitor->setObjName("progenitor");
	ClassBase::progenitor->childrenList.push_back(progenitor);
};

void ClassApplication::formTree() {

	string parentName, childName;
	cin >> parentName;
	ClassBase* child = new ClassBase(parentName);
	while (true) {

		cin >> parentName >> childName;

		if (parentName == childName) {

			return;
		}

		ClassBase* grandchild = new ClassBase(childName, progenitor->getObject(parentName));

		parentName = childName;
	}
};

int ClassApplication::executeApp() {

	cout << progenitor->childrenList.at(1)->getObjName();
	progenitor->childrenList.at(1)->showTree();
	return 0;
};

//void ClassApplication::showNextObject(ClassBase* p_Parent, int i_level) {
//
//
//};
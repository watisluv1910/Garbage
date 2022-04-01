#include "ClassApplication.h"

ClassApplication::ClassApplication(ClassBase* p_Parent) {

	// using setParent due to lack of access to the private field:
	ClassBase::progenitor->setParent(p_Parent);
	ClassBase::progenitor->setObjName("progenitor");
	ClassBase::progenitor->childrenList.push_back(progenitor);
};

void ClassApplication::formTree() {

	string parentName, childName;

	cin >> parentName;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	ClassBase* head = new ClassBase(parentName); // head object

	while (true) {

		cin >> parentName >> childName;

		if (parentName == childName) { // exit condition

			return;
		}

		// new child object
		ClassBase* child = new ClassBase(childName, progenitor->getObject(parentName));
	}
};

int ClassApplication::executeApp() {

	// head object name output:
	cout << progenitor->childrenList.at(1)->getObjName();
	// head object showTree method call:
	progenitor->childrenList.at(1)->showTree();

	return 0;
};
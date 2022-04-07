#include "ClassApplication.h"
#include "ClassBranch.h"

using std::cin;
using std::cout;
using std::numeric_limits;
using std::streamsize;

ClassApplication::ClassApplication(ClassBase* p_Parent) {

	// using setParent due to lack of access to the private field:
	ClassBase::progenitor->setParent(p_Parent);
	ClassBase::progenitor->setObjName("progenitor");
};

void ClassApplication::formTree() {

	string parentName, childName;

	cin >> parentName;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	ClassBase* head = new ClassBase(parentName); // head object

	ClassBase* child = nullptr;

	while (true) {

		cin >> parentName >> childName;

		if (parentName == childName) { return; } // exit condition

		// new child object
		child = new ClassBranch(childName, progenitor->getObject(parentName));
	}
};

int ClassApplication::executeApp() {

	// head object name output:
	cout << progenitor->childrenList.at(0)->getObjName();
	// head object showTree method call:
	progenitor->childrenList.at(0)->showTree();

	return 0;
};
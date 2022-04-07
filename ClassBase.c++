#include "ClassBase.h"

using std::cout;

// creating progenitor object
ClassBase* ClassBase::progenitor = new ClassBase(); 

ClassBase::ClassBase(string objectName, ClassBase* p_Parent) {

	this->objectName = objectName;
	if (p_Parent) { // if object isn't a head

		setParent(p_Parent);

		// adding current object to the children list of its parent:
		p_Parent->childrenList.push_back(this);
	}
	else { // if object is head

		setParent(progenitor); // now progenitor is a parent of a head object

		// adding head object to the children list of progenitor:
		progenitor->childrenList.push_back(this);
	}
};

// setter for name
void ClassBase::setObjName(string objectName) {

	this->objectName = objectName;
};

// getter for name
string ClassBase::getObjName() {

	return objectName;
};

// solves the problem of access to the private field 
// of ClassBase object from ClassApplication (without using protected)
void ClassBase::setParent(ClassBase* p_Parent) {

	this->p_Parent = p_Parent;
};

// is used in formTree ClassApplication method
ClassBase* ClassBase::getObject(string objectName) {

	// temporary pointer at ClassBase object
	ClassBase* tempVar = nullptr;

	// iteration over children of current object:
	for (size_t i = 0; i < childrenList.size(); i++) {

		tempVar = childrenList.at(i)->getObject(objectName);
		if (tempVar->getObjName() == objectName) {

			return tempVar;
		}
	}

	return this; // returns the pointer at itself
};

void ClassBase::showTree() {

	// The tree is printed with the help of recursion
	// The exit condition is the lack of children objects

	if (!childrenList.size()) { return; }

	// output of parent object
	cout << '\n' << this->getObjName();

	// iteration over children of current object:
	for (const auto child : childrenList) {

		cout << "  " << child->getObjName();
	}
	
	// iteration over ALL children children using recursion:
	for (const auto child : childrenList) {

		// showTree method call for each child
		child->showTree();
	}
};
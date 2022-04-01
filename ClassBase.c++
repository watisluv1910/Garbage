#include "ClassBase.h"

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

	// parent object is always at the 1st pos 
	// (0 index) in its children list:
	childrenList.push_back(this); 
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

	// tempVar is needed also to prevent 
	// error in case of incorrect enter, for example:
	// 
	// Incorrect head object enter (ignores Object_1):
	// Object_root Object_1
	// Object_1 Object_2
	// 
	// Will be equal to:
	// Object_root
	// Object_root Object_2
	//
	// Incorrect inheritance (ignores Object_1):
	// Object_root
	// Object_1 Object_2
	// Object_1 Object_3
	// Object_1 Object_4
	// Object_3 Object_5
	// 
	// Will be equal to:
	// Object_root
	// Object_root Object_2
	// Object_2 Object_3
	// Object_3 Object_4
	// Object_3 Object_5

	// temporary pointer at ClassBase object
	ClassBase* tempVar = nullptr;

	// iteration over children of current object:
	for (size_t i = 0; i < childrenList.size(); i++) {

		tempVar = childrenList.at(i);
		if (childrenList.at(i)->getObjName() == objectName) {

			return childrenList.at(i);
		}
	}
	
	// iteration over ALL children using recursion:
	for (size_t i = 1; i < childrenList.size(); i++) {

		tempVar = (childrenList.at(i)->getObject(objectName));
		if (childrenList.at(i)->getObject(objectName)->getObjName() == objectName) {

			return childrenList.at(i)->getObject(objectName);
		}
	}

	return tempVar; // returns pointer at the latest entered object (child probably)
};

void ClassBase::showTree() {

	// iteration over children of current object:
	for (size_t i = 0; i < childrenList.size(); i++) {

		if (!i) {

			cout << endl;
		}

		cout << childrenList.at(i)->getObjName();

		// if element is not the last child:
		if (i + 1 < childrenList.size()) {

			cout << "  ";
		}
	}

	// iteration over ALL children children using recursion:
	for (size_t i = 1; i < childrenList.size(); i++) {
		
		// checking the existance of probably one child:
		if (childrenList.at(i)->childrenList.size() > 1) {

			// showTree method call for each child (recursion)
			childrenList.at(i)->showTree();
		}
	}
};
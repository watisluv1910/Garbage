#include "ClassBase.h"

ClassBase* ClassBase::progenitor = new ClassBase();

ClassBase::ClassBase(string objectName, ClassBase* p_Parent) {

	/*this->subordinateObjName = subordinateObjName;
	currentObjState = 0;

	this->headObjPointer = headObjPointer;

	if (headObjPointer) {

		headObjPointer->subordinateObjList.push_back(this);
	}*/

	this->objectName = objectName;
	if (p_Parent) {

		this->p_Parent = p_Parent;
		p_Parent->childrenList.push_back(this);
	}
	else {

		setParent(progenitor);
		(this->p_Parent)->childrenList.push_back(this);
	}

	childrenList.push_back(this);
};

void ClassBase::setObjName(string objectName) {

	this->objectName = objectName;
};

string ClassBase::getObjName() {

	return objectName;
};

void ClassBase::setParent(ClassBase* p_Parent) {

	this->p_Parent = p_Parent;
};

//void ClassBase::addChild(ClassBase* p_Child) {
//
//
//};

//void ClassBase::deleteChild(string objectName) {
//
//
//};

ClassBase* ClassBase::getObject(string objectName) {

	ClassBase* tempVar = nullptr;

	for (size_t i = 0; i < childrenList.size(); i++) {

		tempVar = childrenList.at(i);
		if (childrenList.at(i)->getObjName() == objectName) {

			return childrenList.at(i);
		}
	}

	for (size_t i = 1; i < childrenList.size(); i++) {

		tempVar = (childrenList.at(i)->getObject(objectName));
		if (childrenList.at(i)->getObject(objectName)->getObjName() == objectName) {

			return childrenList.at(i)->getObject(objectName);
		}
	}

	return tempVar;
};

//ClassBase* ClassBase::getObject(string objectPath) {
//
//
//};

void ClassBase::showTree() {

	for (size_t i = 0; i < childrenList.size(); i++) {

		if (!i) {

			cout << endl;
		}

		cout << childrenList.at(i)->getObjName();

		if (i + 1 < childrenList.size()) {

			cout << "  ";
		}
	}

	for (size_t i = 1; i < childrenList.size(); i++) {

		if (childrenList.at(i)->childrenList.size() > 1) {

			childrenList.at(i)->showTree();
		}
	}
};
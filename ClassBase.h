#pragma once
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;

class ClassBase {
private:
	
	string objectName = "";
	ClassBase* p_Parent; // pointer at parent object
public:
	
	ClassBase() { p_Parent = nullptr; }; // default contructor
	ClassBase(string objectName, ClassBase* p_Parent = nullptr);

	void setObjName(string objName);
	string getObjName();
	void setParent(ClassBase* p_Parent);
	ClassBase* getObject(string objectName);
	void showTree();

	vector<ClassBase*> childrenList;

	// progenitor object is a head object by default
	static ClassBase* progenitor;

	//void addChild(ClassBase* p_Child);
	//void deleteChild(string objectName);
	// //ClassBase* getObject(string objectPath);
	//vector<ClassBase*> ::iterator currChild;
};
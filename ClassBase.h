#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ClassBase {
private:
	
	string objectName = "";
	ClassBase* p_Parent;
public:
	
	ClassBase() { p_Parent = nullptr; };
	ClassBase(string objectName, ClassBase* p_Parent = nullptr);

	void setObjName(string objName);
	string getObjName();
	void setParent(ClassBase* p_Parent);
	//void addChild(ClassBase* p_Child);
	//void deleteChild(string objectName);
	ClassBase* getChild(string objectName);
	//ClassBase* getObject(string objectPath);
	void showTree();

	vector<ClassBase*> childrenList;
	static ClassBase* progenitor;
	//vector<ClassBase*> ::iterator currChild;
};
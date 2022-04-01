#include <iostream>
#include "ClassApplication.h"

using namespace std;

int main() {
    
    ClassApplication object; // ClassApplication object creation

    object.formTree();

    // returning the result of executeApp method according to the task:
    return object.executeApp();
}
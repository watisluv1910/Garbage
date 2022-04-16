#include "application_class.h"

int main() {
    
    ApplicationClass object; // Application object creation

    object.FormTree();

    object.SetStates();

    // returning the result of ExecuteApp method according to the task:
    return object.ExecuteApp();
}

#include "application_class.h"

int main()
{
    ApplicationClass object; // Application object creation

    object.FormTree();

    // Returning the result of ExecuteApp method according to the task:
    return object.ExecuteApp();
}
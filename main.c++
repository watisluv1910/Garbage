#include "network_class.h"

int main()
{
    NetworkClass network_system; // Application object creation

    network_system.FormTree();

    // Returning the result of ExecuteApp method according to the task:
    return network_system.ExecuteApp();
}
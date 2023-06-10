#include <iostream>
#include <ostream>

using namespace std;

void getInput(int &num_server, int &num_cycle)
{
    cout << "Select option to run load balancer: [d]efault or [c]ustom: ";
    char select;
    cin >> select;

    switch (select)
    {
    case 'd':
        break;
    case 'c':
        cout << "Enter number of servers: ";
        cin >> num_server;
        cout << "Enter number of clock cycles: ";
        cin >> num_cycle;
        break;
    default:
        cout << "Invalid. Please select a valid option." << endl;
        getInput(num_server, num_cycle);
        break;
    }
}

int main()
{
    // default
    int num_server = 10, num_cycle = 10000;
    getInput(num_server, num_cycle);

    int full_queue = num_server * 100;
}
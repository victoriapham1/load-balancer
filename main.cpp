#include <iostream>
#include <ostream>
#include <vector>
#include <queue>

#include "webserver.h"
#include "request.h"
#include "loadbalancer.h"

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

    vector<Webserver> servers;
    for (int i = 0; i < num_server; i++)
    {
        servers.push_back(Webserver(i));
    }

    queue<Request> requestqueue;
    int full_queue = num_server * 100;
    // int full_queue = 10;
    for (int i = 0; i < full_queue; i++)
    {
        Request r = Request();
        // cout << r.getIP_in() << " " << r.getIP_out() << " " << r.getTime() << endl;
        requestqueue.push(r);
    }

    cout << "This load balancer has " << num_server << " servers and will be running for " << num_cycle << " clock cycles, with a starting queue of " << full_queue << " requests." << endl;
    cout << "The task time ranges from [1, 500]." << endl;

    LoadBalancer l(requestqueue, servers, num_cycle);
    l.process();

    cout << "After " << num_cycle << " clock cycles, the ending queue currently has " << l.getRequestQueueSize() << " requests." << endl;
}
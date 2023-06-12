#include <iostream>
#include <queue>
#include <vector>

#include "webserver.h"

#ifndef LOADBALANCER_H
#define LOADBALANCER_H

using namespace std;

class LoadBalancer
{
private:
    queue<Request> requestQueue;
    vector<Webserver> servers;
    int time;

public:
    LoadBalancer(queue<Request> requestqueue, vector<Webserver> servers, int time);
    ~LoadBalancer(){};
    void process();
    int getRequestQueueSize() { return this->requestQueue.size(); };
    bool generateRequest();
};

#endif
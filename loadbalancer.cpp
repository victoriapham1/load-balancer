#include <iostream>
#include <random>

#include "loadbalancer.h"
#include "request.h"

LoadBalancer::LoadBalancer(queue<Request> requestqueue, vector<Webserver> servers, int time)
{
    this->requestQueue = requestqueue;
    this->servers = servers;
    this->time = time;
}

void LoadBalancer::process()
{
    int availableServers = this->servers.size();
    int full_queue = requestQueue.size();
    int requestsMade = 0;

    for (int i = 0; i < this->time; i++)
    {
        for (auto &server : this->servers)
        {
            bool serverStatus = server.getStatus();
            if (serverStatus && !this->requestQueue.empty())
            {
                server.processRequest(this->requestQueue.front(), i);
                this->requestQueue.pop();
                availableServers--;
            }

            server.currentState(i);

            if (server.getStatus())
            {
                availableServers++;
            }
        }

        if (this->requestQueue.empty() && availableServers == this->servers.size())
        {
            cout << "There are currently no requests left to process, stopping load balancer at " << i << " clock cycles." << endl;
            break;
        }

        // generate occasional requests if queue is not full
        if (this->requestQueue.size() < full_queue)
        {
            if (generateRequest())
            {
                requestsMade++;
                this->requestQueue.push(Request());
            }
        }
    }

    cout << requestsMade << " new requests made." << endl;
}

bool LoadBalancer::generateRequest()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(mt) < 0.1;
}
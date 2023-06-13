/**
 * @file loadbalancer.cpp
 * @brief Implementation of the LoadBalancer class.
 */

#include <iostream>
#include <random>

#include "loadbalancer.h"
#include "request.h"
#include "firewall.h"

/**
 * @brief Constructs a LoadBalancer object with the specified parameters.
 * @param requestqueue The request queue.
 * @param servers The vector of web servers.
 * @param time The time duration for load balancing.
 */
LoadBalancer::LoadBalancer(queue<Request> requestqueue, vector<Webserver> servers, int time)
{
    this->requestQueue = requestqueue;
    this->servers = servers;
    this->time = time;
}

/**
 * @brief Constructs a LoadBalancer object with the specified parameters, including a firewall.
 * @param requestqueue The request queue.
 * @param servers The vector of web servers.
 * @param time The time duration for load balancing.
 * @param firewall The firewall object to be used.
 */
LoadBalancer::LoadBalancer(queue<Request> requestqueue, vector<Webserver> servers, int time, FireWall firewall)
{
    this->requestQueue = requestqueue;
    this->servers = servers;
    this->time = time;
    this->firewall = firewall;
    this->isFirewallOn = true;
}

/**
 * @brief Processes the load balancing operation.
 */
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
                Request r = this->requestQueue.front();
                if (this->isFirewallOn)
                {
                    // Ensure Request IPs are not restricted given the firewall range.
                    if (this->firewall.isAddressNotInRange(r.getIP_in()) && this->firewall.isAddressNotInRange(r.getIP_out()))
                    {
                        server.processRequest(r, i);
                        cout << "Server " << server.getName() << " has begun processing " << r.getIP_in() << " to " << r.getIP_out() << " at " << i << " clock cycle." << endl;
                        availableServers--;
                    }
                    else
                    {
                        cout << "BLOCKED: Request from " << r.getIP_in() << " to " << r.getIP_out() << "." << endl;
                    }
                }
                else // If firewall is not on, load the balancer as normal.
                {
                    server.processRequest(r, i);
                    cout << "Server " << server.getName() << " has begun processing " << r.getIP_in() << " to " << r.getIP_out() << " at " << i << " clock cycle." << endl;
                    availableServers--;
                }
                this->requestQueue.pop();
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
                Request r = Request();
                this->requestQueue.push(r);
                cout << "Request generated: From " << r.getIP_in() << " to " << r.getIP_out() << " in " << r.getTime() << endl;
            }
        }
    }

    cout << requestsMade << " new requests made." << endl;
}

/**
 * @brief Generates a request with a 10% chance.
 *
 * @return True if a request is generated, false otherwise.
 */
bool LoadBalancer::generateRequest()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(mt) < 0.1;
}
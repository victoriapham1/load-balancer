/**
 * @file loadbalancer.h
 *
 * @brief This file contains the declaration of the LoadBalancer class.
 */

#include <iostream>
#include <queue>
#include <vector>

#include "webserver.h"

#ifndef LOADBALANCER_H
#define LOADBALANCER_H

using namespace std;

/**
 * @class LoadBalancer
 *
 * @brief Represents a load balancer that distributes requests among multiple web servers.
 */
class LoadBalancer
{
private:
    queue<Request> requestQueue; /**< The queue of requests to be processed. */
    vector<Webserver> servers;   /**< The vector of web servers. */
    int time;                    /**< The maximum number of clock cycles to run the load balancing process. */

public:
    /**
     * @brief Constructs a LoadBalancer object.
     *
     * @param requestqueue The queue of requests to be processed.
     * @param servers The vector of web servers.
     * @param time The maximum number of clock cycles to run the load balancing process.
     */
    LoadBalancer(queue<Request> requestqueue, vector<Webserver> servers, int time);

    /**
     * @brief Destructor for the LoadBalancer class.
     */
    ~LoadBalancer(){};

    /**
     * @brief Processes the requests using the load balancing algorithm.
     */
    void process();

    /**
     * @brief Returns the size of the request queue.
     *
     * @return The size of the request queue.
     */
    int getRequestQueueSize() { return this->requestQueue.size(); };

    /**
     * @brief Generates a request with a 10% chance.
     *
     * @return True if a request is generated, false otherwise.
     */
    bool generateRequest();
};

#endif
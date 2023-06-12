/**
 * @file webserver.cpp
 *
 * @brief This file contains the implementation of the Webserver class member functions.
 */

#include <iostream>
#include "webserver.h"

/**
 * @brief Constructs a Webserver object with the given name.
 *
 * @param i The name or identifier of the web server.
 */
Webserver::Webserver(int i)
{
    this->name = i;
    this->reset();
}

/**
 * @brief Destroys the Webserver object.
 */
Webserver::~Webserver()
{
    this->reset();
}

/**
 * @brief Resets the web server to its initial state.
 */
void Webserver::reset()
{
    this->start = -1;
    this->isAvailable = true;
}

/**
 * @brief Gets the availability status of the web server.
 *
 * @return True if the web server is available, false otherwise.
 */
bool Webserver::getStatus()
{
    return this->isAvailable;
}

/**
 * @brief Processes a request by the web server.
 *
 * @param request The request to be processed.
 * @param startTime The start time of the request processing.
 */
void Webserver::processRequest(Request request, int startTime)
{
    this->request = request;
    this->isAvailable = false;
    this->start = startTime;
}

/**
 * @brief Updates the current state of the web server based on the current time.
 *
 * @param curTime The current time.
 */
void Webserver::currentState(int curTime)
{
    int tmp = curTime - this->start;
    if (tmp == this->request.getTime())
    {
        this->reset();
        cout << "Server " << this->name << " has completed request from " << this->request.getIP_in() << " to " << this->request.getIP_out() << " at " << curTime << " clock cycle." << endl;
    }
}
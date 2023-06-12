/**
 * @file webserver.h
 *
 * @brief This file contains the declaration of the Webserver class.
 */

#include <iostream>
#include "request.h"

#ifndef WEBSERVER_H
#define WEBSERVER_H

using namespace std;

/**
 * @class Webserver
 *
 * @brief Represents a web server that processes requests.
 */
class Webserver
{
private:
    Request request;  /**< The request being processed by the web server. */
    int start;        /**< The start time of the current request processing. */
    bool isAvailable; /**< Flag indicating if the web server is available for processing requests. */
    int name;         /**< The name or identifier of the web server. */

public:
    /**
     * @brief Constructs a Webserver object with the specified name.
     *
     * @param i The name or identifier of the web server.
     */
    Webserver(int i);

    /**
     * @brief Destroys the Webserver object.
     */
    ~Webserver();

    /**
     * @brief Resets the web server to its initial state.
     */
    void reset();

    /**
     * @brief Processes the specified request and sets the start time.
     *
     * @param request The request to be processed.
     * @param startTime The start time of the request processing.
     */
    void processRequest(Request request, int startTime);

    /**
     * @brief Gets the availability status of the web server.
     *
     * @return True if the web server is available, false otherwise.
     */
    bool getStatus();

    /**
     * @brief Checks the current state of the web server and performs actions if necessary.
     *
     * @param curTime The current time.
     */
    void currentState(int curTime);

    /**
     * @brief Gets the name or identifier of the web server.
     *
     * @return The name or identifier of the web server.
     */
    int getName() { return this->name; };
};

#endif
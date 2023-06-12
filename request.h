/**
 * @file request.h
 *
 * @brief This file contains the declaration of the Request class.
 */

#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>

/**
 * @class Request
 *
 * @brief Represents a request made to a web server.
 */
class Request
{
private:
    std::string ip_in;  /**< The incoming IP address of the request. */
    std::string ip_out; /**< The outgoing IP address of the request. */
    int time;           /**< The time required to process the request. */

public:
    /**
     * @brief Constructs a Request object.
     */
    Request();

    /**
     * @brief Generates the request details, such as IP addresses and processing time.
     */
    void generate_request();

    /**
     * @brief Generates a random IP address.
     *
     * @return The randomly generated IP address.
     */
    std::string generate_ip();

    /**
     * @brief Gets the time required to process the request.
     *
     * @return The processing time.
     */
    int getTime() { return this->time; };

    /**
     * @brief Gets the incoming IP address of the request.
     *
     * @return The incoming IP address.
     */
    std::string getIP_in() { return this->ip_in; };

    /**
     * @brief Gets the outgoing IP address of the request.
     *
     * @return The outgoing IP address.
     */
    std::string getIP_out() { return this->ip_out; };
};

#endif
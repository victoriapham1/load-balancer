/**
 * @file request.cpp
 *
 * @brief This file contains the implementation of the Request class member functions.
 */

#include <iostream>
#include <random>
#include <ctime>
#include "request.h"

/**
 * @brief Constructs a Request object and generates the request details.
 */
Request::Request()
{
    this->generate_request();
}

/**
 * @brief Generates the details of the request, including IP addresses and time.
 */
void Request::generate_request()
{
    this->ip_in = generate_ip();
    this->ip_out = generate_ip();

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 499);
    this->time = dist(mt);
}

/**
 * @brief Generates a random IP address.
 *
 * @return The generated IP address as a string.
 */
std::string Request::generate_ip()
{
    std::string ipAddress;

    for (int i = 0; i < 4; ++i)
    {
        int component = rand() % 256;
        ipAddress += std::to_string(component);

        if (i < 3)
        {
            ipAddress += ".";
        }
    }

    return ipAddress;
}
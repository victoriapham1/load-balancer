#include <iostream>
#include <random>
#include <ctime>

#include "request.h"

Request::Request()
{
    this->generate_request();
}

void Request::generate_request()
{
    this->ip_in = generate_ip();
    this->ip_out = generate_ip();

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 499);
    this->time = dist(mt);
}

string Request::generate_ip()
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
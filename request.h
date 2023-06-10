#include <iostream>

#ifndef REQUEST_H
#define REQUEST_H

using namespace std;

class Request
{
private:
    string ip_in;
    string ip_out;
    int time;

public:
    Request();
    ~Request(){};
    void generate_request();
    string generate_ip();
    int getTime() { return this->time; };
    string getIP_in() { return this->ip_in; };
    string getIP_out() { return this->ip_out; };
};

#endif
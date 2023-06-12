#include <iostream>

#include "request.h"

#ifndef WEBSERVER_H
#define WEBSERVER_H

using namespace std;

class Webserver
{
private:
    Request request;
    int start;
    bool isAvailable;
    int name;

public:
    Webserver(int i);
    ~Webserver();
    void reset();
    void processRequest(Request request, int startTime);
    bool getStatus();
    void currentState(int curTime);
    int getName() { return this->name; };
};

#endif
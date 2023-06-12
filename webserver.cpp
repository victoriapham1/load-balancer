#include <iostream>

#include "webserver.h"

Webserver::Webserver(int i)
{
    this->name = i;
    this->reset();
}

Webserver::~Webserver()
{
    this->reset();
}

void Webserver::reset()
{
    this->start = -1;
    this->isAvailable = true;
}

bool Webserver::getStatus()
{
    return this->isAvailable;
}

void Webserver::processRequest(Request request, int startTime)
{
    this->request = request;
    this->isAvailable = false;
    this->start = startTime;
}

void Webserver::currentState(int curTime)
{
    int tmp = curTime - this->start;
    if (tmp == this->request.getTime())
    {
        this->reset();
        cout << "Server " << this->name << " has completed request from " << this->request.getIP_in() << " to " << this->request.getIP_out() << " at " << curTime << " clock cycle." << endl;
    }
}
/**
 * @file main.cpp
 * @author Victoria Pham
 * @brief This file contains the main function to run the load balancer simulation.
 */

#include <iostream>
#include <ostream>
#include <vector>
#include <queue>
#include <sstream>

#include "webserver.h"
#include "request.h"
#include "loadbalancer.h"
#include "firewall.h"

using namespace std;

/**
 * @brief Gets input from the user to determine the number of servers and clock cycles for the load balancer.
 *
 * @param num_server Reference to the variable to store the number of servers.
 * @param num_cycle Reference to the variable to store the number of clock cycles.
 */
void getInput(int &num_server, int &num_cycle)
{
    cout << "Select option to run load balancer: [d]efault or [c]ustom: ";
    char select;
    cin >> select;

    switch (select)
    {
    case 'd':
        break;
    case 'c':
        cout << "Enter number of servers: ";
        cin >> num_server;
        cout << "Enter number of clock cycles: ";
        cin >> num_cycle;
        break;
    default:
        cout << "Invalid. Please select a valid option." << endl;
        getInput(num_server, num_cycle);
        break;
    }
}

/**
 * @brief Checks if the given IP address is valid.
 *
 * @param ipAddress The IP address to check.
 * @return True if the IP address is valid, false otherwise.
 */
bool isValidIPAddress(const std::string &ipAddress)
{
    // Splitting the IP address string by '.'
    std::stringstream ss(ipAddress);
    std::string segment;
    std::vector<std::string> segments;

    while (std::getline(ss, segment, '.'))
    {
        segments.push_back(segment);
    }

    // IP address should have 4 segments
    if (segments.size() != 4)
    {
        return false;
    }

    // Checking each segment for validity
    for (const auto &seg : segments)
    {
        // Each segment should contain only digits
        for (char c : seg)
        {
            if (!std::isdigit(c))
            {
                return false;
            }
        }

        // Each segment should be in the range of 0 to 255
        int num = std::stoi(seg);
        if (num < 0 || num > 255)
        {
            return false;
        }

        // Leading zeroes are not allowed, except for 0 itself
        if (seg.length() > 1 && seg[0] == '0')
        {
            return false;
        }
    }

    return true;
}

/**
 * @brief Checks if the second IP address is larger than the first IP address.
 *
 * @param ipAddress1 The first IP address.
 * @param ipAddress2 The second IP address.
 * @return True if the second IP address is larger, false otherwise.
 */
bool isSecondIPAddressLarger(const std::string &ipAddress1, const std::string &ipAddress2)
{
    // Splitting the IP address strings by '.'
    std::stringstream ss1(ipAddress1);
    std::stringstream ss2(ipAddress2);
    std::string segment1, segment2;
    std::vector<std::string> segments1, segments2;

    while (std::getline(ss1, segment1, '.'))
    {
        segments1.push_back(segment1);
    }

    while (std::getline(ss2, segment2, '.'))
    {
        segments2.push_back(segment2);
    }

    // IP address should have 4 segments
    if (segments1.size() != 4 || segments2.size() != 4)
    {
        return false;
    }

    // Comparing each segment of the IP addresses
    for (int i = 0; i < 4; i++)
    {
        int num1 = std::stoi(segments1[i]);
        int num2 = std::stoi(segments2[i]);

        if (num2 > num1)
        {
            return true; // Second IP address is larger
        }
        else if (num1 > num2)
        {
            return false; // Second IP address is not larger
        }
    }

    return true; // IP addresses are identical
}

/**
 * @brief Prompts the user to set up a firewall for DOS protection.
 *
 * @param IP_st [out] The lower bound IP address.
 * @param IP_en [out] The upper bound IP address.
 * @return True if the firewall is set up, false otherwise.
 */
bool getIPRange(string &IP_st, string &IP_en)
{
    cout << "Would you like to set up a firewall for DOS protection? [y]es or [n]o: ";
    char select;
    cin >> select;

    switch (select)
    {
    case 'y':
        cout << "Enter lower bound IP address: ";
        cin >> IP_st;
        while (!isValidIPAddress(IP_st))
        {
            cout << "Invalid. Please enter a valid IP address." << endl;
            cout << "Enter lower bound IP address: ";
            cin >> IP_st;
        }

        cout << "Enter upper bound IP address: ";
        cin >> IP_en;
        while (!isValidIPAddress(IP_en) || !isSecondIPAddressLarger(IP_st, IP_en))
        {
            cout << "Invalid. Please enter a valid IP address or IP address greater than start IP." << endl;
            cout << "Enter upper bound IP address: ";
            cin >> IP_en;
        }
        return true;
        break;
    case 'n':
        return false;
        break;
    default:
        cout << "Invalid. Please select a valid option." << endl;
        getIPRange(IP_st, IP_en);
        break;
    }

    return false;
}

/**
 * @brief The main function to run the load balancer simulation.
 *
 * @return The exit status of the program.
 */
int main()
{
    // default
    int num_server = 10, num_cycle = 10000;
    getInput(num_server, num_cycle);

    string IP_st;
    string IP_en;
    bool activateFirewall = false;

    if (getIPRange(IP_st, IP_en))
    {
        cout << "IP range blocker for DOS protection has been enabled. Requests from " << IP_st << " to " << IP_en << " will not be processed." << endl;
        activateFirewall = true;
    }
    FireWall f(IP_st, IP_en);
    // cout << IP_st << " " << IP_en << endl;

    vector<Webserver> servers;
    for (int i = 0; i < num_server; i++)
    {
        servers.push_back(Webserver(i));
    }

    queue<Request> requestqueue;
    int full_queue = num_server * 100;

    for (int i = 0; i < full_queue; i++)
    {
        Request r = Request();
        requestqueue.push(r);
    }

    cout << "This load balancer has " << num_server << " servers and will be running for " << num_cycle << " clock cycles, with a starting queue of " << full_queue << " requests." << endl;
    cout << "The task time ranges from [1, 500]." << endl;

    LoadBalancer l;
    if (activateFirewall)
    {
        l = LoadBalancer(requestqueue, servers, num_cycle, f);
    }
    else
    {
        l = LoadBalancer(requestqueue, servers, num_cycle);
    }
    l.process();

    cout << "After " << num_cycle << " clock cycles, the ending queue currently has " << l.getRequestQueueSize() << " requests." << endl;
    return 0;
}
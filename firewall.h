/**
 * @file firewall.h
 * @brief Definition of the FireWall class.
 */

#ifndef FIREWALL_H
#define FIREWALL_H

#include <iostream>

/**
 * @class FireWall
 * @brief Represents a firewall that checks if an IP address is within a specified range.
 */
class FireWall
{
private:
    std::string ip_st; /**< The starting IP address of the range. */
    std::string ip_en; /**< The ending IP address of the range. */

public:
    /**
     * @brief Default constructor. Creates a FireWall object.
     */
    FireWall(){};

    /**
     * @brief Constructs a FireWall object with the specified IP range.
     * @param ip_st The starting IP address of the range.
     * @param ip_en The ending IP address of the range.
     */
    FireWall(std::string &ip_st, std::string &ip_en);

    /**
     * @brief Checks if an IP address is not within the specified IP range.
     * @param ipAddress The IP address to check.
     * @return True if the IP address is not within the range, false otherwise.
     */
    bool isAddressNotInRange(const std::string &ipAddress);

    /**
     * @brief Returns the starting IP address of the range.
     * @return The starting IP address.
     */
    std::string getIP_st() { return ip_st; };

    /**
     * @brief Returns the ending IP address of the range.
     * @return The ending IP address.
     */
    std::string getIP_en() { return ip_en; };
};

#endif
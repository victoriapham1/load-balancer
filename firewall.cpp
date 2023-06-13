/**
 * @file firewall.cpp
 * @brief Implementation of the FireWall class.
 */

#include <iostream>
#include <sstream>
#include <vector>

#include "firewall.h"

/**
 * @brief Constructs a FireWall object with the specified IP range.
 * @param ip_st The starting IP address of the range.
 * @param ip_en The ending IP address of the range.
 */
FireWall::FireWall(std::string &ip_st, std::string &ip_en)
{
    this->ip_st = ip_st;
    this->ip_en = ip_en;
}

/**
 * @brief Checks if an IP address is not within the specified IP range.
 * @param ipAddress The IP address to check.
 * @return True if the IP address is not within the range, false otherwise.
 */
bool FireWall::isAddressNotInRange(const std::string &ipAddress)
{
    // Splitting the IP address strings by '.'
    std::stringstream ssAddress(ipAddress);
    std::stringstream ssRangeStart(this->ip_st);
    std::stringstream ssRangeEnd(this->ip_en);
    std::string segmentAddress, segmentRangeStart, segmentRangeEnd;
    std::vector<std::string> segmentsAddress, segmentsRangeStart, segmentsRangeEnd;

    while (std::getline(ssAddress, segmentAddress, '.'))
    {
        segmentsAddress.push_back(segmentAddress);
    }

    while (std::getline(ssRangeStart, segmentRangeStart, '.'))
    {
        segmentsRangeStart.push_back(segmentRangeStart);
    }

    while (std::getline(ssRangeEnd, segmentRangeEnd, '.'))
    {
        segmentsRangeEnd.push_back(segmentRangeEnd);
    }

    // IP address, range start, and range end should have 4 segments
    if (segmentsAddress.size() != 4 || segmentsRangeStart.size() != 4 || segmentsRangeEnd.size() != 4)
    {
        return false;
    }

    // Convert IP addresses to integer values
    uint32_t ip = (std::stoi(segmentsAddress[0]) << 24) + (std::stoi(segmentsAddress[1]) << 16) + (std::stoi(segmentsAddress[2]) << 8) + std::stoi(segmentsAddress[3]);
    uint32_t start = (std::stoi(segmentsRangeStart[0]) << 24) + (std::stoi(segmentsRangeStart[1]) << 16) + (std::stoi(segmentsRangeStart[2]) << 8) + std::stoi(segmentsRangeStart[3]);
    uint32_t end = (std::stoi(segmentsRangeEnd[0]) << 24) + (std::stoi(segmentsRangeEnd[1]) << 16) + (std::stoi(segmentsRangeEnd[2]) << 8) + std::stoi(segmentsRangeEnd[3]);

    // Check if the IP address is not within the given range
    return ip < start || ip > end;
}
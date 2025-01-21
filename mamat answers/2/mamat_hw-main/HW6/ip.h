/**
 * @file ip.h
 * @brief Contains the declaration of the Ip class and related functionalities.
 */
#ifndef IP_H
#define IP_H

#include <stddef.h>
#include <iostream>
#include "generic-field.h"
#include "string.h"
#include <bitset>
#include <string>

/**
 * @enum IpType
 * @brief Enumeration for identifying IP types.
 */
enum {SRC_I = 0, DST_I};

/**
 * @class Ip
 * @brief Represents an IP field and provides related operations.
 */
class Ip : public GenericField {
    int mask;
    String msb_ip;
    bool is_dst;

    public:
    /**
     * @brief Default constructor for the Ip class.
     */
    Ip() : mask(0), msb_ip() {}; 
    /**
     * @brief Copy constructor for the Ip class.
     * @param ip The Ip object to be copied.
     */
    Ip(const Ip &ip) {
        this->mask = ip.mask;
        this->msb_ip = ip.msb_ip;
    }; 
     /**
     * @brief Destructor for the Ip class.
     */
    ~Ip() {}; 
    /**
     * @brief Get the IP mask.
     * @return The IP mask.
     */
    int get_mask() const {
        return mask;
    }
    /**
     * @brief Get the most significant bits of the IP address.
     * @return The most significant bits of the IP address.
     */
    String get_msb_ip() const {
        return msb_ip;
    }
    /**
     * @brief Check if the IP is a destination IP.
     * @return True if the IP is a destination IP, false otherwise.
     */
    bool get_dst() const {
        return is_dst;
    }
     /**
     * @brief Set the IP mask.
     * @param mask The IP mask to be set.
     */
    void set_mask(int mask) {
        this->mask = mask;
    }
    /**
     * @brief Set the most significant bits of the IP address.
     * @param msb_ip The most significant bits of the IP address.
     */
    void set_msb_ip(String msb_ip) {
        this->msb_ip = msb_ip;
    }
      /**
     * @brief Set the IP type based on the parameter.
     * @param string The IP type as a string.
     *
     * This function sets the IP type (source or destination) based on the 
     * parameter.
     * If the parameter equals "dst", the IP type is set as destination IP,
     * otherwise, it is set as source IP.
     */
    void set_dst(const String string) {
        String dst("dst");
        is_dst = (dst.equals(string)) ? DST_I : SRC_I;
    }
     /**
     * @brief Sets the IP value.
     *
     * This function sets the IP value based on the provided string value. 
     * The string value is expected to be in the format "<msb_ip>/<mask>", 
     * where <msb_ip> represents the most significant bits of the IP address 
     * and <mask> represents the network mask.
     *
     * @param value The string value representing the IP address and mask.
     * @return True if the IP value was set successfully, false otherwise.
     */
    bool set_value(String value) override;
    /**
     * @brief Checks if the given packet matches the IP address.
     *
     * This function checks if the provided packet matches the IP address based
     * on the configured IP address and mask. The packet is expected to be a
     * comma-separated string containing multiple commands.
     *
     * @param packet The packet to be checked.
     * @return True if the packet matches the IP address, false otherwise.
     */
    bool match(String packet) override;
}; 

#endif